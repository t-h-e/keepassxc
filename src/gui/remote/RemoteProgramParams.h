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

#ifndef KEEPASSXC_REMOTEPROGRAMPARAMS_H
#define KEEPASSXC_REMOTEPROGRAMPARAMS_H

#include <QString>

class RemoteProgramParams
{
public:
    virtual ~RemoteProgramParams() = default;

    virtual QString getProgram() const = 0;
    virtual QString getUrl() = 0;
    virtual QStringList getArgumentsForDownload(QString destination) = 0;
    virtual QStringList getArgumentsForUpload(QString source) = 0;
};

#endif // KEEPASSXC_REMOTEPROGRAMPARAMS_H
