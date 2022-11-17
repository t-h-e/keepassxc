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

#include "RemoteSettingsDialog.h"
#include "RemoteSettingsWidgetAnyCommand.h"

#include <QDebug>

RemoteFileDialogImpl::RemoteFileDialogImpl(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::RemoteFileDialogImpl())
    , m_remoteSettingsDialog(new RemoteSettingsDialog(this))
    , m_remoteProgramParams(nullptr)
//    , m_remoteAnyCommandWidget(new RemoteSettingsWidgetAnyCommand(this))
{
    m_ui->setupUi(this);

    // TODO: add widget
    //  see RemoteSettingsDialog::RemoteSettingsDialog
    m_ui->verticalLayout->addWidget(m_remoteSettingsDialog);

    connect(m_remoteSettingsDialog, SIGNAL(cancel(bool)), SLOT(close()));
    connect(m_remoteSettingsDialog,
            SIGNAL(syncWithRemote(RemoteProgramParams*)),
            SLOT(acceptRemoteProgramParams(RemoteProgramParams*)));
}

void RemoteFileDialogImpl::acceptRemoteProgramParams(RemoteProgramParams* params)
{
    m_remoteProgramParams = params;
    accept();
    // emit accepted();
}

QString RemoteFileDialogImpl::getRemoteFileName(QWidget* parent)
{
    auto* dialog = new RemoteFileDialogImpl(parent);

    dialog->exec(); // TODO: use open() after verifying that everything else works. apparently exec is dangerous

    if (dialog->m_remoteProgramParams != nullptr) {
        qDebug() << dialog->m_remoteProgramParams->getCommandForDownload("what");
        // TODO: next download :)
    }

    return nullptr;
}