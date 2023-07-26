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

#ifndef KEEPASSX_DATABASESETTINGSWIDGETREMOTE_H
#define KEEPASSX_DATABASESETTINGSWIDGETREMOTE_H

#include "RemoteParams.h"
#include "config-keepassx.h"

#include "../dbsettings/DatabaseSettingsWidget.h"
#include "RemoteSettingsCustomDataHandler.h"

#include <QListWidgetItem>
#include <QPointer>

class Database;
namespace Ui
{
    class DatabaseSettingsWidgetRemote;
}

class DatabaseSettingsWidgetRemote : public DatabaseSettingsWidget
{
    Q_OBJECT

public:
    explicit DatabaseSettingsWidgetRemote(QWidget* parent = nullptr);
    Q_DISABLE_COPY(DatabaseSettingsWidgetRemote);
    ~DatabaseSettingsWidgetRemote() override;

    inline bool hasAdvancedMode() const override
    {
        return false;
    }

public slots:
    void initialize() override;
    void uninitialize() override;
    bool save() override;

private slots:
    void saveCurrentSettings();
    void removeCurrentSettings();
    void editCurrentSettings();

private:
    void updateSettingsList();
    QListWidgetItem* findItemByName(const QString& name);
    void clearFields();

    QPointer<RemoteSettingsCustomDataHandler> m_customDataHandler;
    const QScopedPointer<Ui::DatabaseSettingsWidgetRemote> m_ui;

};

#endif // KEEPASSX_DATABASESETTINGSWIDGETREMOTE_H
