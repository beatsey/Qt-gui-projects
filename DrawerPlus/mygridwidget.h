#ifndef MYGRIDWIDGET_H
#define MYGRIDWIDGET_H

#include <QWidget>
#include <QPainter>

class myGridWidget : public QWidget
{
    Q_OBJECT
public:
    explicit myGridWidget(QWidget *parent = nullptr);

    bool drawLines;

    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
signals:

};

#endif // MYGRIDWIDGET_H
