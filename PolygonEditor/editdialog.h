#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>
#include "figure.h"

class figure;

namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

    figure* fig;

    void updatePerimeterAndArea();
public:
    explicit EditDialog(QWidget *parent = nullptr);
    ~EditDialog();

    void init(figure* fig);

private slots:
    void on_horizontalSlider_Angle_valueChanged(int value);

    void on_AX_valueChanged(int arg1);

    void on_BX_valueChanged(int arg1);

    void on_CX_valueChanged(int arg1);

    void on_EQ_valueChanged(int arg1);

    void on_DR_valueChanged(int arg1);

    void on_FP_valueChanged(int arg1);

private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
