#ifndef EVOLUTEFORM_H
#define EVOLUTEFORM_H

#include <QWidget>

namespace Ui {
class evoluteform;
}

class EvoluteForm : public QWidget
{
    Q_OBJECT

public:
    explicit EvoluteForm(QWidget *parent = nullptr);
    ~EvoluteForm();

private slots:
    void on_evolutetable_cellChanged(int row, int column);

    void on_cBshowCircle_clicked(bool checked);

    void on_cBshowEvolute_clicked(bool checked);

    void on_sliderCircle_valueChanged(int value);

private:
    void parse(bool&,bool&);

    void ready();
    Ui::evoluteform *ui;


    bool initialized;

};

#endif // EVOLUTEFORM_H
