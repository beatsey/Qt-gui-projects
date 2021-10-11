#include "editdialog.h"
#include "ui_editdialog.h"
#include "graphicsWidget.h"

EditDialog::EditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog)
{
    ui->setupUi(this);
}

void EditDialog::init(figure* fig){
    this->fig=fig;

    ui->AX->setValue(fig->AX);
    ui->DR->setValue(fig->DR);
    ui->FP->setValue(fig->FP);
    ui->horizontalSlider_Angle->setValue(fig->Angle);
    ui->label_angle->setText(QString::number(fig->Angle));

    updatePerimeterAndArea();

    // Только для фигуры 61
    if (fig->type==61){
        ui->BX->setValue(fig->BX);
        ui->CX->setValue(fig->CX);
        ui->EQ->setValue(fig->EQ);
    }else if (fig->type==51) {
        ui->BX->setEnabled(false);
        ui->CX->setEnabled(false);
        ui->EQ->setEnabled(false);
    }
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::updatePerimeterAndArea(){
    ui->label_area->setText(QString::number(fig->area));
    ui->label_perimeter->setText(QString::number(fig->perimeter));
}

void EditDialog::on_horizontalSlider_Angle_valueChanged(int value)
{
    // Обновляем угол поворота
    fig->Angle=value;
    ui->label_angle->setText(QString::number(value));

    fig->calculateTransformedPolygon();
    ((GraphicsWidget*)parent())->repaint();
}

void EditDialog::on_AX_valueChanged(int arg1)
{
    fig->AX=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();

    ((GraphicsWidget*)parent())->repaint();
}

void EditDialog::on_BX_valueChanged(int arg1)
{
    fig->BX=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();

    ((GraphicsWidget*)parent())->repaint();
}

void EditDialog::on_CX_valueChanged(int arg1)
{
    fig->CX=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();

    ((GraphicsWidget*)parent())->repaint();
}

void EditDialog::on_EQ_valueChanged(int arg1)
{
    fig->EQ=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();

    ((GraphicsWidget*)parent())->repaint();
}

void EditDialog::on_DR_valueChanged(int arg1)
{
    fig->DR=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();

    ((GraphicsWidget*)parent())->repaint();
}

void EditDialog::on_FP_valueChanged(int arg1)
{
    fig->FP=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();

    ((GraphicsWidget*)parent())->repaint();
}
