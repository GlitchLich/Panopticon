#include <iostream>

#include <QKeyEvent>
#include <QFileDialog>
#include <QApplication>
#include <QLabel>

#include "ide/include/core/EditBuffer.h"
#include "ide/include/style/StyleGlobals.h"
#include "ide/include/core/ide.h"
#include "Grammar/parse.h"
#include "ide/include/core/Session.h"

namespace panopticon
{

namespace ide
{

///////////////////////
/// BufferCloseDialog
///////////////////////

BufferCloseDialog::BufferCloseDialog()
{

}

////////////////////////
/// CodeBlockBackground
////////////////////////

CodeBlockBackground::CodeBlockBackground(EditBuffer* parent) :
    QWidget(parent->viewport()->parentWidget()),
    editBuffer(parent)
{
    init();
}

void CodeBlockBackground::init()
{
    setUpdatesEnabled(true);
    blinkAmount = 0;
    setGeometry(codeGeometry());
    fill = QPixmap(size());
    fill.fill(QColor(255, 255, 255, 10));
    lower();
    blinkTimer.connect(&blinkTimer, SIGNAL(timeout()), this, SLOT(decrementBlinkAlpha()), Qt::QueuedConnection);
}

void CodeBlockBackground::colorizeBlock()
{
    setGeometry(codeGeometry());
    qDebug() << "CursorRect" << geometry();
    fill = QPixmap(geometry().size());
    fill.fill(QColor(255, 255, 255, 10 + blinkAmount));
    setHidden(false);
}

void CodeBlockBackground::blink()
{
    blinkAmount = 66;
    blinkTimer.start(33);
}

void CodeBlockBackground::decrementBlinkAlpha()
{
    blinkAmount -= 3;
    fill = QPixmap(geometry().size());
    fill.fill(QColor(255, 255, 255, 10 + blinkAmount));
    MAIN_WINDOW->centralWidget()->update(geometry());

    if(blinkAmount <= 0)
        blinkTimer.stop();
}

void CodeBlockBackground::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), fill);
}

QRect CodeBlockBackground::codeGeometry()
{
    std::cout << "LineSpacing: " << ide::style->monoFontMetrics.lineSpacing() << std::endl;
    QTextDocument* document = editBuffer->document();
    QTextCursor cursor = editBuffer->textCursor();
    QRect cursorRect = editBuffer->cursorRect(cursor);
    QTextBlock startBlock = document->findBlockByNumber(editBuffer->startBlockNumber());
    QTextBlock endBlock = document->findBlockByNumber(editBuffer->endBlockNumber());
    QTextBlock cursorBlock = cursor.block();
    int startOffset = startBlock.firstLineNumber() - cursorBlock.firstLineNumber();
    int endOffset;

    if(cursorBlock.blockNumber() != endBlock.blockNumber())
        endOffset = cursorBlock.lineCount() + endBlock.lineCount();
    else
        endOffset = cursorBlock.lineCount();

    unsigned int startLine = startBlock.firstLineNumber();
    unsigned int endLine = endBlock.firstLineNumber() + endBlock.lineCount();

    std::cout << "CodeBlock Number of Lines: " << (endLine - startLine) << std::endl;

    return QRect(
        0, // Always 0 because every code block must begin unindented
        cursorRect.top() + (startOffset * (ide::style->monoFontMetrics.lineSpacing() + 1)),
        this->editBuffer->width(),
        (endLine - startLine) * (ide::style->monoFontMetrics.lineSpacing() + 1)
    );
}

/////////////////////
/// EditBuffer
/////////////////////

EditBuffer::EditBuffer(unsigned int id, QWidget *parent) :
    QTextEdit(parent),
    codeBlockBackground(this),
    id(id),
    proxy(0),
    unsavedEdits(false)
{
    init();
}

EditBuffer::EditBuffer(unsigned int id, QWidget *parent, const QString &fileName) :
    QTextEdit(parent),
    codeBlockBackground(this),
    fileName(fileName),
    unsavedEdits(false),
    proxy(0),
    id(id)
{
    init();
    loadFile();
}

