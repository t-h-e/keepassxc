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

#include "RemoteFileDialog.h"
#include "ui_RemoteFileDialog.h"

RemoteFileDialog::RemoteFileDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::RemoteFileDialog())
    , m_remoteHandler(new RemoteHandler(this))
{
    m_ui->setupUi(this);
    m_ui->messageWidget->setHidden(true);

    // setup status bar
    m_statusBar = new QStatusBar(this);
    m_statusBar->setFixedHeight(24);
    m_progressBarLabel = new QLabel(m_statusBar);
    m_progressBarLabel->setVisible(false);
    m_statusBar->addPermanentWidget(m_progressBarLabel);
    m_progressBar = new QProgressBar(m_statusBar);
    m_progressBar->setVisible(false);
    m_progressBar->setTextVisible(false);
    m_progressBar->setMaximumWidth(100);
    m_progressBar->setFixedHeight(15);
    m_progressBar->setMaximum(100);
    m_statusBar->addPermanentWidget(m_progressBar);
    m_ui->verticalLayout->addWidget(m_statusBar);

    connect(m_ui->buttonBox, &QDialogButtonBox::rejected, this, &RemoteFileDialog::close);
    connect(m_ui->buttonBox, &QDialogButtonBox::accepted, this, &RemoteFileDialog::acceptRemoteProgramParams);

    connect(
        m_remoteHandler, &RemoteHandler::downloadedSuccessfullyTo, this, &RemoteFileDialog::handleSuccessfulDownload);
    connect(m_remoteHandler, &RemoteHandler::downloadError, this, &RemoteFileDialog::showRemoteDownloadErrorMessage);
}

RemoteFileDialog::~RemoteFileDialog() = default;

void RemoteFileDialog::acceptRemoteProgramParams()
{
    m_ui->remoteSettingsCommandWidget->setDisabled(true);
    updateProgressBar(50, tr("Downloading..."));
    auto* remoteProgramParams = m_ui->remoteSettingsCommandWidget->getRemoteProgramParams();
    emit m_remoteHandler->downloadFromRemote(remoteProgramParams);
}

void RemoteFileDialog::handleSuccessfulDownload(const QString& downloadedFileName)
{
    accept();
    emit downloadedSuccessfullyTo(downloadedFileName);
}

void RemoteFileDialog::showRemoteDownloadErrorMessage(const QString& errorMessage)
{
    m_ui->remoteSettingsCommandWidget->setDisabled(false);
    updateProgressBar(-1, "");
    m_ui->messageWidget->showMessage(errorMessage, MessageWidget::Error);
}

void RemoteFileDialog::updateProgressBar(int percentage, const QString& message)
{
    if (percentage < 0) {
        m_progressBar->setVisible(false);
        m_progressBarLabel->setVisible(false);
    } else {
        m_progressBar->setValue(percentage);
        m_progressBar->setVisible(true);
        m_progressBarLabel->setText(message);
        m_progressBarLabel->setVisible(true);
    }
}
