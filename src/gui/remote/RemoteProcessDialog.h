/*
 *  Copyright (C) 2024 KeePassXC Team <team@keepassxc.org>
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

#ifndef KEEPASSXC_REMOTEPROCESSDIALOG_H
#define KEEPASSXC_REMOTEPROCESSDIALOG_H

#include "RemoteHandler.h"
#include "gui/DialogyWidget.h"

namespace Ui
{
    class RemoteProcessDialog;
}

class RemoteProcessDialog : public DialogyWidget
{
    Q_OBJECT

public:
    explicit RemoteProcessDialog(QWidget* parent,
                                 const QString& command,
                                 const RemoteHandler::RemoteResult& remoteResult);
    ~RemoteProcessDialog() override;
    Q_DISABLE_COPY(RemoteProcessDialog);

private:
    const QScopedPointer<Ui::RemoteProcessDialog> m_ui;
};

#endif // KEEPASSXC_REMOTEPROCESSDIALOG_H
