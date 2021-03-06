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

#include "BaseWindow.h"
class NodeListModel;
class FileActionsController;

/**
 * The NodeListView class shows a list of files, folders or volumes and allows to navigate between directories and
 * manage the files.
 */
class NodeListView : public BaseWindow
{
    Q_OBJECT

public:

    NodeListView(const QString &path);
    void setToolBarTitle(const QString &toolBarTitle);
    NodeListModel *getModel() const { return this->model; }

private slots:

    void openFolder(int nodeIndex);
    void openFile(int nodeIndex);

    void renameNode(int nodeIndex, const QString &newName);
    void deleteNode(int nodeIndex);
    void publishFile(int nodeIndex, bool publish);
    void copyPublicLink(int nodeIndex);

    void menuCreateFolder(const QString &folderName);
    void menuAbout();

    void refreshView();
    void showError(const QString &errorMessage);

private:

    /**
     * The path displayed in this view.
     */
    QString viewPath;

    /**
     * @see refreshView()
     * @see showError()
     */
    FileActionsController *fileAction;

    /**
     * Model showed by the view.
     */
    NodeListModel *model;

};

#endif // FILESLISTVIEW_H
