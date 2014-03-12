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
#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QtCore/QObject>
class QQuickItem;
class QQmlContext;

/**
 * Base class for all the views/windows of the application.
 */
class BaseWindow : public QObject
{
    Q_OBJECT

public:

    /**
     * @param qmlPath Path to the QML to load.
     * @param parent  Parent of the class.
     */
    BaseWindow(const QString &qmlPath, QObject *parent = 0);

    inline QQuickItem *getView() { return this->view; }

protected:

    /**
     * The real QML window.
     */
    QQuickItem *view;

    /**
     * Context of the view.
     */
    QQmlContext *context;
};

#endif // BASEWINDOW_H
