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

#ifndef KEEPASSXC_SCPPARAMS_H
#define KEEPASSXC_SCPPARAMS_H

#include "RemoteProgramParams.h"
#include <QStringList>

class ScpParams : public RemoteProgramParams {
public:
    explicit ScpParams(QString url);

    QString getProgram() const override
    {
        return "scp";
    }

    void setPort(QString port);
    void setKeyFile(QString keyFile);

    QString getUrl() override;
    QStringList getArgumentsForDownload(QString destination) override;
    QStringList getArgumentsForUpload(QString source) override;

private:
    QStringList getOptions();

    QString m_url;
    QString m_port;
    QString m_keyFile;
};

#endif // KEEPASSXC_SCPPARAMS_H
