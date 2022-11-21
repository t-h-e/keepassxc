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

#include "RemoteFileDialogImpl.h"
#include "ui_RemoteFileDialogImpl.h"

#include "RemoteHandler.h"
#include "RemoteSettingsDialog.h"

#include <QDebug>

RemoteFileDialogImpl::RemoteFileDialogImpl(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::RemoteFileDialogImpl())
    , m_remoteSettingsDialog(new RemoteSettingsDialog(this))
    , m_fileName(nullptr)
{
    m_ui->setupUi(this);

    m_ui->messageWidget->setHidden(true);

    m_ui->verticalLayout->addWidget(m_remoteSettingsDialog);

    connect(m_remoteSettingsDialog, SIGNAL(cancel(bool)), SLOT(close()));
    connect(m_remoteSettingsDialog,
            SIGNAL(syncWithRemote(RemoteProgramParams*)),
            SLOT(acceptRemoteProgramParams(RemoteProgramParams*)));
}

void RemoteFileDialogImpl::acceptRemoteProgramParams(RemoteProgramParams* params)
{
    qDebug() << "params set";
    auto remoteHandler = new RemoteHandler(this, params);
    connect(remoteHandler, &RemoteHandler::downloadedSuccessfullyTo, this, [this, remoteHandler](const QString& downloadedFileName) {
        qDebug() << "success";
        m_fileName = new QString(downloadedFileName);
        accept();
        delete remoteHandler;
    });
    connect(remoteHandler, &RemoteHandler::downloadError, this, [this, remoteHandler](const QString& errorMessage) {
        qDebug() << "fail";
        this->m_ui->messageWidget->showMessage(errorMessage, MessageWidget::Error);
        delete remoteHandler;
    });

    emit remoteHandler->downloadFromRemote();
}

QString RemoteFileDialogImpl::getRemoteFileName(QWidget* parent)
{
    auto* dialog = new RemoteFileDialogImpl(parent);

    dialog->exec(); // TODO: use open() after verifying that everything else works. apparently exec is dangerous

    qDebug() << "exec is over";
    if (dialog->m_fileName != nullptr) {
        qDebug() << dialog->m_fileName;
        return *dialog->m_fileName;
    }
    return nullptr;
}