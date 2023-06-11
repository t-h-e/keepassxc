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

#include "RemoteSettingsDialog.h"
#include "ui_RemoteSettingsDialog.h"

#include "RemoteParamsConfig.h"

#include "core/Database.h"
#include "core/Global.h"

#include <QKeyEvent>
#include <QMenu>
#include <QScrollArea>

RemoteSettingsDialog::RemoteSettingsDialog(QWidget* parent)
    : DialogyWidget(parent)
    , m_ui(new Ui::RemoteSettingsDialog())
{
    m_ui->setupUi(this);

    connect(m_ui->cancelButton, &QPushButton::clicked, this, &RemoteSettingsDialog::reject);
    connect(m_ui->remoteSaveButton, &QPushButton::clicked, this, &RemoteSettingsDialog::remoteSave);
    connect(m_ui->remoteSyncButton, &QPushButton::clicked, this, &RemoteSettingsDialog::remoteSync);
}

RemoteSettingsDialog::~RemoteSettingsDialog() = default;

void RemoteSettingsDialog::remoteSave()
{
    auto remoteProgramParams = getCurrentParams();
    emit saveToRemote(remoteProgramParams);
}

void RemoteSettingsDialog::remoteSync()
{
    auto remoteProgramParams = getCurrentParams();
    emit syncWithRemote(remoteProgramParams);
}

RemoteParams* RemoteSettingsDialog::getCurrentParams()
{
    return m_ui->remoteSettingsCommandWidget->getRemoteProgramParams();
}

void RemoteSettingsDialog::reject()
{
    emit cancel(false);
}

// similar to DialogyWidget::keyPressEvent but no QDialogButtonBox is used
void RemoteSettingsDialog::keyPressEvent(QKeyEvent* e)
{
#ifdef Q_OS_MACOS
    if (e->modifiers() == Qt::ControlModifier && e->key() == Qt::Key_Period) {
        if (!clickButton(m_ui->cancelButton)) {
            e->ignore();
        }
    } else
#endif
        if (!e->modifiers() || e->modifiers() == Qt::ControlModifier
            || (e->modifiers() & Qt::KeypadModifier && e->key() == Qt::Key_Enter)) {
        switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            if (!clickButton(m_ui->remoteSyncButton)) {
                e->ignore();
            }
            break;
        case Qt::Key_Escape:
            if (!clickButton(m_ui->cancelButton)) {
                e->ignore();
            }
            break;
        default:
            e->ignore();
        }
    } else {
        e->ignore();
    }
}

bool RemoteSettingsDialog::clickButton(QPushButton* pb)
{
    if (pb->isVisible() && pb->isEnabled()) {
        pb->click();
        return true;
    }

    return false;
}