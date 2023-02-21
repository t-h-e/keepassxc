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
#include "core/Config.h"

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
    m_ui->url->setText(config()->get(Config::Remote_Scp_Url).toString());
    m_ui->port->setText(config()->get(Config::Remote_Scp_Port).toString());
    m_ui->keyFile->setText(config()->get(Config::Remote_Scp_KeyFile).toString());
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
    config()->set(Config::Remote_Scp_Url, m_ui->url->text());
    config()->set(Config::Remote_Scp_Port, m_ui->port->text());
    config()->set(Config::Remote_Scp_KeyFile, m_ui->keyFile->text());
    return true;
}

RemoteProgramParams* RemoteSettingsWidgetScp::getRemoteProgramParams()
{
    auto* scpParams = new ScpParams(m_ui->url->text());
    scpParams->setPort(m_ui->port->text());
    scpParams->setKeyFile(m_ui->keyFile->text());
    return scpParams;
}
