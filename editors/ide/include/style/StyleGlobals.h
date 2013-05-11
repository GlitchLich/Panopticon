#ifndef STYLEGLOBALS_H
#define STYLEGLOBALS_H

#include <QFont>
#include <QTextCharFormat>

namespace panopticon
{

namespace ide
{

struct real_color
{
    qreal r, g, b, a;
    real_color(const qreal& r = 0.0, const qreal& g = 0.0, const qreal& b = 0.0, const qreal& a = 1.0) : r(r), g(g), b(b), a(a) { }
};

class Style
{
public:
    Style();

    void setClearColor(const QColor& color);
    void setClearColor(const real_color& color);
    const QColor& clearColor();
    const real_color& realClearColor();
    const qreal& clearR();
    const qreal& clearG();
    const qreal& clearB();
    const qreal& clearA();

    QFont mainFont;
    QFont monoFont;
    QFont toolFont;
    QTextCharFormat printFormat;
    QTextCharFormat printErrorFormat;
    QTextCharFormat keywordFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat booleanFormat;
    QTextCharFormat stringFormat;
    QTextCharFormat functionFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat flowFormat;

private:
    real_color prrealClearColor; // requires special handling, using the get/set interface.
    QColor prclearColor; // requires special handling. Use the get/set interface
};

extern Style* style;

} // ide namespace

} // panopticon namespace

#endif // STYLEGLOBALS_H
