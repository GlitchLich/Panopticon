#ifndef EDITBUFFER_H
#define EDITBUFFER_H

#include <QTextEdit>
#include <QFile>
#include <QDialog>
#include <QGraphicsProxyWidget>

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
    EditBuffer(unsigned int id, QWidget* parent = 0);
    EditBuffer(unsigned int id, QWidget *parent, const QString& fileName);

    void keyPressEvent(QKeyEvent *e);
    void open();
    void save();
    void saveAs();
    bool getUnsavedEdits();

    const QString& getFileName();
    const QString& getFilePath();
    unsigned int id;
    QGraphicsProxyWidget* proxy;

signals:
    void fileChanged(unsigned int id, const QString& fileName);

public slots:

    void edited();

protected:

    void executeCommand();

    QString fileName;
    QString filePath;
    QFile file;

private:

    bool unsavedEdits;
    void init();
    void loadFile();
};

} // ide namespace

} // panopticon namespace

#endif // EDITBUFFER_H
