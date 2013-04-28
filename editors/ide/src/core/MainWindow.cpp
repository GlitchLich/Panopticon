#include <QApplication>
#include <QDesktopWidget>
#include <QResizeEvent>
#include <qgl.h>
#include <QPalette>
#include <QScrollBar>
#include <QTextCursor>
#include "ide/include/core/EditBuffer.h"

#include "ide/include/style/StyleGlobals.h"
#include "ide/include/core/MainWindow.h"

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
    this->renderText(50, 50, renderString, mainFont);
}

////////////////////
/// GraphicsScene
////////////////////

GraphicsScene::GraphicsScene() :
    QGraphicsScene()
{
    // QObject::connect(&foregroundFpsTimer, SIGNAL(timeout()), this, SLOT(drawForegroundFrame()), Qt::QueuedConnection);
    QObject::connect(&updateTimer, SIGNAL(timeout()), this, SLOT(update()));
    updateTimer.start(33);
}


void GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    painter->beginNativePainting();
//    glClearColor((rand() % 300) / 1000.0, (rand() % 300) / 1000.0, (rand() % 300) / 1000.0, 1);
    glClearColor(0.1,0.1,0.125, 1);
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

//////////////////////////////////
/// MainWindow
//////////////////////////////////

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    glBackground(0),
    graphicsView(this),
    syntaxHighlighter(0)
{
    setGeometry(QApplication::desktop()->width() / 2 - 400, QApplication::desktop()->height() / 2 - 300, 800, 600);
    glBackground.setGeometry(this->geometry());
    setWindowTitle("Panopticon");
    setFont(mainFont);

    graphicsView.setViewport(new GlWidget());
    EditBuffer* buffer = new EditBuffer();

    buffer->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    buffer->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    buffer->setFrameShape(QTextEdit::NoFrame);
    buffer->setFrameShadow(QTextEdit::Plain);
    buffer->setAcceptRichText(true);
    focusedBuffer = buffer;
    graphicsView.setScene(new GraphicsScene());
    graphicsView.scene()->addWidget(buffer);
    graphicsView.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    editBuffers.push_back(buffer);
    postWindow = new QPlainTextEdit("__________\nPanopticon\n");
    postWindow->setFont(monoFont);
    postWindow->setReadOnly(true);
    postWindow->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    postWindow->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    postWindow->setFrameShape(QTextEdit::NoFrame);
    postWindow->setFrameShadow(QTextEdit::Plain);
    postWindow->moveCursor(QTextCursor::End);
    graphicsView.scene()->addWidget(postWindow);
    syntaxHighlighter.setDocument(focusedBuffer->document());
    // vLayout.addWidget(buffer);
    // glBackground.setL1ayout(&vLayout);

    resizeComponents();
    show();
    buffer->setFocus();
    buffer->grabKeyboard();
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < editBuffers.size(); ++i)
    {
        if(editBuffers.at(i) != focusedBuffer)
            delete editBuffers.at(i);
    }

    editBuffers.clear();
}

void MainWindow::post(const QString &string)
{
    postWindow->insertPlainText(string);
    postWindow->moveCursor(QTextCursor::End);
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    resizeComponents();
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
