#ifndef EDITBUFFER_H
#define EDITBUFFER_H

#include <QTextEdit>
#include <QFile>
#include <QDialog>
#include <QGraphicsProxyWidget>
#include <QPixmap>
#include <QTimer>

namespace panopticon
{

namespace ide
{

class EditBuffer; // Forward declaration

class BufferCloseDialog : QDialog
{
    Q_OBJECT

public:

    BufferCloseDialog();
};

class CodeBlockBackground : public QWidget
{
    Q_OBJECT

public:

    explicit CodeBlockBackground(EditBuffer* parent = 0);
    void init(); // Setup, called from EditBuffer::init

    void colorizeBlock();
    void blink();

    void paintEvent(QPaintEvent *);

public slots:

    void decrementBlinkAlpha();

protected:

    QRect codeGeometry();

    QRect currentCodeRect;
    EditBuffer* editBuffer;
    QPixmap fill;
    unsigned int blinkAmount;
    QTimer blinkTimer;
};

class EditBuffer : public QTextEdit
{
    Q_OBJECT

public:

    EditBuffer(unsigned int id, QWidget* parent = 0);
    EditBuffer(unsigned int id, QWidget *parent, const QString& fileName);

    void keyPressEvent(QKeyEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void scrollContentsBy(int dx, int dy);
    void open(QString path = "");
    void save();
    void saveAs();
    bool getUnsavedEdits();

    const QString& getFileName();
    const QString& getFilePath();
    unsigned int startBlockNumber();
    unsigned int endBlockNumber();
    unsigned int id;
    QGraphicsProxyWidget* proxy;

    enum ScanDirection
    {
        Forward,
        Backward
    };

signals:

    void fileChanged(unsigned int id, const QString& fileName);

public slots:

    void edited();
    void executeCommand();

protected slots:

    void updateCodeBlock();
    void scanCodeBlock(QString* code, ScanDirection direction);

protected:

    QString fileName;
    QString filePath;
    QString codeBlock;
    QFile file;

    unsigned int previousStartBlock, previousEndBlock, startBlock, endBlock;
    CodeBlockBackground codeBlockBackground;

private:

    bool unsavedEdits;
    void init();
    void loadFile();
};

} // ide namespace

} // panopticon namespace

#endif // EDITBUFFER_H
