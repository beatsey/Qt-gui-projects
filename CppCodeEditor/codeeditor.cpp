#include <QtWidgets>
#include <QDebug>
#include "codeeditor.h"

CodeEditor::CodeEditor(QWidget *parent) :
    QPlainTextEdit(parent),
    numeration(true),
    lastchanges(),
    changesWereMade(false),
    lineColor(240, 240, 240),       // фон выделенной строки
    backgroundColor(255, 255, 255), // фон редактора
    numericalColumnColor(232,232,232), // фон колонки нумерации строк
    defaultFont(document()->defaultFont()),
    lineNumberArea(new LineNumberArea(this))
{

    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth()));
    connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
    connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    connect(this, SIGNAL(undoAvailable(bool)), parent->parent(), SLOT(setUndoAvailable(bool)));
    connect(this, SIGNAL(redoAvailable(bool)), parent->parent(), SLOT(setRedoAvailable(bool)));
    connect(this, SIGNAL(copyAvailable(bool)), parent->parent(), SLOT(setCopyAvailable(bool)));

    highlightCurrentLine();
    updateBackgroundColor();

    QPalette p = palette();
    p.setColor(QPalette::Text,Qt::black); // Основной цвет текста
    setPalette(p);
}

void CodeEditor::loadStyle(QString filename) {
    // load Style from file
    if(filename==""){
        // default
        lineColor = QColor(240, 240, 240);       // фон выделенной строки
        backgroundColor = QColor(255, 255, 255); // фон редактора
        document()->setDefaultFont(defaultFont); // стандартный шрифт


    }else{
        // From file
        QFile scr_file(filename);
        if (scr_file.open(QIODevice::ReadOnly)) {

            QDataStream in(&scr_file);

            QFont ft;
            in >> lineColor >> backgroundColor >> ft;
            scr_file.close();

            document()->setDefaultFont(ft);
        }
    }

    updateBackgroundColor();
    highlightCurrentLine();
    repaint();
}

void CodeEditor::saveStyle(QString filename) {

    QFile scr_file(filename);
    if (scr_file.open(QIODevice::WriteOnly))
    {
        QFont ft = document()->defaultFont();

        QDataStream out(&scr_file);
        out << lineColor << backgroundColor << ft;
        scr_file.close();
    }
}

void CodeEditor::updateBackgroundColor(){
    QString color = "rgb(" + QString::number(backgroundColor.red()) +
                    tr(",") + QString::number(backgroundColor.green()) +
                    tr(",") + QString::number(backgroundColor.blue()) + ")";

    setStyleSheet("background-color:" + color);
}

void CodeEditor::updateLineNumberAreaWidth()
{
    int space = 0;
    if(numeration) {
        int digits = qMax(QString::number(blockCount()).length(),2); // Количество символов, необходимых для нумерации строк
        space = 10 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    }

    lineNumberArea->setGeometry(0,0,space, height());
    setViewportMargins(space, 0, 0, 0);
}


void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

    if (rect.contains(viewport()->rect()))
        updateLineNumberAreaWidth();

}


void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);
    updateLineNumberAreaWidth();
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;
    selection.format.setBackground(lineColor);
    selection.format.setProperty(QTextFormat::FullWidthSelection, true);
    selection.cursor = textCursor();
    extraSelections.append(selection);
    setExtraSelections(extraSelections);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{

    QPainter painter(lineNumberArea);
    //painter.setPen(numericalColumnColor); // Цвет нумерации строк
    painter.fillRect(event->rect(), numericalColumnColor);

    QTextBlock block = firstVisibleBlock();
    int blockNumber = block.blockNumber();
    int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
    int bottom = top + (int) blockBoundingRect(block).height();

    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);

            painter.setPen(QColor(160,160,160)); // Цвет текста нумерации строк
            painter.drawText(0, top, lineNumberArea->width(), blockBoundingRect(block).height(), Qt::AlignCenter, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + (int) blockBoundingRect(block).height();
        ++blockNumber;
    }

}
