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
#include "ScpParams.h"
#include "AnyCommandParams.h"

RemoteParamsConfig* RemoteParamsConfig::m_instance(nullptr);

RemoteParamsConfig* RemoteParamsConfig::instance()
{
    if (!m_instance) {
        qRegisterMetaTypeStreamOperators<ScpParams>("ScpParams");
        qRegisterMetaTypeStreamOperators<AnyCommandParams>("AnyCommandParams");
        m_instance = new RemoteParamsConfig();
    }

    return m_instance;
}

RemoteParamsConfig::RemoteParamsConfig()
{
    auto variantList = config()->get(Config::Remote_Program_Params).toList();
    QList<RemoteProgramParams*> typedList;
    foreach (QVariant variant, variantList) {
        auto remoteProgramParams = static_cast<RemoteProgramParams*>(variant.data());
        typedList << remoteProgramParams;
    }
    // TODO: restrict to m_numberOfEntries?
    this->m_lastRemoteProgramEntries = typedList;
}

QList<RemoteProgramParams*> RemoteParamsConfig::getLastRemoteProgramEntries()
{
    return this->m_lastRemoteProgramEntries;
}

void RemoteParamsConfig::updateRemoteProgramEntries(RemoteProgramParams* params)
{
    int indexOfParams = m_lastRemoteProgramEntries.indexOf(params);
    if (indexOfParams == 0) {
        // nothing changed
        return ;
    }
    // new entry or changed position
    if (indexOfParams > 0) {
        m_lastRemoteProgramEntries.removeAt(indexOfParams);
    } else {
        // entry did not exist before
        m_lastRemoteProgramEntries.removeLast();
    }
    m_lastRemoteProgramEntries.prepend(params);
    syncConfig();
}

void RemoteParamsConfig::syncConfig()
{
    QList<QVariant> lastRemoteProgramEntriesConfig;
    foreach (RemoteProgramParams* params, m_lastRemoteProgramEntries) {
        auto paramsConfig = convert(params);
        if (!paramsConfig.isNull()) {
            lastRemoteProgramEntriesConfig << convert(params);
        }
    }
    config()->set(Config::Remote_Program_Params, lastRemoteProgramEntriesConfig);
}

QVariant RemoteParamsConfig::convert(RemoteProgramParams* params)
{
    auto* scpParams = dynamic_cast<ScpParams*>(params);
    if (scpParams != nullptr) {
        return QVariant::fromValue(*scpParams);
    }
    auto* anyCommandParams = dynamic_cast<AnyCommandParams*>(params);
    if (anyCommandParams != nullptr) {
        return QVariant::fromValue(*anyCommandParams);
    }
    // TODO: check that this QVariant returns true for `.isNull()`
    return {};
}

//TODO: got stuck here
template <class T> T* RemoteParamsConfig::getLastRemoteProgramOf(QString type)
{
    // Compile-time check
    // see https://stackoverflow.com/questions/122316/template-constraints-c
    // TODO: verify this works

//    static_assert(std::is_convertible_v<T*, RemoteProgramParams*>, "type parameter of this class must derive from RemoteProgramParams");
//    static_assert(std::is_base_of_v<RemoteProgramParams, T>, "type parameter of this class must derive from RemoteProgramParams");
    foreach (RemoteProgramParams* params, m_lastRemoteProgramEntries) {
        if (params->type() == type) {
            return dynamic_cast<T*>(params);
        }
    }

    return T();
}
