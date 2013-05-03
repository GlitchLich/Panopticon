#include "ide/include/style/StyleGlobals.h"

namespace panopticon
{

namespace ide
{

Style::Style()
{
#ifdef __LINUX__
    toolFont = QFont("Ubuntu", 8);
    mainFont = QFont("Ubuntu", 13);
    monoFont = QFont("Ubuntu Mono", 13);
#else
    toolFont = QFont("Myriad", 8);
    mainFont = QFont("Myriad", 13);
    monoFont = QFont("Menlo", 13);
#endif

    // monoFont.setFixedPitch(true);
    monoFont.setStyleHint(QFont::Monospace);
    monoFont.setStyleStrategy(QFont::ForceIntegerMetrics);
    printFormat.setForeground(QColor(180, 180, 180));
    printFormat.setFont(monoFont);
    printErrorFormat.setForeground(QColor(255, 0, 50));
    printErrorFormat.setFont(monoFont);
    printErrorFormat.setFontWeight(QFont::Bold);
    keywordFormat.setForeground(QColor(25, 125, 200));
    keywordFormat.setFontWeight(QFont::Bold);
    singleLineCommentFormat.setForeground(QColor(200, 80, 80));
    stringFormat.setForeground(QColor(25, 180, 125));
    numberFormat.setForeground(QColor(180, 50, 135));
    flowFormat.setForeground(QColor(100, 255, 200));

    prrealClearColor = { 0.2, 0.06, 0.15, 1 };
    prclearColor.setRgbF(prrealClearColor.r, prrealClearColor.g, prrealClearColor.b, prrealClearColor.a);
}

void Style::setClearColor(const QColor& color)
{
    prclearColor = color;
    prclearColor.getRgbF(&prrealClearColor.r, &prrealClearColor.g, &prrealClearColor.b, &prrealClearColor.a);
}

const QColor& Style::clearColor()
{
    return prclearColor;
}

void Style::setClearColor(const real_color& color)
{
    prrealClearColor = color;
    prclearColor.setRgbF(prrealClearColor.r, prrealClearColor.g, prrealClearColor.b, prrealClearColor.a);
}

const real_color& Style::realClearColor()
{
    return prrealClearColor;
}

const qreal& Style::clearR()
{
    return prrealClearColor.r;
}

const qreal& Style::clearG()
{
    return prrealClearColor.g;
}

const qreal& Style::clearB()
{
    return prrealClearColor.b;
}

const qreal& Style::clearA()
{
    return prrealClearColor.a;
}

Style* style = 0; // global style

} // ide namespace

} // panopticon namespace
