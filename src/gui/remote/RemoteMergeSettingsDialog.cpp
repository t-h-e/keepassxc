/*
 *  Copyright (C) 2018 KeePassXC Team <team@keepassxc.org>
 *  Copyright (C) 2012 Felix Geyer <debfx@fobos.de>
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

#include "RemoteMergeSettingsDialog.h"
#include "ui_RemoteMergeSettingsDialog.h"

#include "RemoteMergeSettingsWidgetScp.h"

#include "core/Database.h"
#include "core/Global.h"
#include "gui/Icons.h"

#include <QScrollArea>
#include <QDebug>

RemoteMergeSettingsDialog::RemoteMergeSettingsDialog(QWidget* parent)
    : DialogyWidget(parent)
    , m_ui(new Ui::RemoteMergeSettingsDialog())
    , m_remoteScpWidget(new RemoteMergeSettingsWidgetScp(this))
{
    m_ui->setupUi(this);

    connect(m_ui->buttonBox, SIGNAL(accepted()), SLOT(save()));
    connect(m_ui->buttonBox, SIGNAL(rejected()), SLOT(reject()));

    m_ui->categoryList->addCategory(tr("scp"), icons()->icon("database-merge"));
    m_ui->stackedWidget->addWidget(m_remoteScpWidget);

    auto* scrollArea = new QScrollArea(parent);
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setFrameShadow(QFrame::Plain);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setSizeAdjustPolicy(QScrollArea::AdjustToContents);
    scrollArea->setWidgetResizable(true);

    m_ui->stackedWidget->setCurrentIndex(0);

    connect(m_ui->categoryList, SIGNAL(categoryChanged(int)), m_ui->stackedWidget, SLOT(setCurrentIndex(int)));

    pageChanged();
}

RemoteMergeSettingsDialog::~RemoteMergeSettingsDialog()
{
}

void RemoteMergeSettingsDialog::load(const QSharedPointer<Database>& db)
{
    m_ui->categoryList->setCurrentCategory(0);
    m_remoteScpWidget->load(db);

    m_db = db;
}

void RemoteMergeSettingsDialog::addSettingsPage(IRemoteMergeSettingsPage* page)
{
    const int category = m_ui->categoryList->currentCategory();
    QWidget* widget = page->createWidget();
    widget->setParent(this);
    m_ui->stackedWidget->addWidget(widget);
    m_ui->categoryList->addCategory(page->name(), page->icon());
    m_ui->categoryList->setCurrentCategory(category);
}

void RemoteMergeSettingsDialog::save()
{
    emit mergeWithRemote(m_remoteScpWidget->getRemoteProgramParams());
}

void RemoteMergeSettingsDialog::reject()
{
    emit cancel(false);
}

void RemoteMergeSettingsDialog::pageChanged()
{
}
