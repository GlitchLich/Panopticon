#include <QApplication>
#include "ide/include/core/ide.h"

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

    panopticon::ide::MainWindow mainWindow;

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
