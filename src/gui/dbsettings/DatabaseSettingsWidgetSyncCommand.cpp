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

#include "DatabaseSettingsWidgetSyncCommand.h"
#include "ui_DatabaseSettingsWidgetSyncCommand.h"

#include "core/Group.h"
#include "core/Metadata.h"
#include "gui/IconModels.h"
#include "gui/Icons.h"
#include "gui/MessageBox.h"

#include <QDebug>

DatabaseSettingsWidgetSyncCommand::DatabaseSettingsWidgetSyncCommand(QWidget* parent)
    : DatabaseSettingsWidget(parent)
    , m_ui(new Ui::DatabaseSettingsWidgetSyncCommand())
{
    m_ui->setupUi(this);
    connect(m_ui->pushButton_13, SIGNAL(clicked()), this, SLOT(syncLoad()));
    connect(m_ui->pushButton_15, SIGNAL(clicked()), this, SLOT(syncSave()));
}

DatabaseSettingsWidgetSyncCommand::~DatabaseSettingsWidgetSyncCommand()
{
}

void DatabaseSettingsWidgetSyncCommand::initialize()
{
}

void DatabaseSettingsWidgetSyncCommand::syncLoad()
{
    // TODO: maybe a command text field is needed after all. Otherwise, a complicated regex is needed if spaces are within the command
    qDebug() << "here load";

    qDebug() << m_ui->plainTextEdit_90->toPlainText();
    qDebug() << m_ui->plainTextEdit_11->toPlainText();
}

void DatabaseSettingsWidgetSyncCommand::syncSave()
{
    qDebug() << "here save";

    qDebug() << m_ui->plainTextEdit_91->toPlainText();
    qDebug() << m_ui->plainTextEdit_13->toPlainText();
}