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

#include "RemoteSettingsDialog.h"
#include "ui_RemoteSettingsDialog.h"

#include "RemoteSettingsWidgetAnyCommand.h"
#include "RemoteSettingsWidgetScp.h"

#include "core/Database.h"
#include "core/Global.h"
#include "gui/Icons.h"

#include <QScrollArea>

#include <QDebug>

RemoteSettingsDialog::RemoteSettingsDialog(QWidget* parent)
    : DialogyWidget(parent)
    , m_ui(new Ui::RemoteSettingsDialog())
    , m_remoteAnyCommandWidget(new RemoteSettingsWidgetAnyCommand(this))
    , m_remoteScpWidget(new RemoteSettingsWidgetScp(this))
{
    m_ui->setupUi(this);

    connect(m_ui->buttonBox, SIGNAL(accepted()), SLOT(save()));
    connect(m_ui->buttonBox, SIGNAL(rejected()), SLOT(reject()));

    m_ui->categoryList->addCategory(tr("scp"), icons()->icon("web"));
    m_ui->categoryList->addCategory(tr("anyCommand"), icons()->icon("web"));
    m_ui->stackedWidget->addWidget(m_remoteScpWidget);
    m_ui->stackedWidget->addWidget(m_remoteAnyCommandWidget);

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

RemoteSettingsDialog::~RemoteSettingsDialog()
{
}

void RemoteSettingsDialog::load(const QSharedPointer<Database>& db)
{
    m_ui->categoryList->setCurrentCategory(0);
    m_remoteScpWidget->load(db);
    m_remoteAnyCommandWidget->load(db);

    m_db = db;
}

void RemoteSettingsDialog::addSettingsPage(IRemoteSettingsPage* page)
{
    const int category = m_ui->categoryList->currentCategory();
    QWidget* widget = page->createWidget();
    widget->setParent(this);
    m_ui->stackedWidget->addWidget(widget);
    m_ui->categoryList->addCategory(page->name(), page->icon());
    m_ui->categoryList->setCurrentCategory(category);
}

void RemoteSettingsDialog::save()
{
    // TODO: use some kind of differentiation
    if (m_ui->categoryList->currentCategory() == 1) {
        qDebug() << "this is one";
    } else if (m_ui->categoryList->currentCategory() == 0) {
        qDebug() << "this is zero";
    } else {
        qDebug() << "this is one: " << m_ui->categoryList->currentCategory();
    }
    emit syncWithRemote(m_remoteAnyCommandWidget->getRemoteProgramParams());
//    emit syncWithRemote(m_remoteScpWidget->getRemoteProgramParams());
}

void RemoteSettingsDialog::reject()
{
    emit cancel(false);
}

void RemoteSettingsDialog::pageChanged()
{
}
