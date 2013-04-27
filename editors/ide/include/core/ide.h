#ifndef IDE_H
#define IDE_H

#include <QtCore/QDir>
#include <QtQml/qqml.h>
#include <QtQuick/QtQuick>
#include <qt5/QtQml/QQmlEngine>
#include <qt5/QtGui/QGuiApplication>
#include <qt5/QtQuick/QQuickView>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QUrl>

#include "MainWindow.h"

namespace panopticon
{

namespace ide
{

extern MainWindow* MAIN_WINDOW;

}

}

#endif // IDE_H
