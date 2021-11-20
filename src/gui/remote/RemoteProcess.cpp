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

#include "RemoteProcess.h"

#include <QTemporaryDir>
#include <QUuid>

RemoteProcess::RemoteProcess(QObject* parent)
    : m_process(new QProcess(parent))
{
}

void RemoteProcess::start(const QString& program, const QStringList& arguments)
{
    m_process->start(program, arguments);
}
bool RemoteProcess::waitForFinished(int msecs)
{
    return m_process->waitForFinished(msecs);
}
int RemoteProcess::exitCode() const
{
    return m_process->exitCode();
}

void RemoteProcess::kill()
{
    m_process->kill();
}

QString RemoteProcess::getTempFileLocation()
{
    QString tempPath = QDir::tempPath();
    return tempPath + "/RemoteDatabase" + QUuid::createUuid().toString() + ".kdbx";
}
