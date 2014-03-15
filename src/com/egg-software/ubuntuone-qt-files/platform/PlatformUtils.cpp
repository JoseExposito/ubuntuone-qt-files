#include "PlatformUtils.h"
#include <QtCore>
#include <QtGui>

PlatformUtils::PlatformUtils(QObject *parent)
    : QObject(parent)
{

}

void PlatformUtils::openFile(const QString &filePath)
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(filePath));
}

QString PlatformUtils::getLocalPath(const QString &nodePath)
{
    QString baseLocalPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
    return baseLocalPath.endsWith(QDir::separator())
            ? baseLocalPath + QString(nodePath).replace("/~/", "")
            : baseLocalPath + QDir::separator() + QString(nodePath).replace("/~/", "");
}

void PlatformUtils::shareLink(const QString &link)
{
    QClipboard *clipboard = qApp->clipboard();
    clipboard->setText(link);
}
