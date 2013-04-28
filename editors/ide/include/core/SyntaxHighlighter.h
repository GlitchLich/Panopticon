#ifndef SYNTAXHIGHLIGHER_H
#define SYNTAXHIGHLIGHER_H

#include <QSyntaxHighlighter>
#include <QHash>

namespace panopticon
{

namespace ide
{

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT

public:

    explicit SyntaxHighlighter(QTextDocument* parent = 0);

    void highlightBlock(const QString &text);

protected:

    struct Rule
    {
        QRegExp pattern;
        QTextCharFormat format;
    };

    QVector<Rule> rules;
};

} // ide namespace

} // panopticon namespace

#endif // SYNTAXHIGHLIGHER_H