void EditBuffer::init()
{
    setFont(ide::style->monoFont);
    // setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QTextEdit::NoFrame);
    setFrameShadow(QTextEdit::Plain);
    setAcceptRichText(false);
    fileName = "";
    connect(document(), SIGNAL(contentsChanged()), this, SLOT(edited()), Qt::QueuedConnection);
    panopticon::init();
    unsavedEdits = false;
    document()->setModified(false);
    const int tabStop = 4;  // 4 characters
    QFontMetrics metrics(ide::style->monoFont);
    this->setTabStopWidth(tabStop * metrics.width(' '));
    previousStartBlock = previousEndBlock = startBlock = endBlock = 0;
    QObject::connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(updateCodeBlock()));
    codeBlockBackground.init();
    codeBlockBackground.colorizeBlock();
    codeBlockBackground.show();
}

bool isWhiteSpace(QString string)
{
    return string.simplified().replace(" ", "").length() == 0;
}

void EditBuffer::scanCodeBlock(QString* code, ScanDirection direction)
{
    unsigned int currentBlock = textCursor().blockNumber();

    if(direction == Forward)
        currentBlock += 1;
    else
        currentBlock -= 1;

    while(true)
    {
        QTextBlock block = document()->findBlockByNumber(currentBlock);

        if(isWhiteSpace(block.text()))
        {
            endBlock = currentBlock - 1;
            return;
        }

        if(block.text().size() > 0 && block.text().at(0).isSpace())
        {
            if(direction == Forward)
                code->append("\n" + block.text());
            else if(direction == Backward)
                code->prepend(block.text() + "\n");
        }

        else
        {
            break;
        }

        if(direction == Forward)
            ++currentBlock;
        else if(direction == Backward)
            --currentBlock;
    }

    if(direction == Backward && currentBlock >= 0)
    {
        code->prepend(document()->findBlockByNumber(currentBlock).text() + "\n");
        startBlock = currentBlock;
    }

    else if(currentBlock < 0)
    {
        startBlock = 0;
    }

    else if(direction == Forward)
    {
        endBlock = currentBlock - 1;
    }
}

void EditBuffer::updateCodeBlock()
{
    std::cout << "Update code block" << std::endl;
    QTextCursor cursor = textCursor();
    previousStartBlock = startBlock;
    previousEndBlock = endBlock;
    startBlock = endBlock = cursor.blockNumber();

    // If code has been directly selected by the user use that, other wise just the current block
    if(cursor.selectedText().size() > 0)
    {
        codeBlock = cursor.selectedText();
    }

    else
    {
        QString code = cursor.block().text();

        // Note whitespace
        if(!isWhiteSpace(code))
        {
            // Check to see if we're not at the beginning of the doc and we ARE indented
            if(cursor.blockNumber() > 0 && (code.startsWith(" ") || code.startsWith("	")))
            {
                std::cout << "Scan Backwards" << std::endl;
                // Look for the beginning of this code block, prepending code when appropriate
                scanCodeBlock(&code, Backward);
            }

            // Check to see if it isn't at the end of the doc and isn't a comment
            if(cursor.blockNumber() != (document()->blockCount() - 1) && !code.startsWith("//"))
            {
                std::cout << "Scan Forwards" << std::endl;
                // Look for the end of this code block, appending code where appropriate
                scanCodeBlock(&code, Forward);
            }
        }

        codeBlock = code;
    }

    codeBlockBackground.colorizeBlock();
    std::cout << codeBlock.toStdString() << std::endl;
}

void EditBuffer::keyPressEvent(QKeyEvent *e)
{
    if(e->modifiers() == Qt::ALT)
    {
        switch(e->key())
        {
        case Qt::Key_Left:
        case Qt::Key_Up:
            MAIN_WINDOW->decrementBuffer();
            return;

        case Qt::Key_Down:
        case Qt::Key_Right:
            MAIN_WINDOW->incrementBuffer();
            return;

        default:
            break;
        }
    }

    else if(e->modifiers() == Qt::ControlModifier)
    {
        switch(e->key())
        {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            executeCommand();
            return;

        case Qt::Key_N:
            MAIN_WINDOW->newFile();
            return;

        case Qt::Key_S:
            MAIN_WINDOW->saveFile();
            return;

        case Qt::Key_O:
            MAIN_WINDOW->openFile();
            return;

        case Qt::Key_Q:
            MAIN_WINDOW->quit();
            return;

        case Qt::Key_W:
            MAIN_WINDOW->closeFile();
            return;

        case Qt::Key_F1:
            MAIN_WINDOW->toggleOpenGL();
            break;

        case Qt::Key_Left:
        case Qt::Key_Right:
        case Qt::Key_Up:
        case Qt::Key_Down:
            // updateCodeBlock();
            break;

        default:
            break;
        }
    }

    else if(e->modifiers() == Qt::ShiftModifier)
    {
        switch(e->key())
        {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            executeCommand();
            // std::cout << textCursor()
            return;

        default:
            break;
        }
    }

    QTextEdit::keyPressEvent(e);
}

