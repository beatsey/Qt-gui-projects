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

    ui->label_angle->setText(QString::number(fig->Angle));
    ui->horizontalSlider_Angle->setValue(fig->Angle);

    ui->A->setMaximum(fig->h/3);
    ui->B->setMaximum(fig->h/3);
    ui->C->setMaximum(fig->h/3);
    ui->D->setMaximum(fig->h/3);
    ui->E->setMaximum(fig->w/4);
    ui->F->setMaximum(fig->w/4);

    if (fig->type==22){
        ui->A->setValue(fig->AR);
        ui->B->setValue(fig->BR);
        ui->C->setValue(fig->CR);
        ui->D->setValue(fig->DX);
        ui->E->setValue(0);
        ui->E->setEnabled(false);
        ui->F->setValue(fig->FQ);
    }else if (fig->type==32) {
        ui->A->setValue(fig->AX);
        ui->B->setValue(0);
        ui->B->setEnabled(false);
        ui->C->setValue(fig->CR);
        ui->D->setValue(fig->DX);
        ui->E->setValue(0);
        ui->E->setEnabled(false);
        ui->F->setValue(0);
        ui->F->setEnabled(false);
    }
    updatePerimeterAndArea();
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

void EditDialog::on_A_valueChanged(int arg1)
{
    fig->AX=arg1;
    fig->AR=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();

    ((GraphicsWidget*)parent())->repaint();
}

void EditDialog::on_B_valueChanged(int arg1)
{
    fig->BX=arg1;
    fig->BR=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();
    ((GraphicsWidget*)parent())->repaint();
}

void EditDialog::on_C_valueChanged(int arg1)
{

    fig->CX=arg1;
    fig->CR=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();
    ((GraphicsWidget*)parent())->repaint();
}

void EditDialog::on_D_valueChanged(int arg1)
{

    fig->DX=arg1;
    fig->DR=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();
    ((GraphicsWidget*)parent())->repaint();
}

void EditDialog::on_E_valueChanged(int arg1)
{
    fig->EP=arg1;
    fig->EQ=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();
    ((GraphicsWidget*)parent())->repaint();
}

void EditDialog::on_F_valueChanged(int arg1)
{
    fig->FP=arg1;
    fig->FQ=arg1;
    fig->calculatePolygon();
    updatePerimeterAndArea();
    ((GraphicsWidget*)parent())->repaint();
}
