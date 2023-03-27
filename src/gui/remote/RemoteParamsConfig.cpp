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
    QList<RemoteSettings*> typedList;
    foreach (QVariant variant, variantList) {
        auto* remoteProgramParams = new RemoteSettings(); // TODO: add `this` QObject in constructor?
        remoteProgramParams->fromConfig(variant.toMap());
        typedList << remoteProgramParams;
    }
    this->m_lastRemoteProgramEntries = typedList;
}

QList<RemoteSettings*> RemoteParamsConfig::getRemoteProgramEntries()
{
    return this->m_lastRemoteProgramEntries;
}

void RemoteParamsConfig::addRemoteSettingsEntry(RemoteSettings* newRemoteSettings)
{
    // TODO: cool logic so that add does in-place replacement
    QList<RemoteSettings*> toRemove;
    foreach (auto* remoteSettings, m_lastRemoteProgramEntries) {
        if (newRemoteSettings->getName() == remoteSettings->getName()) {
            toRemove << remoteSettings;
        }
    }
    foreach (auto* removeSetting, toRemove) {
        m_lastRemoteProgramEntries.removeOne(removeSetting);
    }

    m_lastRemoteProgramEntries.append(newRemoteSettings);
    syncConfig();
}

void RemoteParamsConfig::removeRemoteSettingsEntry(const QString& name) {
    QList<RemoteSettings*> toRemove;
    foreach (auto* remoteSettings, m_lastRemoteProgramEntries) {
        if (name == remoteSettings->getName()) {
            toRemove << remoteSettings;
        }
    }
    foreach (auto* removeSetting, toRemove) {
        m_lastRemoteProgramEntries.removeOne(removeSetting);
    }

    syncConfig();
}

RemoteSettings* RemoteParamsConfig::getRemoteSettingsEntry(const QString& name) {
    foreach (auto* remoteSettings, m_lastRemoteProgramEntries) {
        if (name == remoteSettings->getName()) {
            return remoteSettings;
        }
    }
    return nullptr;
}

void RemoteParamsConfig::syncConfig()
{
    QList<QVariant> lastRemoteProgramEntriesConfig;
    foreach (RemoteSettings* remoteSettings, m_lastRemoteProgramEntries) {
            lastRemoteProgramEntriesConfig << remoteSettings->toConfig();
    }
    config()->set(Config::Remote_Program_Params, lastRemoteProgramEntriesConfig);
}
