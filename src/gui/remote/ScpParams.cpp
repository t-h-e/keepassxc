/*
 *  Copyright (C) 2021 KeePassXC Team <team@keepassxc.org>
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

#include "ScpParams.h"

#include <QMap>
#include <QSharedPointer>
#include <utility>

ScpParams::ScpParams(QString url)
    : RemoteProgramParams()
    , m_url(std::move(url))
{
}

void ScpParams::setPort(QString port)
{
    m_port = std::move(port);
}

void ScpParams::setKeyFile(QString keyFile)
{
    m_keyFile = std::move(keyFile);
}

bool ScpParams::allNecessaryParamsSet()
{
    return !m_url.isEmpty();
}

QString ScpParams::getCommandForDownload(QString destination)
{
    QStringList argumentsForDownload;
    argumentsForDownload << getProgram() << getOptions() << m_url << destination;
    return argumentsForDownload.join(' ');
}

QString ScpParams::getCommandForUpload(QString source)
{
    QStringList argumentsForUpload;
    argumentsForUpload << getProgram() << getOptions() << source << m_url;
    return argumentsForUpload.join(' ');
}

QStringList ScpParams::getOptions()
{
    QStringList options;
    if (!m_port.isEmpty()) {
        options << "-P" << m_port;
    }
    if (!m_keyFile.isEmpty()) {
        options << "-i" << m_keyFile;
    }
    return options;
}
QMap<QString, QString> ScpParams::toConfig()
{
    QMap<QString, QString> configMap;
    configMap.insert("type", type());
    configMap.insert("url", m_url);
    configMap.insert("port", m_port);
    configMap.insert("keyFile", m_keyFile);
    return configMap;
}

QSharedPointer<ScpParams> ScpParams::fromConfig(const QMap<QString, QVariant>& configMap)
{
    QSharedPointer<ScpParams> scpParams;
    Q_ASSERT(configMap.value("type").toString() == scpParams.type());

    scpParams.m_url = configMap.value("url").toString();
    scpParams.m_port = configMap.value("port").toString();
    scpParams.m_keyFile = configMap.value("keyFile").toString();
    return scpParams;
}