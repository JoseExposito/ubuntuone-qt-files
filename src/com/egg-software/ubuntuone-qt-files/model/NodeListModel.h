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
#ifndef NODELISTMODEL_H
#define NODELISTMODEL_H

#include <QtCore/QAbstractListModel>
#include <QtCore/QList>
#include "NodeInfoDTO.h"

/**
 * The NodeListModel class
 */
class NodeListModel : public QAbstractListModel
{
    Q_OBJECT

public:

    NodeListModel(QObject *parent = 0);
    void setNodeList(QList<NodeInfoDTO *> *nodeList);

protected:

    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
    virtual QHash<int, QByteArray> roleNames() const;
    virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:

    /**
     * Returns the size of the file in KB, MB...
     */
    QString humanReadableSize(int size) const;

    /**
     * Returns the icon path for the specified file.
     */
    QString fileIcon(NodeInfoDTO::NodeType type, const QString &fileName) const;

    QList<NodeInfoDTO *> *nodeList;

};

#endif // NODELISTMODEL_H
