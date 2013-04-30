#include <QApplication>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <qgl.h>
#include <QPalette>
#include <QScrollBar>
#include <QTextCursor>
#include <QDialog>
#include<QMessageBox>
#include <QLabel>
#include <QKeySequence>
#include <QGraphicsProxyWidget>
#include <QPushButton>

#include "ide/include/core/EditBuffer.h"
#include "ide/include/style/StyleGlobals.h"
#include "ide/include/core/MainWindow.h"
#include "ide/include/core/ide.h"

namespace panopticon
{

namespace ide
{

/////////////////////
// CloseFileDialog
/////////////////////
CloseFileDialog::CloseFileDialog(const QString &fileName, QWidget *parent) :
    QMessageBox(parent)
{
    setText("The document has been modified.");
    setInformativeText("Save changes to \"" + fileName + "\" before closing?");
    setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    setWindowFlags(Qt::Window);
    grabKeyboard();
    setDefaultButton(QMessageBox::Save);
}

void CloseFileDialog::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
    case Qt::Key_Left:
        focusPreviousChild();
        return;

    case Qt::Key_Right:
        focusNextChild();
        return;

    default:
        break;
    }

    QMessageBox::keyPressEvent(event);
}

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
    editMenu->addAction("Previous Buffer", this, SLOT(decrementBuffer()), QKeySequence(Qt::ShiftModifier, Qt::LeftArrow));
    editMenu->addAction("Next Buffer", this, SLOT(incrementBuffer()), QKeySequence(Qt::ShiftModifier, Qt::RightArrow));

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

void MenuBar::incrementBuffer()
{
    MAIN_WINDOW->incrementBuffer();
}

void MenuBar::decrementBuffer()
{
    MAIN_WINDOW->decrementBuffer();
}


