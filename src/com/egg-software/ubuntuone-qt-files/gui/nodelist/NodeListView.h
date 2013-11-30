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
#ifndef FILESLISTVIEW_H
#define FILESLISTVIEW_H

#include <QtQuick/QQuickView>
class NodeListModel;

/**
 * The NodeListView class shows a list of files, folders or volumes and allows to navigate between directories and
 * manage the files.
 */
class NodeListView : public QQuickView
{
    Q_OBJECT

public:

    NodeListView(NodeListModel *model);

private slots:

    void openFolder(const QString &path);
    void openFile(const QString &path);

    void renameNode(const QString &path, const QString &newName);
    void deleteNode(const QString &path);

    void downloadFile(const QString &path);
    void publishFile(const QString &path, bool publish);
    void copyPublicLink(const QString &path);

};

#endif // FILESLISTVIEW_H
