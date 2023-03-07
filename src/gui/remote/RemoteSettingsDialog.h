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

#ifndef KEEPASSX_REMOTESETTINGSDIALOG_H
#define KEEPASSX_REMOTESETTINGSDIALOG_H

#include "RemoteProgramParams.h"
#include "config-keepassx.h"
#include "gui/DialogyWidget.h"

#include <QPointer>

class Database;

namespace Ui
{
    class RemoteSettingsDialog;
}

class RemoteSettingsDialog : public DialogyWidget
{
    Q_OBJECT

public:
    explicit RemoteSettingsDialog(QWidget* parent = nullptr);
    ~RemoteSettingsDialog() override;
    Q_DISABLE_COPY(RemoteSettingsDialog);

    void initialize();
    void load(const QSharedPointer<Database>& db);

signals:
    void cancel(bool accepted);
    void saveToRemote(RemoteProgramParams* remoteProgramParams);
    void syncWithRemote(RemoteProgramParams* remoteProgramParams);

protected:
    void keyPressEvent(QKeyEvent* e) override;

private slots:
    void remoteSave();
    void remoteSync();
    void reject();

private:
    RemoteProgramParams* getCurrentParams();
    static bool clickButton(QPushButton* button);

    QSharedPointer<Database> m_db;
    const QScopedPointer<Ui::RemoteSettingsDialog> m_ui;
};

#endif // KEEPASSX_REMOTESETTINGSDIALOG_H
