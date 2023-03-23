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

#ifndef KEEPASSXC_ANYCOMMANDPARAMS_H
#define KEEPASSXC_ANYCOMMANDPARAMS_H

#include "RemoteProgramParams.h"
#include <QMap>
#include <QStringList>
#include <QVariant>

class AnyCommandParams : public RemoteProgramParams
{
public:
    AnyCommandParams() = default;
    AnyCommandParams(const AnyCommandParams&) = default;
    AnyCommandParams& operator=(const AnyCommandParams&) = default;

    QString type() override
    {
        return "anyCommand";
    }
    bool allNecessaryParamsSet() override
    {
        return true;
    }
    QString getCommandForDownload(QString destination) override;
    QString getInputForDownload(QString destination) override;
    QString getCommandForUpload(QString source) override;
    QString getInputForUpload(QString source) override;

    void setCommandForDownload(QString downloadCommand);
    void setInputForDownload(QString downloadCommandInput);
    void setCommandForUpload(QString uploadCommand);
    void setInputForUpload(QString uploadCommandInput);

    QMap<QString, QString> toConfig() override;
    static QSharedPointer<AnyCommandParams> fromConfig(const QMap<QString, QVariant>& configMap);

private:
    QString resolveCommandOrInput(QString input, const QString& tempDatabasePath);

    QString m_downloadCommand;
    QString m_downloadCommandInput;
    QString m_uploadCommand;
    QString m_uploadCommandInput;
};

#endif // KEEPASSXC_ANYCOMMANDPARAMS_H
