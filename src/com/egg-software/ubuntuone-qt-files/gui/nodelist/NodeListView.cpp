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

    connect(this->rootObject(), SIGNAL(nodeClicked(QString)), this, SLOT(nodeClicked(QString)));
}

void NodeListView::nodeClicked(const QString &path)
{
    NodeListController *nodeListController = new NodeListController();
    MainWindow::getInstance()->push(nodeListController->createView(path));
}
