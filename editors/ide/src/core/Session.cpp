#include "ide/include/core/Session.h"
#include "ide/include/core/ide.h"

namespace panopticon
{

namespace ide
{

QStringList Session::recentFiles;

Session::Session()
{

}

void Session::initRecentFiles()
{
    recentFiles = IDE_SETTINGS->value("recentFileList").toStringList();
}

void Session::pushRecentFile(const QString& fileName)
{
    recentFiles = IDE_SETTINGS->value("recentFileList").toStringList();
    recentFiles.removeAll(fileName);
    recentFiles.push_back(fileName);
    IDE_SETTINGS->setValue("recentFileList", recentFiles);
}

void Session::open()
{

}

void Session::save()
{

}

void Session::saveAs()
{

}

} // ide namespace

} // panopticon namespace
