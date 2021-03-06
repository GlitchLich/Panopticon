#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QWindow>
#include <QTextDocument>
#include <QObject>
#include <QMessageBox>
#include <QGLWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QVector>
#include <QMap>
#include <QTimer>
#include <QGraphicsView>
#include <QPlainTextEdit>
#include <QMenuBar>
#include <QMenu>

#include "EditBuffer.h"
#include "SyntaxHighlighter.h"
#include "ide/include/core/FilePanel.h"

namespace panopticon
{

namespace ide
{

class CloseFileDialog : public QMessageBox
{
    Q_OBJECT

public:

    CloseFileDialog(const QString& fileName, QWidget* parent = 0);

protected:

    void keyPressEvent(QKeyEvent *event);
};

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
    void openFileFromMenu();
    void saveFile();
    void saveFileAs();
    void closeFile();
    void closeAllFiles();
    void quit();

    void updateRecentFiles();

    void incrementBuffer();
    void decrementBuffer();

    void evaluateCode();
    void toggleOpenGL();

    void about();

protected:

    QMenu *fileMenu, *recentMenu, *sessionMenu, *editMenu, *languageMenu, *helpMenu;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    EditBuffer* getFocusedBuffer();

public slots:
    void post(const QString& string);
    void postError(const QString& string);
    void newFile();
    void openFile();
    void openFile(const QString& filePath);
    void saveFile();
    void saveFileAs();
    bool closeFile(bool autospawn = true); // returns true if user agrees to close file
    bool closeAllFiles(); // returns true if user agrees to close all files
    void quit();
    void showEditBuffer(unsigned int buffer);
    void incrementBuffer();
    void decrementBuffer();
    void toggleOpenGL();
    void evaluateCode();

protected:

    void resizeEvent(QResizeEvent *e);
    void keyPressEvent(QKeyEvent *e);
    void resizeComponents();
    void newEditBuffer();
    void prCloseFile(bool autospawn = true);

    GlWidget glBackground;
    QVBoxLayout vLayout;
    QMap<unsigned int, EditBuffer*> editBuffers;
    EditBuffer* focusedBuffer;
    QMainWindow* window;
    QWidget* widget;
    QGraphicsView graphicsView;
    QTextEdit* postWindow;
    SyntaxHighlighter syntaxHighlighter;
    MenuBar menuBar;
    unsigned int bufferCount;
    FilePanel filePanel;
    bool openGL;
};

} // ide namespace

} // panopticon namespace


#endif // MAINWINDOW_H
