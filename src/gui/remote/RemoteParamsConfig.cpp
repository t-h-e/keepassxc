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

#include "RemoteParamsConfig.h"

#include "AnyCommandParams.h"
#include "ScpParams.h"
#include "core/Config.h"

RemoteParamsConfig* RemoteParamsConfig::m_instance(nullptr);

RemoteParamsConfig* RemoteParamsConfig::instance()
{
    if (!m_instance) {
        m_instance = new RemoteParamsConfig();
    }

    return m_instance;
}

RemoteParamsConfig::RemoteParamsConfig()
{
    auto variantList = config()->get(Config::Remote_Program_Params).toList();
    qDebug() << variantList;
    QList<QSharedPointer<RemoteProgramParams>> typedList;

    foreach (QVariant variant, variantList) {
        qDebug() << variant;
        auto configMap = variant.toMap();
        if (configMap.value("type").toString() == "anyCommand") {
            auto a = AnyCommandParams::fromConfig(configMap);
            AnyCommandParams* b = &a;
            //            auto a = QSharedPointer();
        } else if (configMap.value("type").toString() == "scp") {

        } else {
            // ignore invalid types
        }
        auto remoteProgramParams = static_cast<RemoteProgramParams*>(variant.data());
        qDebug() << remoteProgramParams;
        qDebug() << remoteProgramParams->type();
        auto* scpParams = dynamic_cast<ScpParams*>(remoteProgramParams);
        if (scpParams != nullptr) {
            QSharedPointer<RemoteProgramParams> test(scpParams);
            qDebug() << scpParams;
            //            typedList << scpParams;
            typedList << test;
        }
        auto* anyCommandParams = dynamic_cast<AnyCommandParams*>(remoteProgramParams);
        if (anyCommandParams != nullptr) {
            //            typedList << anyCommandParams;
        }
    }
    //    qDebug() << typedList;
    //    qDebug() << typedList.first();
    //    qDebug() << typedList.first()->type();

    // TODO: restrict to m_numberOfEntries?
    this->m_lastRemoteProgramEntries = typedList;
    //    qDebug() << this->m_lastRemoteProgramEntries;
    //    qDebug() << this->m_lastRemoteProgramEntries.first();
    //    qDebug() << this->m_lastRemoteProgramEntries.first()->type();
}

QList<QSharedPointer<RemoteProgramParams>> RemoteParamsConfig::getLastRemoteProgramEntries()
{
    return this->m_lastRemoteProgramEntries;
}

void RemoteParamsConfig::updateRemoteProgramEntries(QSharedPointer<RemoteProgramParams> params)
{
    int indexOfParams = m_lastRemoteProgramEntries.indexOf(params);
    if (indexOfParams == 0) {
        // nothing changed
        return;
    }
    // new entry or changed position
    if (indexOfParams > 0) {
        m_lastRemoteProgramEntries.removeAt(indexOfParams);
    } else if (m_lastRemoteProgramEntries.size() >= m_numberOfEntries) {
        // entry did not exist before
        m_lastRemoteProgramEntries.removeLast();
    }
    m_lastRemoteProgramEntries.prepend(params);
    syncConfig();
}

void RemoteParamsConfig::syncConfig()
{
    QList<QVariant> lastRemoteProgramEntriesConfig;
    foreach (QSharedPointer<RemoteProgramParams> params, m_lastRemoteProgramEntries) {
        lastRemoteProgramEntriesConfig << QVariant::fromValue(params->toConfig());
    }
    config()->set(Config::Remote_Program_Params, lastRemoteProgramEntriesConfig);
}
