#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "cppmath.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    curve(200), // amount of points
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showBrokenLine=ui->cbShowBroken->isChecked();
    vertices = ui->sBpolygonCount->value();
    editDerivatives=ui->cBDeriv->isChecked();

    ui->twPoints->verticalHeader()->show();

    // Изменение точек влечёт изменения в таблице
    connect(ui->graph_widget, SIGNAL(updatePoint(size_t)),
            ui->twPoints, SLOT(updateTable(size_t)));

    connect(ui->graph_widget, SIGNAL(updatePoint(size_t)),
            this, SLOT(OnChangingPoints()));

    // Изменили касательный вектор в сплайне Эрмита
    connect(ui->graph_widget, SIGNAL(updateDerivEnd(size_t)),
            this, SLOT(OnChangingPoints()));


    connect(ui->graph_widget, SIGNAL(ChangedPoints(int)),
            this, SLOT(buildCurve(int)));

}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pbNewControlLine_clicked(){
  clearPoints();
  ui->graph_widget->BeginCurve();
}

void MainWindow::buildCurve(int num=-1){
    // Проверка на количество точек
    int n= static_cast<int>(control_points.size());
    if(n<3)return;
    if(num<0)num=curve_type;

    switch(num){
        case NoCurve:
            curve_type = NoCurve;
            return;
        case insideTriangle:
            if(n<4)return;
            break;
        case insidePolygon:
            if(n<=vertices)return;
            break;
        case Rotation:
            if(n<3)return;
            break;
        default:;
    }
    curve_type = num;

    if(curve_type==HermitCurve || curve_type==CubicCurve|| curve_type==RationalBezierCurve){
        ui->cBDeriv->setEnabled(1);
    }else{
        ui->cBDeriv->setEnabled(0);
    }

    if(curve.build())repaint();
}

void MainWindow::OnChangingPoints(){
 if(ui->cbOnFlyRebuild->isChecked())
   buildCurve();
}

void MainWindow::on_pbLagrange_clicked(){
    buildCurve(LagrangeCurve);
}

void MainWindow::on_pbBezierCurve_clicked(){
buildCurve(BezierCurve);
}

void MainWindow::on_pbDeletePoint_clicked(){
    clearPoints();
}

void MainWindow::clearPoints(){
    control_points.clear();
    curve_points.clear();
    tangent_vectors.clear();
    tangent_ends.clear();
    curve_type = NoCurve;

    ui->sBpolygonCount->setValue(
        ui->sBpolygonCount->minimum());

    ui->twPoints->clearTable();
    repaint();
}

void MainWindow::on_twPoints_cellChanged(int row, int column){
    if(editMode!=Still)return;
    // Таблица изменена с клавиатуры

    bool status;
    double newValue = ui->twPoints->model()->index(row, column).data().toDouble(&status);

    if(status){
        control_points[static_cast<size_t>(row)].elem[column] = newValue;
        buildCurve();
    }
}

void MainWindow::on_cbShowBroken_clicked(bool checked){
    showBrokenLine=checked;
    repaint();
}

void MainWindow::on_pbRotate_clicked(){
    buildCurve(Rotation); // Предикат поворота. Прямую задают первые две точки.
}

void MainWindow::on_pbTriangle_clicked(){
    buildCurve(insideTriangle);
}

void MainWindow::on_pbPolygon_clicked(){
    buildCurve(insidePolygon);
}

void MainWindow::on_sBpolygonCount_valueChanged(int amount){
    if(static_cast<size_t>(amount)<control_points.size())
    vertices = amount;

    if(curve_type == insidePolygon)
        buildCurve(insidePolygon);
}

void MainWindow::on_pbHermitCurve_clicked(){
    // Удаляем касательные, чтобы curve.build()
    // их перестроила
    tangent_vectors.clear();
    buildCurve(HermitCurve);
}

void MainWindow::on_cBDeriv_clicked(bool checked)
{
    editDerivatives=checked;
    if(curve_type==HermitCurve||curve_type==CubicCurve||curve_type==RationalBezierCurve)
    repaint();
}

void MainWindow::on_pBCubicCurve_clicked(){
    tangent_vectors.clear();
    buildCurve(CubicCurve);
}

void MainWindow::on_phHermitEnergy_clicked(){
    buildCurve(HermitEnergy);
}

void MainWindow::on_pBrationalBezier_clicked(){
    tangent_vectors.clear();
    buildCurve(RationalBezierCurve);
}

void MainWindow::on_pbDelaunay_clicked(){
    buildCurve(DelaunayTriangulation);
}


// Открываем ещё одно окно для эволюты
void MainWindow::on_pBevolute_clicked(){
    evoluteform.show();
}
