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

#ifndef KEEPASSXC_REMOTEPARAMSCONFIG_H
#define KEEPASSXC_REMOTEPARAMSCONFIG_H

#include "RemoteProgramParams.h"

#include <QDebug>
#include <QList>
#include <QVariant>

class RemoteParamsConfig
{
public:
    static RemoteParamsConfig* instance();

    QList<QSharedPointer<RemoteProgramParams>> getLastRemoteProgramEntries();
    void updateRemoteProgramEntries(QSharedPointer<RemoteProgramParams> params);

    // code would not compile if this was placed in the cpp file
    template <class T> T* getLastRemoteProgramOf(QString)
    {
        // Compile-time check
        // see https://stackoverflow.com/questions/122316/template-constraints-c
        static_assert(std::is_convertible_v<T*, RemoteProgramParams*>,
                      "type parameter of this class must be convertible to RemoteProgramParams");
        foreach (QSharedPointer<RemoteProgramParams> params, this->m_lastRemoteProgramEntries) {
            auto cur = dynamic_cast<T*>(params.data());
            if (cur != nullptr) {
                return cur;
            }
            //            qDebug() << type;
            //            qDebug() << params;
            //            qDebug() << params->type();
            //            if (params->type() == type) {
            //                return dynamic_cast<T*>(params.data());
            //            }
        }

        return nullptr;
    }

private:
    RemoteParamsConfig();
    int m_numberOfEntries = 5;
    QList<QSharedPointer<RemoteProgramParams>> m_lastRemoteProgramEntries;

    static RemoteParamsConfig* m_instance;

    void syncConfig();
};

inline RemoteParamsConfig* remoteParamsConfig()
{
    return RemoteParamsConfig::instance();
}

#endif // KEEPASSXC_REMOTEPARAMSCONFIG_H