void EditBuffer::open(QString path)
{
    if(path.size() > 0)
        filePath = path;
    else
        filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QApplication::applicationDirPath(), tr("*.optic"));

    fileName = filePath.mid(filePath.lastIndexOf("/") + 1);
    loadFile();
}

void EditBuffer::mousePressEvent(QMouseEvent *e)
{
    // updateCodeBlock();
    QTextEdit::mousePressEvent(e);
}

void EditBuffer::wheelEvent(QWheelEvent *e)
{
    codeBlockBackground.setHidden(true);
    QTextEdit::wheelEvent(e);
}

void EditBuffer::scrollContentsBy(int dx, int dy)
{
    codeBlockBackground.setHidden(true);
    QTextEdit::scrollContentsBy(dx, dy);
}

void EditBuffer::save()
{
    if(fileName.length() == 0)
    {
        filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QApplication::applicationDirPath(), tr("*.optic"));
        fileName = filePath.mid(filePath.lastIndexOf("/") + 1);
        file.setFileName(filePath);
    }

    if(file.open(QIODevice::WriteOnly))
    {
        if(!file.write(document()->toPlainText().toLocal8Bit()))
        {
            Post("An error occured while saving file " + fileName + "\n");
        }

        else
        {
            Post("File saved.\n");
        }

        file.close();
        unsavedEdits = false;
        document()->setModified(false);
        emit fileChanged(id, fileName);
    }

    else
    {
        Post("File not saved.\n");
    }
}

void EditBuffer::saveAs()
{
    QFile newFile;
    QString newFileName = QFileDialog::getSaveFileName(this, tr("Save File"), QApplication::applicationDirPath(), tr("*.optic"));
    newFile.setFileName(newFileName);
    if(newFile.open(QIODevice::WriteOnly))
    {
        if(!newFile.write(document()->toPlainText().toLocal8Bit()))
        {
            Post("An error occured while saving file " + fileName + "\n");
        }

        else
        {
            Post("File saved.\n");
        }

        newFile.close();
    }

    else
    {
        Post("File not saved.\n");
    }
}

bool EditBuffer::getUnsavedEdits()
{
    return unsavedEdits && document()->isModified();
}

void EditBuffer::edited()
{
    unsavedEdits = true;
}

void EditBuffer::executeCommand()
{
    // updateCodeBlock();
    // QString command;
    std::string returnString;


    /*
    if(textCursor().selectedText().size() > 0)
        command = textCursor().selectedText();
    else
        command = textCursor().block().text();*/

    std::string string = codeBlock.toStdString();

    if(panopticon::exec(string, returnString))
    {
        Post(returnString.c_str());
        codeBlockBackground.blink();
    }

    else
    {
        PostError(returnString.c_str());
    }

}

void EditBuffer::loadFile()
{
    file.setFileName(filePath);

    if(file.open(QIODevice::ReadOnly))
    {
        clear();
        QString text = file.readAll();
        setText(text);
        file.close();
        unsavedEdits = false;
        document()->setModified(false);
        Session::pushRecentFile(filePath);
        emit fileChanged(id, fileName);
    }

    else
    {
        Post("No file opened.\n");
    }
}

const QString& EditBuffer::getFileName()
{
    return fileName;
}

const QString& EditBuffer::getFilePath()
{
    return filePath;
}

unsigned int EditBuffer::startBlockNumber()
{
    return startBlock;
}

unsigned int EditBuffer::endBlockNumber()
{
    return endBlock;
}

} // ide namespace

} // panopticon namespace
