#include <iostream>

#include <QKeyEvent>
#include <QFileDialog>
#include <QApplication>

#include "ide/include/core/EditBuffer.h"
#include "ide/include/style/StyleGlobals.h"
#include "ide/include/core/ide.h"
#include "Grammar/parse.h"

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

EditBuffer::EditBuffer(QWidget* parent) :
    QTextEdit(parent)
{
    init();
}

EditBuffer::EditBuffer(QWidget *parent, const QString &fileName) :
    QTextEdit(parent),
    fileName(fileName),
    unsavedEdits(false)
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
    connect(this, SIGNAL(textChanged()), this, SLOT(edited()), Qt::QueuedConnection);
}

void EditBuffer::keyPressEvent(QKeyEvent *e)
{
    if(e->modifiers() == Qt::ControlModifier)
    {
        switch(e->key())
        {
        case Qt::Key_Enter:
        case Qt::Key_Return:
            executeCommand();
            return;

        case Qt::Key_S:
            save();
            return;

        case Qt::Key_O:
            open();
            return;

        case Qt::Key_Q:
            QApplication::quit();
            return;

        default:
            break;
        }
    }

    else if(e->modifiers() == Qt::ShiftModifier)
    {
        if(e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
        {
            executeCommand();
            return;
        }
    }

    QTextEdit::keyPressEvent(e);
}

void EditBuffer::open()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QApplication::applicationDirPath(), tr("*.optic"));
    loadFile();
}

void EditBuffer::save()
{
    if(fileName.length() == 0)
    {
        fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QApplication::applicationDirPath(), tr("*.optic"));
        file.setFileName(fileName);
    }

    if(file.open(QIODevice::WriteOnly))
    {
        if(!file.write(document()->toPlainText().toLocal8Bit()))
        {
            Post("An error occured while saving file " + fileName + "\n");
        }

        else
        {
            Post("File saved.");
        }

        file.close();
        unsavedEdits = false;
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
            Post("File saved.");
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
    return unsavedEdits;
}

void EditBuffer::edited()
{
    unsavedEdits = true;
}

void EditBuffer::executeCommand()
{
    QString command;
    std::string returnString;

    if(textCursor().selectedText().size() > 0)
        command = textCursor().selectedText();
    else
        command = textCursor().block().text();


    if(panopticon::exec(command.toStdString(), returnString))
    {
        Post(returnString.c_str());
    }

    else
    {
        Post("Parse failed.\n");
    }
}

void EditBuffer::loadFile()
{
    file.setFileName(fileName);

    if(file.open(QIODevice::ReadOnly))
    {
        clear();
        QString text = file.readAll();
        setText(text);
        file.close();
    }

    else
    {
        Post("No file opened.\n");
    }
}

} // ide namespace

} // panopticon namespace
