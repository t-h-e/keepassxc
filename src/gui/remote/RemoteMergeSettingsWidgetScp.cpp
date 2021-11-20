/*
 *  Copyright (C) 2018 KeePassXC Team <team@keepassxc.org>
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

#include "RemoteMergeSettingsWidgetScp.h"
#include "ui_RemoteMergeSettingsWidgetScp.h"

#include "core/Group.h"
#include "core/Metadata.h"
#include "ScpParams.h"
#include <QDebug>

RemoteMergeSettingsWidgetScp::RemoteMergeSettingsWidgetScp(QWidget* parent)
    : DatabaseSettingsWidget(parent)
    , m_ui(new Ui::RemoteMergeSettingsWidgetScp())
{
    m_ui->setupUi(this);
}

RemoteMergeSettingsWidgetScp::~RemoteMergeSettingsWidgetScp()
{
}

void RemoteMergeSettingsWidgetScp::initialize()
{
}

void RemoteMergeSettingsWidgetScp::uninitialize()
{
}

void RemoteMergeSettingsWidgetScp::showEvent(QShowEvent* event)
{
    QWidget::showEvent(event);
    m_ui->url->setFocus();
}

bool RemoteMergeSettingsWidgetScp::save()
{
    qDebug() << m_ui->url->text() << "Do not get here";
    return true;
}

RemoteProgramParams* RemoteMergeSettingsWidgetScp::getRemoteProgramParams()
{
    auto* scpParams = new ScpParams(m_ui->url->text());
    scpParams->setPort(m_ui->port->text());
    scpParams->setKeyFile(m_ui->keyFile->text());
    return scpParams;
}
