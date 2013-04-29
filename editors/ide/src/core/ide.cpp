#include <QApplication>
#include "ide/include/core/ide.h"
#include "ide/include/style/StyleGlobals.h"

namespace panopticon
{

namespace ide
{

MainWindow* MAIN_WINDOW = 0; // global pointer

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

    panopticon::ide::Style style;
    panopticon::ide::style = &style;
    panopticon::ide::MainWindow mainWindow;
    panopticon::ide::MAIN_WINDOW = &mainWindow;

    /*
    QGuiApplication app(argc,argv);
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    view.connect(view.engine(), SIGNAL(quit()), &app, SLOT(quit()));
    QUrl ideQml(QUrl::fromLocalFile(app.applicationDirPath() + "/resources/ide/qml/PanopticonIDE.qml"));
    view.setSource(ideQml);

    if(QGuiApplication::platformName() == QLatin1String("qnx") ||
          QGuiApplication::platformName() == QLatin1String("eglfs"))
    {
        view.setResizeMode(QQuickView::SizeRootObjectToView);
        view.showFullScreen();
    }

    else
    {
        view.showMaximized();
    }*/

    return app.exec();
}
