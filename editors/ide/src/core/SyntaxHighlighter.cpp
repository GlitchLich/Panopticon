#include "ide/include/core/SyntaxHighlighter.h"

namespace panopticon
{

namespace ide
{
SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent) :
    QSyntaxHighlighter(parent)
{
    Rule rule;
    keywordFormat.setForeground(QColor(25, 125, 200));
    keywordFormat.setFontWeight(QFont::Bold);
    QStringList keywordPatterns;
    keywordPatterns << "\\btrue\\b" << "\\bfalse\\b" << "\\blet\\b" << "\\bswitch\\b"
                    << "\\bif\\b" << "\\bthen\\b" << "\\belse\\b"
                    << "\\[" << "\\]" << "\\(" << "\\)"
                    << "\\:" << "\\|" << "\\.";

    foreach(const QString& pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = keywordFormat;
        rules.append(rule);
    }

    singleLineCommentFormat.setForeground(QColor(200, 80, 80));
    rule.pattern = QRegExp("//[^\n]*");
    rule.format = singleLineCommentFormat;
    rules.append(rule);

    stringFormat.setForeground(QColor(25, 180, 125));
    rule.pattern = QRegExp("\".*\"");
    rule.format = stringFormat;
    rules.append(rule);

    rule.pattern = QRegExp("\'.*\'");
    rule.format = stringFormat;
    rules.append(rule);

    numberFormat.setForeground(QColor(180, 50, 135));
    rule.pattern = QRegExp("\\d");
    rule.format = numberFormat;
    rules.append(rule);
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    foreach (const Rule& rule, rules)
    {
        QRegExp expression(rule.pattern);
        int index = expression.indexIn(text);

        while (index >= 0)
        {
            int length = expression.matchedLength();
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }

    setCurrentBlockState(0);
}

} // ide namespace

} // panopticon namespace
