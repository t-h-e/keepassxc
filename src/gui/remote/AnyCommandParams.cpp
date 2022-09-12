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

#include "AnyCommandParams.h"

#include <utility>

AnyCommandParams::AnyCommandParams(QString url)
    : RemoteProgramParams()
    , m_url(std::move(url))
{
}

QString AnyCommandParams::getProgram()
{
    return m_url;
}

void AnyCommandParams::setPort(QString port)
{
    m_port = std::move(port);
}

void AnyCommandParams::setKeyFile(QString keyFile)
{
    m_keyFile = std::move(keyFile);
}

QStringList AnyCommandParams::getArgumentsForDownload(QString destination)
{
    QStringList argumentsForDownload;
    argumentsForDownload << m_keyFile << destination;
    return argumentsForDownload;
}

QStringList AnyCommandParams::getArgumentsForUpload(QString source)
{
    QStringList argumentsForUpload;
    argumentsForUpload << source << m_keyFile;
    return argumentsForUpload;
}

QString AnyCommandParams::getInputForDownload(QString) {
    return m_keyFile;
}
QString AnyCommandParams::getInputForUpload(QString) {
    return m_keyFile;
}

QStringList AnyCommandParams::getOptions()
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
