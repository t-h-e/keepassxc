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

#include <utility>

ScpParams::ScpParams(QString url)
    : RemoteProgramParams()
    , m_url(std::move(url))
{
}

void ScpParams::setPort(const QString& port)
{
    m_port = port;
}

void ScpParams::setKeyFile(const QString& keyFile)
{
    m_keyFile = keyFile;
}

QString ScpParams::getUrl()
{
    return m_url;
}

QStringList ScpParams::getArgumentsForDownload(const QString& destination)
{
    QStringList argumentsForDownload;
    argumentsForDownload << getOptions() << m_url << destination;
    return argumentsForDownload;
}

QStringList ScpParams::getArgumentsForUpload(const QString& source)
{
    QStringList argumentsForUpload;
    argumentsForUpload << getOptions() << source << m_url;
    return argumentsForUpload;
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
