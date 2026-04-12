/*
 *  Copyright (C) 2023 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "RemoteSettings.h"

#include "core/Config.h"
#include "core/CustomData.h"
#include "core/Database.h"
#include "core/Metadata.h"
#include "crypto/CryptoHash.h"
#include "crypto/Random.h"

#include <QDebug>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

namespace
{
    const int SaltSize = 32;
}

RemoteSettings::RemoteSettings(const QSharedPointer<Database>& db, QObject* parent)
    : QObject(parent)
{
    setDatabase(db);
}

RemoteSettings::~RemoteSettings() = default;

void RemoteSettings::setDatabase(const QSharedPointer<Database>& db)
{
    m_remoteParams.clear();
    m_db = db;
    loadSettings();
}

void RemoteSettings::addRemoteParams(RemoteParams* params)
{
    if (params->name.isEmpty()) {
        qWarning() << "RemoteSettings::addRemoteParams: Remote parameters name is empty";
        return;
    }
    m_remoteParams.insert(params->name, params);
}

void RemoteSettings::removeRemoteParams(const QString& name)
{
    m_remoteParams.remove(name);
}

RemoteParams* RemoteSettings::getRemoteParams(const QString& name) const
{
    if (m_remoteParams.contains(name)) {
        return m_remoteParams.value(name);
    }
    return nullptr;
}

QList<RemoteParams*> RemoteSettings::getAllRemoteParams() const
{
    return m_remoteParams.values();
}

void RemoteSettings::loadSettings()
{
    if (m_db) {
        fromConfig(m_db->metadata()->customData()->value(CustomData::RemoteProgramSettings));
    }
}

void RemoteSettings::saveSettings() const
{
    if (m_db) {
        m_db->metadata()->customData()->set(CustomData::RemoteProgramSettings, toConfig());
    }
}

QString RemoteSettings::toConfig() const
{
    QJsonArray config;
    for (const auto params : m_remoteParams.values()) {
        QJsonObject object;
        object["name"] = params->name;
        object["downloadCommand"] = params->downloadCommand;
        object["downloadCommandInput"] = params->downloadInput;
        object["downloadTimeoutMsec"] = params->downloadTimeoutMsec;
        object["uploadCommand"] = params->uploadCommand;
        object["uploadCommandInput"] = params->uploadInput;
        object["uploadTimeoutMsec"] = params->uploadTimeoutMsec;
        object["syncOnSave"] = params->syncOnSave;
        config << object;
    }
    QJsonDocument doc(config);
    return doc.toJson(QJsonDocument::Compact);
}

void RemoteSettings::fromConfig(const QString& data)
{
    m_remoteParams.clear();

    QJsonDocument json = QJsonDocument::fromJson(data.toUtf8());
    for (const auto& item : json.array().toVariantList()) {
        auto itemMap = item.toMap();
        auto* params = new RemoteParams();
        params->name = itemMap["name"].toString();
        params->downloadCommand = itemMap["downloadCommand"].toString();
        params->downloadInput = itemMap["downloadCommandInput"].toString();
        params->downloadTimeoutMsec = itemMap.value("downloadTimeoutMsec", 10000).toInt();
        params->uploadCommand = itemMap["uploadCommand"].toString();
        params->uploadInput = itemMap["uploadCommandInput"].toString();
        params->uploadTimeoutMsec = itemMap.value("uploadTimeoutMsec", 10000).toInt();
        params->syncOnSave = itemMap.value("syncOnSave", false).toBool();

        m_remoteParams.insert(params->name, params);
    }
}

QByteArray RemoteSettings::getOrCreateSalt(const QSharedPointer<Database>& db)
{
    if (!db || !db->metadata()) {
        return {};
    }

    auto customData = db->metadata()->customData();
    QString saltBase64 = customData->value(CustomData::RemoteSalt);

    if (!saltBase64.isEmpty()) {
        return QByteArray::fromBase64(saltBase64.toLatin1());
    }

    QByteArray salt = randomGen()->randomArray(SaltSize);
    customData->set(CustomData::RemoteSalt, salt.toBase64());
    return salt;
}

QString RemoteSettings::computeCommandHash(const QString& command, const QString& input, const QByteArray& salt)
{
    if (command.isEmpty() && input.isEmpty()) {
        return {};
    }

    QByteArray data;
    data.append(command.toUtf8());
    data.append('\n');
    data.append(input.toUtf8());
    data.append(salt);

    QByteArray hash = CryptoHash::hash(data, CryptoHash::Sha256);
    return QString::fromLatin1(hash.toHex());
}

void RemoteSettings::saveTrustedHash(const QString& dbUuid,
                                     const QString& remoteName,
                                     const QString& operation,
                                     const QString& hash)
{
    if (dbUuid.isEmpty() || remoteName.isEmpty() || operation.isEmpty() || hash.isEmpty()) {
        return;
    }

    QVariantMap trustedCommands = config()->get(Config::RemoteTrustedCommands).toMap();
    QVariantMap dbHashes = trustedCommands.value(dbUuid).toMap();

    QString key = QString("%1_%2").arg(remoteName, operation);
    dbHashes.insert(key, hash);
    trustedCommands.insert(dbUuid, dbHashes);

    config()->set(Config::RemoteTrustedCommands, trustedCommands);
}

bool RemoteSettings::isCommandTrusted(const QString& dbUuid,
                                      const QString& remoteName,
                                      const QString& operation,
                                      const QString& hash)
{
    if (dbUuid.isEmpty() || remoteName.isEmpty() || operation.isEmpty() || hash.isEmpty()) {
        return false;
    }

    QVariantMap trustedCommands = config()->get(Config::RemoteTrustedCommands).toMap();
    QVariantMap dbHashes = trustedCommands.value(dbUuid).toMap();

    QString key = QString("%1_%2").arg(remoteName, operation);
    return dbHashes.value(key).toString() == hash;
}
