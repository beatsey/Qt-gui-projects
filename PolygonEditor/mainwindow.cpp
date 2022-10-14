#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Для кнопки удаления
    connect(ui->centralWidget, SIGNAL(updateSelection(int)),
                this, SLOT(selection_actions_enabler(int)));

    // Для контекстного меню
    //connect(ui->centralWidget->remove, SIGNAL(triggered()), parent(), SLOT(removeDataPoint()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_action_figure_add_triggered()
{
    if (ui->action_figure_22->isChecked()){
        ui->centralWidget->addFigure(22);
        ui->centralWidget->repaint();
    }
    else if (ui->action_figure_32->isChecked()){
        ui->centralWidget->addFigure(32);
        ui->centralWidget->repaint();
    }

}

// Удалить все в меню
void MainWindow::on_action_triggered()
{
    ui->centralWidget->clearFigures();
}

// Врубить/вырубить кнопку удаления
void MainWindow::selection_actions_enabler(int index)
{
    ui->action_figure_remove->setEnabled(index!=-1);
    ui->action_figure_move->setEnabled(index!=-1);
    ui->action_figure_rotate->setEnabled(index!=-1);
}

void MainWindow::on_action_figure_remove_triggered()
{
    ui->centralWidget->removeSelection();
}

void MainWindow::on_action_2_triggered()
{
    ui->centralWidget->removeIntersected();
}

void MainWindow::on_action_figure_move_triggered()
{
    ui->centralWidget->relocateSelection();
}

void MainWindow::on_action_figure_rotate_triggered()
{
    ui->centralWidget->editSelection();
}

void MainWindow::on_action_figure_22_triggered(bool checked)
{
    if (checked){
        ui->action_figure_32->setChecked(false);
    }
    ui->action_figure_add->setEnabled(checked);

}

void MainWindow::on_action_figure_32_triggered(bool checked)
{
    if (checked){
        ui->action_figure_22->setChecked(false);
    }
    ui->action_figure_add->setEnabled(checked);

}
