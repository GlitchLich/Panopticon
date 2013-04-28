#ifndef EDITBUFFER_H
#define EDITBUFFER_H

#include <QTextEdit>
#include <QFile>
#include <QDialog>

namespace panopticon
{

namespace ide
{

class BufferCloseDialog : QDialog
{
    Q_OBJECT

public:

    BufferCloseDialog();
};

class EditBuffer : public QTextEdit
{
    Q_OBJECT

public:
    EditBuffer(QWidget* parent = 0);
    EditBuffer(QWidget *parent, const QString& fileName);

    void keyPressEvent(QKeyEvent *e);
    void open();
    void save();
    void saveAs();
    bool getUnsavedEdits();

    const QString& getFileName();

public slots:

    void edited();

protected:

    void executeCommand();

    QString fileName;
    QFile file;

private:

    bool unsavedEdits;
    void init();
    void loadFile();
};

} // ide namespace

} // panopticon namespace

#endif // EDITBUFFER_H
