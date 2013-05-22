#include <iostream>

#include <QKeyEvent>
#include <QFileDialog>
#include <QApplication>

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

/////////////////////
/// EditBuffer
////////////////////

EditBuffer::EditBuffer(unsigned int id, QWidget *parent) :
    QTextEdit(parent),
    id(id),
    proxy(0),
    unsavedEdits(false)
{
    init();
}

EditBuffer::EditBuffer(unsigned int id, QWidget *parent, const QString &fileName) :
    QTextEdit(parent),
    fileName(fileName),
    unsavedEdits(false),
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
            return;

        default:
            break;
        }
    }

    else if(e->key() == Qt::Key_F1)
    {
        MAIN_WINDOW->toggleOpenGL();
        return;
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

void EditBuffer::findCodeBlock()
{

}

void EditBuffer::executeCommand()
{
    QString command;
    std::string returnString;

    if(textCursor().selectedText().size() > 0)
        command = textCursor().selectedText();
    else
        command = textCursor().block().text();

    std::string string = command.toStdString();

    if(panopticon::exec(string, returnString))
    {
        Post(returnString.c_str());
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

} // ide namespace

} // panopticon namespace
