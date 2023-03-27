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

#include "RemoteFileDialog.h"
#include "ui_RemoteFileDialog.h"

#include "RemoteSettingsDialog.h"

RemoteFileDialog::RemoteFileDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::RemoteFileDialog())
    // TODO: remove and use RemoteSettingsCommandWidget. Maybe directly in widget
    , m_remoteSettingsDialog(new RemoteSettingsDialog(this))
    , m_remoteHandler(new RemoteHandler(this))
{
    m_ui->setupUi(this);

    m_ui->messageWidget->setHidden(true);

    m_ui->verticalLayout->addWidget(m_remoteSettingsDialog);

    connect(m_remoteSettingsDialog, SIGNAL(cancel(bool)), SLOT(close()));
    connect(m_remoteSettingsDialog,
            &RemoteSettingsDialog::syncWithRemote,
            this,
            &RemoteFileDialog::acceptRemoteProgramParams);

    connect(
        m_remoteHandler, &RemoteHandler::downloadedSuccessfullyTo, this, &RemoteFileDialog::handleSuccessfulDownload);
    connect(m_remoteHandler, &RemoteHandler::downloadError, this, &RemoteFileDialog::showRemoteDownloadErrorMessage);

    m_remoteSettingsDialog->initialize();
}

RemoteFileDialog::~RemoteFileDialog()
{
}

void RemoteFileDialog::acceptRemoteProgramParams(RemoteProgramParams* remoteProgramParams)
{
    this->setDisabled(true);
    emit m_remoteHandler->downloadFromRemote(remoteProgramParams);
}

void RemoteFileDialog::handleSuccessfulDownload(const QString& downloadedFileName)
{
    accept();
    emit downloadedSuccessfullyTo(downloadedFileName);
}

void RemoteFileDialog::showRemoteDownloadErrorMessage(const QString& errorMessage)
{
    this->setDisabled(false);
    this->m_ui->messageWidget->showMessage(errorMessage, MessageWidget::Error);
}