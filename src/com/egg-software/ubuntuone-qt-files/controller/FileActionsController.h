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
#ifndef FILEACTIONSCONTROLLER_H
#define FILEACTIONSCONTROLLER_H

#include <QtCore/QObject>
#ifdef Q_OS_ANDROID
#include <jni.h>
#endif
class LoginInfoDTO;
class NodeInfoDTO;

class FileActionsController : public QObject
{
    Q_OBJECT

public:

    /**
     * Only method to get an instance of the class.
     * @return The single instance of the class.
     */
    static FileActionsController *getInstance();

    void deleteNode(NodeInfoDTO *node);
    void publishNode(NodeInfoDTO *node, bool publish);
    void shareLink(NodeInfoDTO *node);
    void rename(NodeInfoDTO *node);

signals:

    void actionFinished();
    void actionFinishedWithError(const QString &errorDescription);

    /**
     * Signal used to call renameAux() on the main thread to avoid problems with Android.
     */
    void renameOnMainThread(NodeInfoDTO *node, const QString &newName);

private slots:

    static void renameAux(NodeInfoDTO *node, const QString &newName);

private:

    LoginInfoDTO *loginInfo;

#ifdef Q_OS_ANDROID
    static void renameCallback(JNIEnv *env, jobject object, jstring result);
#endif

    // Singleton
    static FileActionsController *instance;
    FileActionsController();
    FileActionsController(const FileActionsController &);
    const FileActionsController &operator = (const FileActionsController &);
};

#endif // FILEACTIONSCONTROLLER_H
