//
// Created by Stefan on 26/03/2023.
//

#include "RemoteSettings.h"

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
    m_name = name;
}
void RemoteSettings::setAddToMenu(bool addToMenu)
{
    m_addToMenu = addToMenu;
}
void RemoteSettings::setDownloadCommand(QString downloadCommand)
{
    m_downloadCommand = downloadCommand;
}
void RemoteSettings::setDownloadCommandInput(QString downloadCommandInput)
{
    m_downloadCommandInput = downloadCommandInput;
}
void RemoteSettings::setUploadCommand(QString uploadCommand)
{
    m_uploadCommand = uploadCommand;
}
void RemoteSettings::setUploadCommandInput(QString uploadCommandInput)
{
    m_uploadCommandInput = uploadCommandInput;
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