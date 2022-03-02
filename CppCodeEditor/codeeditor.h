#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QPlainTextEdit>
#include <QObject>
#include <QPainter>
#include <QListWidget>
#include <QListWidgetItem>
#include <algorithm>
#include <QDateTime>

QT_BEGIN_NAMESPACE
class QPaintEvent;
class QResizeEvent;
class QSize;
class QWidget;
QT_END_NAMESPACE

class LineNumberArea;

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent = 0);

    void lineNumberAreaPaintEvent(QPaintEvent *event);

    // Флаг нумерации строк
    bool numeration;

    QDateTime lastchanges;
    bool changesWereMade;

    QColor lineColor;
    QColor backgroundColor;
    QColor numericalColumnColor;
    QFont defaultFont;

    void updateBackgroundColor();

public slots:
    void highlightCurrentLine();
    void updateLineNumberAreaWidth();
    void loadStyle(QString filename="");
    void saveStyle(QString filename);

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void updateLineNumberArea(const QRect &, int);

private:
    QWidget *lineNumberArea;

};

class LineNumberArea : public QWidget
{
public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor) {
        codeEditor = editor;
    }

    QSize sizeHint() const override {
        return QSize(width(), 0);
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        codeEditor->lineNumberAreaPaintEvent(event);

    }

private:
    CodeEditor *codeEditor;

};

#endif
