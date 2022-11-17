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

#include "RemoteFileDialog.h"
#include "RemoteFileDialogImpl.h"

RemoteFileDialog* RemoteFileDialog::m_instance(nullptr);

RemoteFileDialog::RemoteFileDialog()
{
}

QString RemoteFileDialog::getRemoteFileName(QWidget* parent)
{
    const auto result = RemoteFileDialogImpl::getRemoteFileName(parent);
    //    const auto& workingDir = dir.isEmpty() ? config()->get(Config::LastDir).toString() : dir;
    //    const auto result = QDir::toNativeSeparators(
    //        QFileDialog::getOpenFileName(parent, caption, workingDir, filter, selectedFilter, options));

    // TODO: how to check if this is needed without a Mac?
#ifdef Q_OS_MACOS
    // on Mac OS X the focus is lost after closing the native dialog
    if (parent) {
        parent->activateWindow();
    }
#endif
    return result;
}

RemoteFileDialog* RemoteFileDialog::instance()
{
    if (!m_instance) {
        m_instance = new RemoteFileDialog();
    }
    return m_instance;
}