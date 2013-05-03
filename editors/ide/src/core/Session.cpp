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
    QSettings settings("Glitch Lich", "Panopticon");
    recentFiles = settings.value("recentFileList").toStringList();
}

void Session::pushRecentFile(const QString& fileName)
{
    QSettings settings("Glitch Lich", "Panopticon");
    recentFiles = settings.value("recentFileList").toStringList();
    recentFiles.removeAll(fileName);
    recentFiles.push_back(fileName);

    if(recentFiles.size() > 10)
        recentFiles.pop_front();

    settings.setValue("recentFileList", recentFiles);
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
