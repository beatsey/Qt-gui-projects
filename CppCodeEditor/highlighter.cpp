#include "highlighter.h"

Highlighter::Highlighter(QTextDocument *parent)
    : QSyntaxHighlighter(parent),
      syntax(CPP2014)
{
    HighlightingRule rule;

    // CPP2014

    QStringList keywordPatterns;
    keywordPatterns << "\\bchar\\b" << "\\bclass\\b" << "\\bconst\\b"
                    << "\\bdouble\\b" << "\\benum\\b" << "\\bexplicit\\b"
                    << "\\bfriend\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bnamespace\\b" << "\\boperator\\b"
                    << "\\bprivate\\b" << "\\bprotected\\b" << "\\bpublic\\b"
                    << "\\bshort\\b" << "\\bsignals\\b" << "\\bsigned\\b"
                    << "\\bslots\\b" << "\\bstatic\\b" << "\\bstruct\\b" << "\\bauto\\b"
                    << "\\btemplate\\b" << "\\btypedef\\b" << "\\btypename\\b"
                    << "\\bunion\\b" << "\\bunsigned\\b" << "\\bvirtual\\b"
                    << "\\bvoid\\b" << "\\bvolatile\\b" << "\\bbool\\b"<<"\\busing\\b"<<"\\bconstexpr\\b"
                    <<"\\bsizeof\\b"<<"\\bif\\b"<<"\\bfor\\b"<<"\\bforeach\\b"<<"\\bwhile\\b"<<"\\bdo\\b"<<"\\bcase\\b"
                    <<"\\bbreak\\b"<<"\\bcontinue\\b"<<"\\btemplate\\b"<<"\\bdelete\\b"<<"\\bnew\\b"
                    <<"\\bdefault\\b"<<"\\btry\\b"<<"\\breturn\\b"<<"\\bthrow\\b"<<"\\bcatch\\b"<<"\\bgoto\\b"<<"\\belse\\b"
                    <<"\\bextren\\b"<<"\\bthis\\b"<<"\\bswitch\\b"<<"\\binclude\\b"<<"\\bdefine\\b";

    keywordFormat.setForeground(QColor(201,81,116));
    keywordFormat.setFontWeight(QFont::Bold);
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRulesCPP2014.append(rule);
    }


    // C2011 https://docs.microsoft.com/ru-ru/cpp/c-language/c-keywords?view=msvc-170

    keywordPatterns.clear();
    keywordPatterns << "\\bauto\\b" << "\\bbreak\\b" << "\\bcase\\b"
                    << "\\bchar\\b" << "\\bconst\\b" << "\\bcontinue\\b"
                    << "\\bdefault\\b" << "\\bdo\\b" << "\\bdouble\\b"
                    << "\\belse\\b" << "\\benum\\b" << "\\bextern\\b"
                    << "\\bfloat\\b" << "\\bfor\\b" << "\\bgoto\\b"
                    << "\\bif\\b" << "\\binline\\b" << "\\bint\\b"
                    << "\\blong\\b" << "\\bregister\\b" << "\\brestrict\\b"
                    << "\\breturn\\b" << "\\bshort\\b" << "\\bsigned\\b"
                    << "\\bsizeof\\b" << "\\bstatic\\b" << "\\bstruct\\b"
                    << "\\bswitch\\b" << "\\btypedef\\b" << "\\bunion\\b"
                    << "\\bunsigned\\b" << "\\bvoid\\b" << "\\bvolatile\\b"
                    << "\\bwhile\\b";

    keywordFormat.setForeground(QColor(201,81,116));
    keywordFormat.setFontWeight(QFont::Bold);
    foreach (const QString &pattern, keywordPatterns) {
        rule.pattern = QRegularExpression(pattern);
        rule.format = keywordFormat;
        highlightingRulesC2011.append(rule);
    }




    // class and struct
    classFormat.setFontWeight(QFont::Bold);
    classFormat.setForeground(Qt::darkMagenta);
    rule.pattern = QRegularExpression("(?<=class\\s)\\w*");
    rule.format = classFormat;
    highlightingRulesCPP2014.append(rule);
    rule.pattern = QRegularExpression("(?<=struct\\s)\\w*");
    highlightingRulesCommon.append(rule);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("(?<=#include\\s)(<.*>)|(?<=#include)(<.*>)|(?<=#include\\s)(\".*\")|(?<=#include)(\".*\")|\".*\"");
    rule.format = quotationFormat;
    highlightingRulesCommon.append(rule);

    quotationFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression("(?<=#define\\s)(<.*>)|(?<=#define)(<.*>)|(?<=#define\\s)(\".*\")|(?<=#define)(\".*\")|\".*\"");
    rule.format = quotationFormat;
    highlightingRulesCommon.append(rule);

    functionFormat.setFontItalic(true);
    functionFormat.setForeground(QColor(115,182,209));
    rule.pattern = QRegularExpression("\\b[A-Za-z0-9_]+(?=\\()");
    rule.format = functionFormat;
    highlightingRulesCommon.append(rule);


    singleLineCommentFormat.setForeground(Qt::gray);
    rule.pattern = QRegularExpression("//[^\n]*");
    rule.format = singleLineCommentFormat;
    highlightingRulesCommon.append(rule);

    multiLineCommentFormat.setForeground(Qt::gray);
    commentStartExpression = QRegularExpression("/\\*");
    commentEndExpression = QRegularExpression("\\*/");
}

void Highlighter::highlightBlock(const QString &text)
{
    if (syntax==CPP2014) {
        foreach (const HighlightingRule &rule, highlightingRulesCPP2014) {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
    }else if (syntax==C2011) {
        foreach (const HighlightingRule &rule, highlightingRulesC2011) {
            QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
            while (matchIterator.hasNext()) {
                QRegularExpressionMatch match = matchIterator.next();
                setFormat(match.capturedStart(), match.capturedLength(), rule.format);
            }
        }
    }

    foreach (const HighlightingRule &rule, highlightingRulesCommon) {
        QRegularExpressionMatchIterator matchIterator = rule.pattern.globalMatch(text);
        while (matchIterator.hasNext()) {
            QRegularExpressionMatch match = matchIterator.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }

    // комментарии
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1)
        startIndex = text.indexOf(commentStartExpression);

    while (startIndex >= 0) {
        QRegularExpressionMatch match = commentEndExpression.match(text, startIndex);
        int endIndex = match.capturedStart();
        int commentLength = 0;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                            + match.capturedLength();
        }

        setFormat(startIndex, commentLength, multiLineCommentFormat);
        startIndex = text.indexOf(commentStartExpression, startIndex + commentLength);
    }
}
