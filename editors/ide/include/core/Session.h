#ifndef SESSION_H
#define SESSION_H

#include <QList>
#include <QString>

namespace panopticon
{

namespace ide
{

class Session
{
public:
    Session();

    static void initRecentFiles();
    static void pushRecentFile(const QString& fileName);
    static void open();
    static void save();
    static void saveAs();

    static QStringList recentFiles;

};

} // ide namespace

} // panopticon namespace

#endif // SESSION_H
