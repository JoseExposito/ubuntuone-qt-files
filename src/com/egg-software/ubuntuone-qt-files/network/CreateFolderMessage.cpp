/*
 * This file is part of UbuntuOne Qt Files.
 *
 * UbuntuOne Qt Files is free software:  you can redistribute it  and/or  modify it under the terms of the  GNU  General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * UbuntuOne Qt Files  is distributed in the hope  that it will be useful,  but  WITHOUT ANY WARRANTY;  without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with Foobar.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include "CreateFolderMessage.h"
#include "LoginInfoDTO.h"
#include <QtCore>
#include <QtNetwork>

namespace
{
    static const QString CREATE_FOLDER_URL = "https://one.ubuntu.com/api/file_storage/v1";
}

CreateFolderMessage::CreateFolderMessage(LoginInfoDTO *loginInfo, QObject *parent)
    : AbstractMessage(loginInfo, parent),
      createFolderReply(NULL)
{

}

CreateFolderMessage::~CreateFolderMessage()
{
    delete this->createFolderReply;
}

void CreateFolderMessage::createFolder(const QString &path)
{
    QString url  = CREATE_FOLDER_URL + this->toPercentEncoding(path);
    QString json = "{ \"kind\": \"directory\" }";

    qDebug() << "[+] CREATING FOLDER:";
    qDebug() << "\t Path: " << path;
    qDebug() << "\t URL: "  << url;
    this->printJson(json);

    this->createFolderReply = this->oauthPutRequest(url, json.toUtf8());
}

void CreateFolderMessage::replyFinished(QNetworkReply *reply)
{
    AbstractMessage::replyFinished(reply);

    if (reply == this->createFolderReply) {
        if (this->createFolderReply->error() == QNetworkReply::NoError) {
            qDebug() << "\t Folder correctly created";
            emit this->folderCreated();
        } else {
            qDebug() << "\t Error renaming node: " << this->createFolderReply->errorString();
            emit this->errorCreatingFolder(tr("Error creating folder"));
        }
    }
}
