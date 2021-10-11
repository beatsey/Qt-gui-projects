#ifndef EVOLUTE2DWIDGET_H
#define EVOLUTE2DWIDGET_H

#include <QWidget>

class Evolute2dWidget : public QWidget
{
    Q_OBJECT
public:
    explicit Evolute2dWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;

    bool statusX;
    bool statusY;
    bool showCircle;
    bool showEvolute;
    int circlePos;

signals:

public slots:
};

#endif // EVOLUTE2DWIDGET_H
