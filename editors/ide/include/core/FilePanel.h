#ifndef FILEPANEL_H
#define FILEPANEL_H

#include <QToolBar>
#include <QHBoxLayout>
#include <QToolButton>
#include <QMap>

#include "ide/include/core/EditBuffer.h"

namespace panopticon
{

namespace ide
{

class FilePanel : public QToolBar
{
    Q_OBJECT

public:

    FilePanel(QWidget* parent);

signals:
    void showEditBuffer(unsigned int buffer);

public slots:

    void addEditBuffer(unsigned int buffer);
    void setFileName(unsigned int buffer, const QString& fileName);
    void removeEditBuffer(unsigned int buffer);
    void fileButtonPressed();
    void checkButton(unsigned int buffer);

protected:

    QHBoxLayout layout;
    QMap<unsigned int, QToolButton*> fileButtons;
    unsigned int lastPressed;
};

} // ide namespace

} // panopticon namespace


#endif // FILEPANEL_H
