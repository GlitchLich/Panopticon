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

    QTimer updateTimer;
};


class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void post(const QString& string);

protected:

    void resizeEvent(QResizeEvent *e);
    void resizeComponents();

    GlWidget glBackground;
    QVBoxLayout vLayout;
    QVector<EditBuffer*> editBuffers;
    EditBuffer* focusedBuffer;
    QMainWindow* window;
    QWidget* widget;
    QGraphicsView graphicsView;
    QPlainTextEdit* postWindow;
    SyntaxHighlighter syntaxHighlighter;
};

} // ide namespace

} // panopticon namespace


#endif // MAINWINDOW_H
