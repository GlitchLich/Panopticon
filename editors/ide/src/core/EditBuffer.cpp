#include "ide/include/core/EditBuffer.h"
#include "ide/include/style/StyleGlobals.h"

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

} // ide namespace

} // panopticon namespace
