/*
 *  Copyright (C) 2022 KeePassXC Team <team@keepassxc.org>
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

#include "RemoteHandler.h"
#include "RemoteProcessFactory.h"

#include <QDebug>

RemoteHandler::RemoteHandler(QObject* parent, RemoteProgramParams* remoteProgramParams)
    : QObject(parent)
    , m_remoteProgramParams(remoteProgramParams)
{
    connect(this, SIGNAL(downloadFromRemote()), SLOT(download()));
    connect(this, SIGNAL(uploadToRemote(QSharedPointer<Database>)), SLOT(upload(QSharedPointer<Database>)));
}

RemoteHandler::~RemoteHandler()
{
}

void RemoteHandler::download()
{
    if (!m_remoteProgramParams->allNecessaryParamsSet()) {
        emit downloadError(tr("Not all required parameters set. Cannot sync database."));
        return;
    }

    auto* remoteProcess = RemoteProcessFactory::createRemoteProcess(this);
    QString destination = remoteProcess->getTempFileLocation();
    auto downloadCommand = m_remoteProgramParams->getCommandForDownload(destination);
    qDebug() << "download command" << downloadCommand;
    remoteProcess->start(downloadCommand);
    auto input = m_remoteProgramParams->getInputForDownload(destination);
    if (!input.isEmpty()) {
        qDebug() << "download input" << input;

        remoteProcess->write(input + "\n");
        remoteProcess->waitForBytesWritten();
        remoteProcess->closeWriteChannel();
    }
    bool finished = remoteProcess->waitForFinished(10000);
    int statusCode = remoteProcess->exitCode();
    if (finished && statusCode == 0) {
        emit downloadedSuccessfullyTo(destination);
        return;
    }

    if (finished) {
        emit downloadError(tr("Command `%1` exited with status code: %3").arg(downloadCommand).arg(statusCode));
    } else {
        remoteProcess->kill();
        emit downloadError(tr("Command `%1` did not finish in time. Process was killed.").arg(downloadCommand));
    }
}

void RemoteHandler::upload(const QSharedPointer<Database>& remoteSyncedDb)
{
    auto* remoteProcess = RemoteProcessFactory::createRemoteProcess(this);
    QString source = remoteSyncedDb->filePath();
    auto uploadCommand = m_remoteProgramParams->getCommandForUpload(source);
    qDebug() << "upload command" << uploadCommand;
    remoteProcess->start(uploadCommand);
    auto input = m_remoteProgramParams->getInputForUpload(source);
    if (!input.isEmpty()) {
        qDebug() << "upload input" << input;

        remoteProcess->write(input + "\n");
        remoteProcess->waitForBytesWritten();
        remoteProcess->closeWriteChannel();
    }
    bool finished = remoteProcess->waitForFinished(10000);
    int statusCode = remoteProcess->exitCode();
    if (finished && statusCode == 0) {
        emit uploadSuccess();
        return;
    }

    if (finished) {
        emit uploadError(tr("Failed to upload merged database. Command `%1` exited with status code: %3")
                             .arg(uploadCommand)
                             .arg(statusCode));
    } else {
        remoteProcess->kill();
        emit uploadError(
            tr("Failed to upload merged database. Command `%1` did not finish in time. Process was killed.")
                .arg(uploadCommand)
                .arg(statusCode));
    }
}
