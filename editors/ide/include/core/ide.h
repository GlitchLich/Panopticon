#ifndef IDE_H
#define IDE_H

#include <QtCore/QDir>
#include <QtQml/qqml.h>
#include <QtQuick/QtQuick>
#include <QFile>
#include <QDebug>
#include <QCoreApplication>
#include <QUrl>
#include <QSettings>

#include "MainWindow.h"

namespace panopticon
{

namespace ide
{

extern MainWindow* MAIN_WINDOW;
extern QSettings* IDE_SETTINGS;
void Post(const QString& string);
void PostError(const QString& string);

}

}

#endif // IDE_H
