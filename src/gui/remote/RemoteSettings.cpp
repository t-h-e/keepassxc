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

#include "RemoteParams.h"
#include <utility>

RemoteSettings::RemoteSettings(QObject* parent)
    : QObject(parent)
{
}

QString RemoteSettings::getName()
{
    return m_name;
}
bool RemoteSettings::getAddToMenu()
{
    return m_addToMenu;
}
QString RemoteSettings::getDownloadCommand()
{
    return m_downloadCommand;
}
QString RemoteSettings::getDownloadCommandInput()
{
    return m_downloadCommandInput;
}
QString RemoteSettings::getUploadCommand()
{
    return m_uploadCommand;
}
QString RemoteSettings::getUploadCommandInput()
{
    return m_uploadCommandInput;
}
void RemoteSettings::setName(QString name)
{
    m_name = std::move(name);
}
void RemoteSettings::setAddToMenu(bool addToMenu)
{
    m_addToMenu = addToMenu;
}
void RemoteSettings::setDownloadCommand(QString downloadCommand)
{
    m_downloadCommand = std::move(downloadCommand);
}
void RemoteSettings::setDownloadCommandInput(QString downloadCommandInput)
{
    m_downloadCommandInput = std::move(downloadCommandInput);
}
void RemoteSettings::setUploadCommand(QString uploadCommand)
{
    m_uploadCommand = std::move(uploadCommand);
}
void RemoteSettings::setUploadCommandInput(QString uploadCommandInput)
{
    m_uploadCommandInput = std::move(uploadCommandInput);
}

QMap<QString, QVariant> RemoteSettings::toConfig()
{
    QMap<QString, QVariant> config;
    config.insert("name", m_name);
    config.insert("addToMenu", m_addToMenu);
    config.insert("downloadCommand", m_downloadCommand);
    config.insert("downloadCommandInput", m_downloadCommandInput);
    config.insert("uploadCommand", m_uploadCommand);
    config.insert("uploadCommandInput", m_uploadCommandInput);
    return config;
}

void RemoteSettings::fromConfig(const QMap<QString, QVariant>& config)
{
    setName(config.value("name", "").toString());
    setAddToMenu(config.value("addToMenu", false).toBool());
    setDownloadCommand(config.value("downloadCommand", "").toString());
    setDownloadCommandInput(config.value("downloadCommandInput", "").toString());
    setUploadCommand(config.value("uploadCommand", "").toString());
    setUploadCommandInput(config.value("uploadCommandInput", "").toString());
}

RemoteParams* RemoteSettings::toRemoteProgramParams()
{
    auto* remoteProgramParams = new RemoteParams();
    remoteProgramParams->setCommandForDownload(m_downloadCommand);
    remoteProgramParams->setInputForDownload(m_downloadCommandInput);
    remoteProgramParams->setCommandForUpload(m_uploadCommand);
    remoteProgramParams->setInputForUpload(m_uploadCommandInput);
    return remoteProgramParams;
}
