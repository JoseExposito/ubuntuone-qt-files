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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
class QQuickWindow;
class QQmlEngine;
class QQuickView;
class QKeyEvent;

/**
 * Singleton class to manage the main window of the application and the stack view.
 */
class MainWindow : public QObject
{
    Q_OBJECT

public:

    MainWindow(QObject *parent = 0);

    /**
     * Makes the window visible.
     */
    void show() const;

    void push(QQuickView *view);
    void pop();

    inline QQuickWindow *getWindow() { return this->window; }

private:

    /**
     * QML Engine. It is VERY important to preserve it to be able to receive mouse events and etc
     */
    QQmlEngine *engine;

    /**
     * The real QtQuick window.
     */
    QQuickWindow *window;

};

#endif // MAINWINDOW_H
