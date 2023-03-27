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

#include "RemoteSettingsCommandWidget.h"
#include "ui_RemoteSettingsCommandWidget.h"

#include "AnyCommandParams.h"
#include "RemoteParamsConfig.h"
#include "RemoteSettings.h"
#include "core/Config.h"

RemoteSettingsCommandWidget::RemoteSettingsCommandWidget(QWidget* parent)
    : QWidget(parent)
    , m_ui(new Ui::RemoteSettingsCommandWidget())
{
    m_ui->setupUi(this);

    connect(m_ui->saveSettingsButton, &QPushButton::clicked, this, &RemoteSettingsCommandWidget::saveCurrentSettings);
    connect(m_ui->removeSettingsButton, &QPushButton::clicked, this, &RemoteSettingsCommandWidget::removeCurrentSettings);
    connect(m_ui->settingsListWidget, &QListWidget::itemSelectionChanged, this, &RemoteSettingsCommandWidget::editCurrentSettings);

    updateSettingsList();
}

RemoteSettingsCommandWidget::~RemoteSettingsCommandWidget()
{
}

void RemoteSettingsCommandWidget::initialize()
{
    updateSettingsList();
}

RemoteProgramParams* RemoteSettingsCommandWidget::getRemoteProgramParams()
{
    auto* anyCommandParams = new AnyCommandParams();
    anyCommandParams->setCommandForDownload(m_ui->downloadCommand->text());
    anyCommandParams->setInputForDownload(m_ui->inputForDownload->toPlainText());
    anyCommandParams->setCommandForUpload(m_ui->uploadCommand->text());
    anyCommandParams->setInputForUpload(m_ui->inputForUpload->toPlainText());
    return anyCommandParams;
}

void RemoteSettingsCommandWidget::saveCurrentSettings()
{
    QString name = m_ui->nameLineEdit->text();
    auto* remoteSettings = new RemoteSettings(this);
    remoteSettings->setName(m_ui->nameLineEdit->text());
    remoteSettings->setAddToMenu(m_ui->addToMenuCheckBox->isChecked());
    remoteSettings->setDownloadCommand(m_ui->downloadCommand->text());
    remoteSettings->setDownloadCommandInput(m_ui->inputForDownload->toPlainText());
    remoteSettings->setUploadCommand(m_ui->uploadCommand->text());
    remoteSettings->setUploadCommandInput(m_ui->inputForUpload->toPlainText());

    remoteParamsConfig()->addRemoteSettingsEntry(remoteSettings);
    updateSettingsList();

    auto item = m_ui->settingsListWidget->findItems(name, Qt::MatchExactly).first();
    m_ui->settingsListWidget->setCurrentItem(item);
}

void RemoteSettingsCommandWidget::removeCurrentSettings()
{
    remoteParamsConfig()->removeRemoteSettingsEntry(m_ui->nameLineEdit->text());
    updateSettingsList();
    if (!remoteParamsConfig()->getLastRemoteProgramEntries().empty()){
        m_ui->settingsListWidget->setCurrentRow(0);
    }
}

void RemoteSettingsCommandWidget::editCurrentSettings()
{
    if (m_ui->settingsListWidget->currentItem() == nullptr) {
        return;
    }
    auto* remoteSettings = remoteParamsConfig()->getRemoteSettingsEntry(m_ui->settingsListWidget->currentItem()->text());
    if (remoteSettings == nullptr) {
        // this should never happen
        return;
    }

    m_ui->nameLineEdit->setText(remoteSettings->getName());
    m_ui->addToMenuCheckBox->setChecked(remoteSettings->getAddToMenu());
    m_ui->downloadCommand->setText(remoteSettings->getDownloadCommand());
    m_ui->inputForDownload->setPlainText(remoteSettings->getDownloadCommandInput());
    m_ui->uploadCommand->setText(remoteSettings->getUploadCommand());
    m_ui->inputForUpload->setPlainText(remoteSettings->getUploadCommandInput());
}

void RemoteSettingsCommandWidget::updateSettingsList()
{
    m_ui->settingsListWidget->clear();
    foreach (auto remoteSetting, remoteParamsConfig()->getLastRemoteProgramEntries()) {
        auto* item = new QListWidgetItem(m_ui->settingsListWidget);
        item->setText(remoteSetting->getName());
        m_ui->settingsListWidget->addItem(item);
    }
}