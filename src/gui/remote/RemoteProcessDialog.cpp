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

#include "RemoteProcessDialog.h"
#include "ui_RemoteProcessDialog.h"

#include "gui/MessageBox.h"

// TODO: make this a real dialog
RemoteProcessDialog::RemoteProcessDialog(QWidget* parent,
                                         const QString& command,
                                         const RemoteHandler::RemoteResult& remoteResult)
    : DialogyWidget(parent)
    , m_ui(new Ui::RemoteProcessDialog())
{
    m_ui->setupUi(this);
    //    m_ui->messageWidget->setHidden(true);

    m_ui->messageWidget->setCloseButtonVisible(false);
    m_ui->messageWidget->setAutoHideTimeout(0);
    // TODO: pass in error message
    if (remoteResult.success) {
        m_ui->messageWidget->showMessage(tr("Download command cannot be empty."), MessageWidget::Positive);
    } else {
        m_ui->messageWidget->showMessage(tr("Download command cannot be empty."), MessageWidget::Error);
    }

    m_ui->output->setPlainText(QString("$ %1\n%2").arg(command, remoteResult.stdOutput));
}

RemoteProcessDialog::~RemoteProcessDialog() = default;
