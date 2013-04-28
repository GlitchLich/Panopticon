#include <QApplication>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <qgl.h>
#include <QPalette>
#include <QScrollBar>
#include <QTextCursor>
#include <QDialog>
#include <QKeySequence>

#include "ide/include/core/EditBuffer.h"
#include "ide/include/style/StyleGlobals.h"
#include "ide/include/core/MainWindow.h"
#include "ide/include/core/ide.h"

namespace panopticon
{

namespace ide
{

/////////////////////
/// GlContext
/////////////////////

GlContext::GlContext(QGLFormat format) :
    QGLContext(format)
{

}

bool GlContext::create(const QGLContext *shareContext)
{
    if(QGLContext::create(shareContext))
    {
        makeCurrent();

        glClearColor(1, 0, 0, 1);
        glEnable(GL_DEPTH_TEST);

        doneCurrent();

        return true;
    }

    return false;
}

///////////////////////
/// GLWidget
///////////////////////

GlWidget::GlWidget(QWidget* parent) :
    QGLWidget(new GlContext(QGLFormat(QGL::SampleBuffers)))
{
    renderString = "Hello World!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
}

void GlWidget::setRenderString(QString renderString)
{
    this->renderString = renderString;
}

QString GlWidget::getRenderString()
{
    return renderString;
}

void GlWidget::initializeGL()
{
    glClearColor(1, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void GlWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glClearColor(1, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
}

void GlWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3b(0, 0, 0);
    this->renderText(50, 50, renderString, ide::style->mainFont);
}

////////////////////
/// GraphicsScene
////////////////////

GraphicsScene::GraphicsScene() :
    QGraphicsScene()
{
    // QObject::connect(&foregroundFpsTimer, SIGNAL(timeout()), this, SLOT(drawForegroundFrame()), Qt::QueuedConnection);
    QObject::connect(&updateTimer, SIGNAL(timeout()), this, SLOT(update()));
}


void GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->beginNativePainting();
    // glClearColor(0.2, 0.06, 0.15, 1);
    glClearColor(ide::style->clearR(), ide::style->clearG(), ide::style->clearB(), ide::style->clearA());
    glClear(GL_COLOR_BUFFER_BIT);
    painter->endNativePainting();
}

void GraphicsScene::drawForeground(QPainter *painter, const QRectF &rect)
{

}

void GraphicsScene::updateFrame()
{
    update();
    // invalidate(sceneRect());
}

void GraphicsScene::toggleTimer()
{
    if(updateTimer.isActive())
        updateTimer.stop();
    else
        updateTimer.start(33);
}

//////////////////
// MenuBar
//////////////////

MenuBar::MenuBar(QWidget *parent) :
    QMenuBar(parent)
{
    fileMenu = new QMenu("File");
    fileMenu->addAction("New", this, SLOT(newFile()), QKeySequence(Qt::Key_Control, Qt::Key_N));
    fileMenu->addAction("Open", this, SLOT(openFile()), QKeySequence(Qt::Key_Control, Qt::Key_O));
    fileMenu->addAction("Open Recent");
    fileMenu->addAction("Save", this, SLOT(saveFile()), QKeySequence(Qt::Key_Control, Qt::Key_S));
    fileMenu->addAction("Save As...", this, SLOT(saveFileAs()), QKeySequence(Qt::Key_Shift, Qt::Key_Control, Qt::Key_S));
    fileMenu->addSeparator();
    fileMenu->addAction("Close", this, SLOT(closeFile()), QKeySequence(Qt::Key_Control, Qt::Key_W));
    fileMenu->addAction("Close All", this, SLOT(closeAllFiles()), QKeySequence(Qt::Key_Shift, Qt::Key_Control, Qt::Key_W));
    fileMenu->addSeparator();
    fileMenu->addAction("Quit", this, SLOT(quit()), QKeySequence(Qt::Key_Control, Qt::Key_Q));

    sessionMenu = new QMenu("Session");



    editMenu = new QMenu("Edit");



    languageMenu = new QMenu("Language");



    helpMenu = new QMenu("Help");

    addMenu(fileMenu);
    addMenu(sessionMenu);
    addMenu(editMenu);
    addMenu(languageMenu);
    addMenu(helpMenu);
}

MenuBar::~MenuBar()
{

}

void MenuBar::newFile()
{
    MAIN_WINDOW->newFile();
}

void MenuBar::openFile()
{
    MAIN_WINDOW->openFile();
}

void MenuBar::saveFile()
{
    MAIN_WINDOW->saveFile();
}

void MenuBar::saveFileAs()
{
    MAIN_WINDOW->saveFileAs();
}

void MenuBar::closeFile()
{
    MAIN_WINDOW->closeFile();
}

void MenuBar::closeAllFiles()
{
    MAIN_WINDOW->closeAllFiles();
}

void MenuBar::quit()
{
    MAIN_WINDOW->quit();
}


//////////////////////////////////
/// MainWindow
//////////////////////////////////

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    menuBar(this),
    glBackground(0),
    graphicsView(this),
    syntaxHighlighter(0),
    focusedBuffer(0)
{
    setGeometry(QApplication::desktop()->width() / 2 - 450, QApplication::desktop()->height() / 2 - 250, 900, 500);
    glBackground.setGeometry(this->geometry());
    setWindowTitle("Panopticon");
    setFont(ide::style->mainFont);
    graphicsView.setViewport(new GlWidget());
    graphicsView.setScene(new GraphicsScene());
    newEditBuffer();
    graphicsView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    postWindow = new QPlainTextEdit("__________\nPanopticon\n");
    postWindow->setFont(ide::style->monoFont);
    postWindow->setReadOnly(true);
    // postWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    postWindow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    postWindow->setFrameShape(QTextEdit::NoFrame);
    postWindow->setFrameShadow(QTextEdit::Plain);
    postWindow->moveCursor(QTextCursor::End);
    graphicsView.scene()->addWidget(postWindow);
    syntaxHighlighter.setDocument(focusedBuffer->document());
    // vLayout.addWidget(buffer);
    // glBackground.setL1ayout(&vLayout);

    menuBar.hide();
    resizeComponents();
    show();
}

MainWindow::~MainWindow()
{
    /*
    for(int i = 0; i < editBuffers.size(); ++i)
    {
        if(editBuffers.at(i) != focusedBuffer)
            delete editBuffers.at(i);
    }*/

    editBuffers.clear();
}

void MainWindow::post(const QString &string)
{
    postWindow->insertPlainText(string);
    postWindow->moveCursor(QTextCursor::End);
}

void MainWindow::newFile()
{
    newEditBuffer();
}

void MainWindow::openFile()
{
    newEditBuffer();
    focusedBuffer->open();
}

void MainWindow::saveFile()
{
    focusedBuffer->save();
}

void MainWindow::saveFileAs()
{
    focusedBuffer->saveAs();
}

void MainWindow::closeFile()
{
    /*
    if(focusedBuffer)
    {
        if(focusedBuffer->getUnsavedEdits())
        {
            QDialog closeDialog;

            closeDialog.

            closeDialog.show();
            closeDialog.raise();
            closeDialog.setModal(true);
        }
    }

    for(unsigned int i = 0; i < editBuffers.size(); ++i)
    {
        if(editBuffers.at(i) == focusedBuffer)
        {
            if()
        }
    }*/
}

void MainWindow::closeAllFiles()
{

}

void MainWindow::quit()
{
    QApplication::quit();
}

void MainWindow::newEditBuffer()
{
    if(focusedBuffer)
        focusedBuffer->hide();

    EditBuffer* buffer = new EditBuffer();
    buffer->setGeometry(0, 0, width(), (double) height() * 0.8);
    syntaxHighlighter.setDocument(buffer->document());
    buffer->setFocus();
    buffer->grabKeyboard();
    graphicsView.scene()->addWidget(buffer);
    editBuffers.push_back(buffer);
    focusedBuffer = buffer;
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    resizeComponents();
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    if((e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
            && (e->modifiers() == Qt::ShiftModifier || e->modifiers() == Qt::ControlModifier))
    {
        ((GraphicsScene*) graphicsView.scene())->toggleTimer();
    }

    else
    {
        QMainWindow::keyPressEvent(e);
    }
}

void MainWindow::resizeComponents()
{
    graphicsView.setGeometry(0, 0, width(), height());

    for(int i = 0; i < editBuffers.size(); ++i)
    {
       editBuffers.at(i)->setGeometry(0, 0, width(), (double) height() * 0.8);
    }

    postWindow->setGeometry(0, (double) height() * 0.8, width(), (double) height() * 0.2);
}

} // ide namespace

} // panopticon namespace
