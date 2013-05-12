#include <QApplication>
#include "ide/include/core/ide.h"
#include "ide/include/core/Session.h"
#include "ide/include/style/StyleGlobals.h"
#include "include/core/heap.h"
#include "include/core/Memory.h"

namespace panopticon
{

namespace ide
{

MainWindow* MAIN_WINDOW = 0; // global pointer
QSettings* IDE_SETTINGS = 0; // global pointer

void Post(const QString& string)
{
    MAIN_WINDOW->post(string);
}

void PostError(const QString& string)
{
    MAIN_WINDOW->postError(string);
}

} // ide namespace

} // panopticon namespace


int main(int argc, char* argv[])
{
    QApplication app(argc,argv);
    app.setApplicationName("Panopticon");
    app.setApplicationVersion("0.1");
    app.setOrganizationName("Chad McKinney and Curtis McKinney");
    app.setOrganizationDomain("glitchlich.com");

    QFile styleFile("resources/ide/Panopticon.qss");

    if(styleFile.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(styleFile.readAll());
        app.setStyleSheet(styleSheet);
    }

    QSettings settings("Glitch Lich", "Panopticon");
    panopticon::ide::IDE_SETTINGS = &settings;
    panopticon::ide::Session::initRecentFiles();
    panopticon::ide::Style style;
    panopticon::ide::style = &style;
    panopticon::ide::MainWindow mainWindow;
    panopticon::ide::MAIN_WINDOW = &mainWindow;


    int result = app.exec();

    panopticon::clear_heap();
    panopticon::gc_free_all();
    return result;
}
