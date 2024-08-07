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

RemoteProcessDialog::RemoteProcessDialog(QWidget* parent,
                                         const QString& command,
                                         const RemoteHandler::RemoteResult& remoteResult,
                                         const QString& translatedMessage)
    : QDialog(parent)
    , m_ui(new Ui::RemoteProcessDialog())
{
    m_ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);

    m_ui->messageWidget->setCloseButtonVisible(false);
    m_ui->messageWidget->setAutoHideTimeout(0);
    if (remoteResult.success) {
        m_ui->messageWidget->showMessage(translatedMessage, MessageWidget::Positive);
    } else {
        m_ui->messageWidget->showMessage(translatedMessage, MessageWidget::Error);
    }

    m_ui->output->setPlainText(QString("$ %1\n%2").arg(command, remoteResult.stdOutput));

    QFont courierFont("Courier");
    courierFont.setStyleHint(QFont::Courier);
    m_ui->output->setFont(courierFont);
}

RemoteProcessDialog::~RemoteProcessDialog() = default;

// TODO:
//  - close button does not do anything
//  - Settings are responsive while testing. Should be disabled
//  - little info in output window. e.g. if host is not known. Why is nothing displayed?
