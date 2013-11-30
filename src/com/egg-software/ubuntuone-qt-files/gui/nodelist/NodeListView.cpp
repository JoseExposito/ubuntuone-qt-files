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
#include "NodeListView.h"
#include "MainWindow.h"
#include "Utils.h"
#include "NodeListModel.h"
#include "NodeListController.h"
#include <QtCore>
#include <QtQuick>

NodeListView::NodeListView(NodeListModel *model)
    : QQuickView(MainWindow::getInstance()->getWindow())
{
    Utils::setGlobalProperties(this->rootContext());
    model->setParent(this);
    this->rootContext()->setContextProperty("nodeListModel", model);
    this->setSource(QUrl("qrc:/qml/NodeListView.qml"));

    connect(this->rootObject(), SIGNAL(openFolder(QString)), this, SLOT(openFolder(QString)));
    connect(this->rootObject(), SIGNAL(openFile(QString)), this, SLOT(openFile(QString)));

    connect(this->rootObject(), SIGNAL(renameNode(QString, QString)), this, SLOT(renameNode(QString, QString)));
    connect(this->rootObject(), SIGNAL(deleteNode(QString)), this, SLOT(deleteNode(QString)));

    connect(this->rootObject(), SIGNAL(downloadFile(QString)), this, SLOT(downloadFile(QString)));
    connect(this->rootObject(), SIGNAL(publishFile(QString, bool)), this, SLOT(publishFile(QString, bool)));
    connect(this->rootObject(), SIGNAL(copyPublicLink(QString)), this, SLOT(copyPublicLink(QString)));
}

void NodeListView::openFolder(const QString &path)
{
    NodeListController *nodeListController = new NodeListController();
    MainWindow::getInstance()->push(nodeListController->createView(path));
}

void NodeListView::openFile(const QString &path)
{
    qDebug() << "Open file: " << path;
}

void NodeListView::renameNode(const QString &path, const QString &newName)
{
    qDebug() << "Rename file: " << path << " to " << newName;
}

void NodeListView::deleteNode(const QString &path)
{
    qDebug() << "Delete file: " << path;
}

void NodeListView::downloadFile(const QString &path)
{
    qDebug() << "Download file: " << path;
}

void NodeListView::publishFile(const QString &path, bool publish)
{
    qDebug() << (publish ? "Publis file: " : "Unpublis file: ") << path;
}

void NodeListView::copyPublicLink(const QString &path)
{
    qDebug() << "Copy public link: " << path;
}
