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

#ifndef KEEPASSX_REMOTEMERGESETTINGSWIDGET_H
#define KEEPASSX_REMOTEMERGESETTINGSWIDGET_H

#include "RemoteProgramParams.h"
#include "config-keepassx.h"
#include "gui/DialogyWidget.h"

#include <QPointer>

class Database;
class RemoteMergeSettingsWidgetScp;

namespace Ui
{
    class RemoteMergeSettingsDialog;
}

class IRemoteMergeSettingsPage
{
public:
    virtual ~IRemoteMergeSettingsPage() = default;
    virtual QString name() = 0;
    virtual QIcon icon() = 0;
    virtual QWidget* createWidget() = 0;
    virtual void loadSettings(QWidget* widget, QSharedPointer<Database> db) = 0;
    virtual void saveSettings(QWidget* widget) = 0;
};

class RemoteMergeSettingsDialog : public DialogyWidget
{
    Q_OBJECT

public:
    explicit RemoteMergeSettingsDialog(QWidget* parent = nullptr);
    ~RemoteMergeSettingsDialog() override;
    Q_DISABLE_COPY(RemoteMergeSettingsDialog);

    void load(const QSharedPointer<Database>& db);
    void addSettingsPage(IRemoteMergeSettingsPage* page);

signals:
    void cancel(bool accepted);
    void mergeWithRemote(RemoteProgramParams* remoteProgramParams);

private slots:
    void save();
    void reject();
    void pageChanged();

private:
    QSharedPointer<Database> m_db;
    const QScopedPointer<Ui::RemoteMergeSettingsDialog> m_ui;
    QPointer<RemoteMergeSettingsWidgetScp> m_remoteScpWidget;
};

#endif // KEEPASSX_REMOTEMERGESETTINGSWIDGET_H
