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

#include "RemoteSettingsWidgetAnyCommand.h"
#include "ui_RemoteSettingsWidgetAnyCommand.h"

#include "AnyCommandParams.h"

RemoteSettingsWidgetAnyCommand::RemoteSettingsWidgetAnyCommand(QWidget* parent)
    : RemoteSettingsWidget(parent)
    , m_ui(new Ui::RemoteSettingsWidgetAnyCommand())
{
    m_ui->setupUi(this);
}

RemoteSettingsWidgetAnyCommand::~RemoteSettingsWidgetAnyCommand()
{
}

void RemoteSettingsWidgetAnyCommand::initialize()
{
    // Not used. Left to load SCP settings from Database in the future
}

void RemoteSettingsWidgetAnyCommand::uninitialize()
{
}

void RemoteSettingsWidgetAnyCommand::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    m_ui->downloadCommand->setFocus();
}

bool RemoteSettingsWidgetAnyCommand::save()
{
    // Not used. Left for future to persist settings in database.
    return true;
}

RemoteProgramParams* RemoteSettingsWidgetAnyCommand::getRemoteProgramParams()
{
    auto* anyCommandParams = new AnyCommandParams();
    anyCommandParams->setCommandForDownload(m_ui->downloadCommand->text());
    anyCommandParams->setInputForDownload(m_ui->inputForDownload->toPlainText());
    anyCommandParams->setCommandForUpload(m_ui->uploadCommand->text());
    anyCommandParams->setInputForUpload(m_ui->inputForUpload->toPlainText());
    return anyCommandParams;
}
