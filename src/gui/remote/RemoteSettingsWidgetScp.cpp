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

#include "RemoteSettingsWidgetScp.h"
#include "ui_RemoteSettingsWidgetScp.h"

#include "ScpParams.h"

RemoteSettingsWidgetScp::RemoteSettingsWidgetScp(QWidget* parent)
    : RemoteSettingsWidget(parent)
    , m_ui(new Ui::RemoteSettingsWidgetScp())
{
    m_ui->setupUi(this);
}

RemoteSettingsWidgetScp::~RemoteSettingsWidgetScp()
{
}

void RemoteSettingsWidgetScp::initialize()
{
    // Not used. Left to load SCP settings from Database in the future
}

void RemoteSettingsWidgetScp::uninitialize()
{
}

void RemoteSettingsWidgetScp::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    m_ui->url->setFocus();
}

bool RemoteSettingsWidgetScp::save()
{
    // Not used. Left for future to persist SCP settings in database.
    return true;
}

RemoteProgramParams* RemoteSettingsWidgetScp::getRemoteProgramParams()
{
    auto* scpParams = new ScpParams(m_ui->url->text());
    scpParams->setPort(m_ui->port->text());
    scpParams->setKeyFile(m_ui->keyFile->text());
    return scpParams;
}
