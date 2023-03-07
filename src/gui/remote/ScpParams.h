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
#include <QMetaType>
#include <QStringList>

class ScpParams : public RemoteProgramParams
{
public:
    ScpParams() = default;
    ScpParams(const ScpParams &) = default;
    ScpParams &operator=(const ScpParams &) = default;

//    ScpParams(QString url, QString port, QString keyFile);

    explicit ScpParams(QString url);

    void setPort(QString port);
    void setKeyFile(QString keyFile);

    QString type() override {
        return "scp";
    }
    bool allNecessaryParamsSet() override;
    QString getCommandForDownload(QString destination) override;
    QString getCommandForUpload(QString source) override;

    friend QDataStream &operator<<(QDataStream &out, const ScpParams& scpParams);
    friend QDataStream &operator>>(QDataStream &in, ScpParams& scpParams);

private:
    QString getProgram()
    {
        return "scp";
    }

    QStringList getOptions();

    QString m_url;
    QString m_port;
    QString m_keyFile;
};

Q_DECLARE_METATYPE(ScpParams);

#endif // KEEPASSXC_SCPPARAMS_H