//////////////////////////////////
/// MainWindow
//////////////////////////////////

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    menuBar(this),
    filePanel(0),
    glBackground(0),
    syntaxHighlighter(0),
    focusedBuffer(0)
{
    setGeometry(QApplication::desktop()->width() / 2 - 450, QApplication::desktop()->height() / 2 - 250, 900, 500);
    glBackground.setGeometry(this->geometry());
    setWindowTitle("Panopticon");
    setFont(ide::style->mainFont);
    graphicsView.setViewport(new GlWidget());
    graphicsView.setScene(new GraphicsScene());
    graphicsView.setFont(ide::style->monoFont);
    newEditBuffer();
    graphicsView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    postWindow = new QTextEdit();
    postWindow->setFont(ide::style->monoFont);
    postWindow->setReadOnly(false);
    postWindow->setCursorWidth(0);
    // postWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    postWindow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    postWindow->setFrameShape(QTextEdit::NoFrame);
    postWindow->setFrameShadow(QTextEdit::Plain);
    postWindow->moveCursor(QTextCursor::End);
    post("__________\nPanopticon\n");
    graphicsView.scene()->addWidget(postWindow);
    graphicsView.setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
    syntaxHighlighter.setDocument(focusedBuffer->document());
    QObject::connect(&filePanel, SIGNAL(showEditBuffer(uint)), this, SLOT(showEditBuffer(uint)));
    // vLayout.addWidget(buffer);
    // glBackground.setL1ayout(&vLayout);
    menuBar.hide();
    resizeComponents();
    focusedBuffer->setFocus();
    addToolBar(Qt::BottomToolBarArea, &filePanel);
    setCentralWidget(&graphicsView);
    // setLayout(&vLayout);
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

void MainWindow::post(const QString& string)
{
    postWindow->setCurrentCharFormat(ide::style->printFormat);
    postWindow->insertPlainText(string);
    postWindow->moveCursor(QTextCursor::End);
}

void MainWindow::postError(const QString& string)
{
    postWindow->setCurrentCharFormat(ide::style->printErrorFormat);
    postWindow->insertPlainText(string);
    postWindow->moveCursor(QTextCursor::End);
}

void MainWindow::newFile()
{
    newEditBuffer();
    focusedBuffer->grabKeyboard();
}

void MainWindow::openFile()
{
    if(focusedBuffer->getFileName().length() > 0)
        newEditBuffer();

    focusedBuffer->open();
    focusedBuffer->grabKeyboard();
}

void MainWindow::saveFile()
{
    focusedBuffer->save();
    focusedBuffer->grabKeyboard();
}

void MainWindow::saveFileAs()
{
    focusedBuffer->saveAs();
    focusedBuffer->grabKeyboard();
}

bool MainWindow::closeFile(bool autospawn)
{
    bool fileClosed = true;

    if(focusedBuffer)
    {
        if(focusedBuffer->getUnsavedEdits())
        {
            CloseFileDialog msgBox(focusedBuffer->getFileName());
            int ret = msgBox.exec();

            switch(ret)
            {
            case QMessageBox::Save:
                saveFile();
                prCloseFile(autospawn);
                break;

            case QMessageBox::Discard:
                prCloseFile(autospawn);
                break;

            case QMessageBox::Cancel:
                fileClosed = false;
                focusedBuffer->setFocus();
                focusedBuffer->show();
                focusedBuffer->grabKeyboard();
                break;
            }
        }

        else
        {
            prCloseFile(autospawn);
        }
    }

    return fileClosed;
}

bool MainWindow::closeAllFiles()
{
    while(editBuffers.size())
    {
        if(!closeFile(false))
        {
            return false;
        }
    }

    focusedBuffer = 0;
    return true;
}

void MainWindow::quit()
{
    bool doQuit = true;

    doQuit = closeAllFiles();

    if(doQuit)
        QApplication::quit();
}

void MainWindow::showEditBuffer(unsigned int buffer)
{
    if(editBuffers.contains(buffer))
    {
        if(focusedBuffer)
            focusedBuffer->hide();

        focusedBuffer = editBuffers[buffer];
        syntaxHighlighter.setDocument(focusedBuffer->document());
        focusedBuffer->setFocus();
        focusedBuffer->show();
        focusedBuffer->grabKeyboard();
    }

    else
    {
        PostError("Unable to find edit buffer.");
    }
}

void MainWindow::incrementBuffer()
{
    QMap<unsigned int, EditBuffer*>::iterator nextBuffer = editBuffers.lowerBound(focusedBuffer->id + 1);

    if(nextBuffer != editBuffers.end())
    {
        showEditBuffer(nextBuffer.key());
        filePanel.checkButton(nextBuffer.key());
    }
}

void MainWindow::decrementBuffer()
{
    QMap<unsigned int, EditBuffer*>::iterator previousBuffer = editBuffers.find(focusedBuffer->id);
    if(previousBuffer != editBuffers.begin())
    {
        --previousBuffer;
        showEditBuffer(previousBuffer.key());
        filePanel.checkButton(previousBuffer.key());
    }
}

void MainWindow::newEditBuffer()
{
    if(focusedBuffer)
        focusedBuffer->hide();

    EditBuffer* buffer = new EditBuffer(bufferCount);
    buffer->setGeometry(0, 0, width(), (double) height() * 0.8);
    syntaxHighlighter.setDocument(buffer->document());
    buffer->setFocus();
    buffer->setTabChangesFocus(false);
    buffer->setFont(ide::style->monoFont);
    buffer->grabKeyboard();
    buffer->proxy = graphicsView.scene()->addWidget(buffer);
    editBuffers[bufferCount] = buffer;
    buffer->connect(buffer, SIGNAL(fileChanged(uint,QString)), &filePanel, SLOT(setFileName(uint,QString)));
    filePanel.addEditBuffer(bufferCount);
    ++bufferCount;
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
    // graphicsView.setGeometry(0, 0, width(), height());

    foreach(EditBuffer* buffer, editBuffers)
    {
        buffer->setGeometry(0, 0, width(), (double) height() * 0.8);
    }

    postWindow->setGeometry(0, (double) height() * 0.8, width(), (double) height() * 0.19);
}

void MainWindow::prCloseFile(bool autospawn)
{
    unsigned int id = focusedBuffer->id;
    filePanel.removeEditBuffer(id);
    editBuffers.remove(id);
    graphicsView.scene()->removeItem(focusedBuffer->proxy);
    EditBuffer* buffer = focusedBuffer;
    buffer->releaseKeyboard();
    buffer->releaseMouse();
    buffer->hide();
    buffer->disconnect();

    if(editBuffers.size() > 0)
    {
        QMap<unsigned int, EditBuffer*>::iterator nextBuffer = editBuffers.lowerBound(id);

        if(nextBuffer == editBuffers.end())
        {
            nextBuffer = --editBuffers.end();
        }

        if(nextBuffer != editBuffers.end())
        {
            focusedBuffer = nextBuffer.value();
            syntaxHighlighter.setDocument(focusedBuffer->document());
            focusedBuffer->setFocus();
            focusedBuffer->grabKeyboard();
            graphicsView.scene()->setFocusItem(focusedBuffer->proxy);
            filePanel.checkButton(focusedBuffer->id);
            showEditBuffer(focusedBuffer->id);
        }
    }

    else if(autospawn)
    {
        newFile();
        showEditBuffer(focusedBuffer->id);
    }

    delete buffer;
}

} // ide namespace

} // panopticon namespace
