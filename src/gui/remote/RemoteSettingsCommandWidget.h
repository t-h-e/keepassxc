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

#ifndef KEEPASSXC_REMOTESETTINGSCOMMANDWIDGET_H
#define KEEPASSXC_REMOTESETTINGSCOMMANDWIDGET_H

#include "RemoteProgramParams.h"

#include <QWidget>

class Database;

namespace Ui
{
    class RemoteSettingsCommandWidget;
}

class RemoteSettingsCommandWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RemoteSettingsCommandWidget(QWidget* parent = nullptr);
    Q_DISABLE_COPY(RemoteSettingsCommandWidget);
    ~RemoteSettingsCommandWidget() override;

    void initialize();
    RemoteProgramParams* getRemoteProgramParams();

private slots:
    void saveCurrentSettings();
    void removeCurrentSettings();
    void editCurrentSettings();

private:
    void updateSettingsList();

    const QScopedPointer<Ui::RemoteSettingsCommandWidget> m_ui;
};

#endif // KEEPASSXC_REMOTESETTINGSCOMMANDWIDGET_H
