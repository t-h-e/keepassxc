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

#include "AnyCommandParams.h"

#include "core/Entry.h"
#include <utility>

AnyCommandParams::AnyCommandParams()
    : RemoteProgramParams()
{
}

void AnyCommandParams::setCommandForDownload(QString downloadCommand)
{
    m_downloadCommand = std::move(downloadCommand);
}

void AnyCommandParams::setInputForDownload(QString downloadCommandInput)
{
    m_downloadCommandInput = std::move(downloadCommandInput);
}

void AnyCommandParams::setCommandForUpload(QString uploadCommand)
{
    m_uploadCommand = std::move(uploadCommand);
}
void AnyCommandParams::setInputForUpload(QString uploadCommandInput)
{
    m_uploadCommandInput = std::move(uploadCommandInput);
}

QString AnyCommandParams::getCommandForDownload(QString destination)
{
    return resolveCommandOrInput(m_downloadCommand, destination);
}

QString AnyCommandParams::getInputForDownload(QString destination)
{
    return resolveCommandOrInput(m_downloadCommandInput, destination);
}

QString AnyCommandParams::getCommandForUpload(QString source)
{
    return resolveCommandOrInput(m_uploadCommand, source);
}

QString AnyCommandParams::getInputForUpload(QString source)
{
    return resolveCommandOrInput(m_uploadCommandInput, source);
}

QString AnyCommandParams::resolveCommandOrInput(QString input, QString tempDatabasePath)
{
    auto resolved = input.replace("{TEMP_DATABASE}", tempDatabasePath);
    // TODO: Question for the reviewer: currently `Entry::resolveReferencePlaceholderRecursive` is private,
    //  but the method does not rely on any field of `Entry`.
    //  Therefore the method could be made static.
    //  Should `Entry::resolveReferencePlaceholderRecursive` in some way be reused to also resolve other placeholders?
    // result = Entry::resolveReferencePlaceholderRecursive(result, 5);
    return resolved;
}
