#include "ide/include/core/SyntaxHighlighter.h"
#include "ide/include/style/StyleGlobals.h"

namespace panopticon
{

namespace ide
{
SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent) :
    QSyntaxHighlighter(parent)
{
    Rule rule;

    QStringList keywordPatterns;
    keywordPatterns << "\\btrue\\b" << "\\bfalse\\b" << "\\blet\\b" << "\\bswitch\\b"
                    << "\\bif\\b" << "\\bthen\\b" << "\\belse\\b"
                    << "\\bcase\\b" << "\\bof\\b" << "\\bwhere\\b" << "\\bin\\b"
                    << "\\[" << "\\]" << "\\(" << "\\)" << "\\_"
                    << "\\:" << "\\|" << "\\." << "\\\\";

    foreach(const QString& pattern, keywordPatterns)
    {
        rule.pattern = QRegExp(pattern);
        rule.format = style->keywordFormat;
        rules.append(rule);
    }


    rule.pattern = QRegExp("//[^\n]*");
    rule.format = style->singleLineCommentFormat;
    rules.append(rule);


    rule.pattern = QRegExp("\".*\"");
    rule.format = style->stringFormat;
    rules.append(rule);

    rule.pattern = QRegExp("\'.*\'");
    rule.format = style->stringFormat;
    rules.append(rule);


    rule.pattern = QRegExp("\\d");
    rule.format = style->numberFormat;
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
