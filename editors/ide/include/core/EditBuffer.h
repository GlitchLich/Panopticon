#ifndef EDITBUFFER_H
#define EDITBUFFER_H

#include <QTextEdit>

namespace panopticon
{

namespace ide
{

class EditBuffer : public QTextEdit
{
    Q_OBJECT

public:
    EditBuffer(QWidget* parent = 0);


protected:

};

} // ide namespace

} // panopticon namespace

#endif // EDITBUFFER_H
