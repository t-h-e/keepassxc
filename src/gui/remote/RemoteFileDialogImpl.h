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

#ifndef KEEPASSXC_REMOTEFILEDIALOGIMPL_H
#define KEEPASSXC_REMOTEFILEDIALOGIMPL_H

#include <QDialog>
#include <QString>
#include <QWidget>

#include "RemoteProgramParams.h"
//#include "RemoteSettingsWidgetAnyCommand.h"

class RemoteSettingsDialog;
// class RemoteSettingsWidgetAnyCommand;

namespace Ui
{
    class RemoteFileDialogImpl;
}

class RemoteFileDialogImpl : public QDialog
{
    Q_OBJECT
public:
    static QString getRemoteFileName(QWidget* parent);

private slots:
    void acceptRemoteProgramParams(RemoteProgramParams* params);

private:
    RemoteFileDialogImpl(QWidget* parent = nullptr);

    // TODO: cannot use QT pointers here. Why?
    Ui::RemoteFileDialogImpl* m_ui;
    // TODO: use a more general widget
    //  requires refactoring of RemoteSettingsDialog as the dialog contains Database, which we do not need here
    //    RemoteSettingsWidgetAnyCommand* m_remoteAnyCommandWidget;
    RemoteSettingsDialog* m_remoteSettingsDialog;
    RemoteProgramParams* m_remoteProgramParams;
};

#endif // KEEPASSXC_REMOTEFILEDIALOGIMPL_H
