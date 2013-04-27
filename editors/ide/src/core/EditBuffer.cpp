#include <iostream>

#include <QKeyEvent>

#include "ide/include/core/EditBuffer.h"
#include "ide/include/style/StyleGlobals.h"
#include "ide/include/core/ide.h"
#include "Grammar/parse.h"

namespace panopticon
{

namespace ide
{

EditBuffer::EditBuffer(QWidget* parent) :
    QTextEdit(parent)
{
    setFont(monoFont);
}

void EditBuffer::keyPressEvent(QKeyEvent *e)
{
    if(
            ((e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) && e->modifiers() == Qt::ShiftModifier)
            ||
            ((e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) && e->modifiers() == Qt::ControlModifier)
        )
    {
        QString command;
        std::string returnString;

        if(textCursor().selectedText().size() > 0)
            command = textCursor().selectedText();
        else
            command = textCursor().block().text();


        if(panopticon::exec(command.toStdString(), returnString))
        {
            MAIN_WINDOW->post(returnString.c_str());
        }
    }

    else
    {
        QTextEdit::keyPressEvent(e);
    }
}

} // ide namespace

} // panopticon namespace
