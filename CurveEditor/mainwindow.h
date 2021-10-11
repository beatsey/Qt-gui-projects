#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vec.h"
#include "variables.h"
#include "curvebuilder.h"
#include "evoluteform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    CurveBuilder curve;
    EvoluteForm evoluteform;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void clearPoints();

private slots:
    void on_pbNewControlLine_clicked();

    void OnChangingPoints();
    void buildCurve(int);

    void on_twPoints_cellChanged(int,int);

    // Buttons
    void on_pbLagrange_clicked();
    void on_pbBezierCurve_clicked();
    void on_pbDeletePoint_clicked();
    void on_cbShowBroken_clicked(bool);
    void on_pbRotate_clicked();

    void on_pbTriangle_clicked();

    void on_pbPolygon_clicked();

    void on_sBpolygonCount_valueChanged(int);

    void on_pbHermitCurve_clicked();

    void on_cBDeriv_clicked(bool checked);

    void on_pBCubicCurve_clicked();

    void on_phHermitEnergy_clicked();

    void on_pBrationalBezier_clicked();

    void on_pbDelaunay_clicked();

    void on_pBevolute_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
