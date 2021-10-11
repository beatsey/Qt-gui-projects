#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_actionDraw_triggered(bool checked)
{
    if(checked) {
        // Режим рисования
        ui->centralWidget->mode = DRAW;

        ui->centralWidget->pixmap=QPixmap(ui->centralWidget->size());
        ui->centralWidget->pixmap.fill();

    }else{
        // Режим ломанной
        ui->centralWidget->mode = LINE;
        ui->centralWidget->control_points.clear();
    }

    repaint();
}

enum {BLACK,RED,BLUE} current=BLACK;
void MainWindow::on_actionColor_triggered()
{
    if(current==BLACK){
        current=RED;
        ui->centralWidget->painterPenColor = Qt::red;
        ui->actionColor->setText("Цвет: красный");
    }else if(current==RED){
        current=BLUE;
        ui->centralWidget->painterPenColor = Qt::blue;
        ui->actionColor->setText("Цвет: синий");
    }else if(current==BLUE){
        current=BLACK;
        ui->centralWidget->painterPenColor = Qt::black;
        ui->actionColor->setText("Цвет: черный");
    }
}


void MainWindow::on_actionClear_triggered()
{
    if(ui->centralWidget->mode==LINE)
        ui->centralWidget->control_points.clear();
    else if(ui->centralWidget->mode==DRAW)
        ui->centralWidget->pixmap.fill();

    repaint();
}

