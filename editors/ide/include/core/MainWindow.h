#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QDir>
#include <qt5/QtGui/QGuiApplication>
#include <QDebug>
#include <QCoreApplication>
#include <QWindow>
#include <QTextDocument>
#include <QObject>
#include <QGLWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QVector>
#include <QTimer>
#include <QGraphicsView>
#include <QPlainTextEdit>
#include <QMenuBar>
#include <QMenu>

#include "EditBuffer.h"
#include "SyntaxHighlighter.h"

namespace panopticon
{

namespace ide
{

class GlContext : public QGLContext
{
public:
    GlContext(QGLFormat format);
    virtual bool create(const QGLContext *shareContext = 0);
};

class GlWidget : public QGLWidget
{
    Q_OBJECT

public:

    GlWidget(QWidget* parent = 0);

    QString getRenderString();


public slots:
    void setRenderString(QString renderString);

protected:

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    QString renderString;
};

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

public:
    GraphicsScene();

    void drawBackground(QPainter *painter, const QRectF &rect);
    void drawForeground(QPainter *painter, const QRectF &rect);
    void updateFrame();
    void toggleTimer();

    QTimer updateTimer;
};

class MenuBar : public QMenuBar
{
    Q_OBJECT

public:

    MenuBar(QWidget* parent = 0);
    ~MenuBar();

public slots:

    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void closeFile();
    void closeAllFiles();
    void quit();

protected:

    QMenu *fileMenu, *sessionMenu, *editMenu, *languageMenu, *helpMenu;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void post(const QString& string);
    void postError(const QString& string);
    void newFile();
    void openFile();
    void saveFile();
    void saveFileAs();
    void closeFile();
    void closeAllFiles();
    void quit();

protected:

    void resizeEvent(QResizeEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void resizeComponents();
    void newEditBuffer();

    GlWidget glBackground;
    QVBoxLayout vLayout;
    QVector<EditBuffer*> editBuffers;
    EditBuffer* focusedBuffer;
    QMainWindow* window;
    QWidget* widget;
    QGraphicsView graphicsView;
    QTextEdit* postWindow;
    SyntaxHighlighter syntaxHighlighter;
    MenuBar menuBar;
};

} // ide namespace

} // panopticon namespace


#endif // MAINWINDOW_H
