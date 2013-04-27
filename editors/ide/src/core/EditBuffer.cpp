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
    /*
    QRect newGeometry = parent->geometry();
    newGeometry.setY(newGeometry.y() * 0.8);
    setGeometry(newGeometry);*/
    setFont(monoFont);
}

void EditBuffer::keyPressEvent(QKeyEvent *e)
{
    if((e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return) && e->modifiers() == Qt::ShiftModifier)
    {
        QString command;

        if(textCursor().selectedText().size() > 0)
            command = textCursor().selectedText();
        else
            command = textCursor().block().text();

        MAIN_WINDOW->post(command);

        if(panopticon::exec(command.toStdString()))
        {
            MAIN_WINDOW->post("SUCCESS!");
        }
    }

    else
    {
        QTextEdit::keyPressEvent(e);
    }
}

} // ide namespace

} // panopticon namespace
