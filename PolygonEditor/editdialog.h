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

    void on_A_valueChanged(int arg1);

    void on_B_valueChanged(int arg1);

    void on_C_valueChanged(int arg1);

    void on_D_valueChanged(int arg1);

    void on_F_valueChanged(int arg1);

    void on_E_valueChanged(int arg1);

private:
    Ui::EditDialog *ui;
};

#endif // EDITDIALOG_H
