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


#include "RemoteRecentSettingsWidget.h"
#include "ui_RemoteRecentSettingsWidget.h"

#include "core/Config.h"

RemoteRecentSettingsWidget::RemoteRecentSettingsWidget(QWidget* parent)
    : RemoteSettingsWidget(parent)
    , m_ui(new Ui::RemoteRecentSettingsWidget())
{
    m_ui->setupUi(this);
}

RemoteRecentSettingsWidget::~RemoteRecentSettingsWidget()
{
}

void RemoteRecentSettingsWidget::initialize()
{
//    m_ui->url->setText(config()->get(Config::Remote_Scp_Url).toString());
//    m_ui->port->setText(config()->get(Config::Remote_Scp_Port).toString());
//    m_ui->keyFile->setText(config()->get(Config::Remote_Scp_KeyFile).toString());
}

void RemoteRecentSettingsWidget::uninitialize()
{
}

void RemoteRecentSettingsWidget::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
//    m_ui->url->setFocus();
}

bool RemoteRecentSettingsWidget::save()
{
//    config()->set(Config::Remote_Scp_Url, m_ui->url->text());
//    config()->set(Config::Remote_Scp_Port, m_ui->port->text());
//    config()->set(Config::Remote_Scp_KeyFile, m_ui->keyFile->text());
    return true;
}

RemoteProgramParams* RemoteRecentSettingsWidget::getRemoteProgramParams()
{
//    auto* scpParams = new ScpParams(m_ui->url->text());
//    scpParams->setPort(m_ui->port->text());
//    scpParams->setKeyFile(m_ui->keyFile->text());
//    return scpParams;
    return nullptr;
}
