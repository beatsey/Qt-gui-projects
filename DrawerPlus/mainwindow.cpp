#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QRandomGenerator>

void setButtonEnabled(QPushButton* but,bool flag){
    but->setEnabled(flag);
    if (flag)
        but->setStyleSheet("");
    else
        but->setStyleSheet("background-color: rgba(255, 255, 255, 0);color:rgba(255, 255, 255, 0);");
}

void MainWindow::setButtonForExit(QPushButton* but){
    setButtonEnabled(but, true);
    connect(but, SIGNAL(clicked()),this, SLOT(on_actionExit_triggered()));
    but->setText("Выход");
}

void MainWindow::setButtonForClear(QPushButton* but){
    setButtonEnabled(but, true);
    connect(but, SIGNAL(clicked()),this, SLOT(clearCurrentGraphics()));
    but->setText("Очистить");
}



void MainWindow::setButtonsOnTab(int tabIndex){
    switch(tabIndex){
        case 0:
            disconnect(ui->pushButton_11, SIGNAL(clicked()),0,0);
            disconnect(ui->pushButton_12, SIGNAL(clicked()),0,0);
            disconnect(ui->pushButton_13, SIGNAL(clicked()),0,0);
            disconnect(ui->pushButton_14, SIGNAL(clicked()),0,0);

            if(array[tabIndex]==0){
                // выход
                setButtonForExit(ui->pushButton_11);

                // очистить
                setButtonForClear(ui->pushButton_13);

                setButtonEnabled(ui->pushButton_12, false);
                setButtonEnabled(ui->pushButton_14, false);

            }else if(array[tabIndex]==1){
                // выход
                setButtonForExit(ui->pushButton_12);

                // очистить
                setButtonForClear(ui->pushButton_14);

                setButtonEnabled(ui->pushButton_11, false);
                setButtonEnabled(ui->pushButton_13, false);
            }else if(array[tabIndex]==2){
                // выход
                setButtonForExit(ui->pushButton_13);

                // очистить
                setButtonForClear(ui->pushButton_11);

                setButtonEnabled(ui->pushButton_12, false);
                setButtonEnabled(ui->pushButton_14, false);
            }else if(array[tabIndex]==3){
                // выход
                setButtonForExit(ui->pushButton_14);

                // очистить
                setButtonForClear(ui->pushButton_12);

                setButtonEnabled(ui->pushButton_11, false);
                setButtonEnabled(ui->pushButton_13, false);
            }
            break;
        case 1:
            disconnect(ui->pushButton_21, SIGNAL(clicked()),0,0);
            disconnect(ui->pushButton_22, SIGNAL(clicked()),0,0);
            disconnect(ui->pushButton_23, SIGNAL(clicked()),0,0);
            disconnect(ui->pushButton_24, SIGNAL(clicked()),0,0);

            if(array[tabIndex]==0){
                // выход
                setButtonForExit(ui->pushButton_21);

                // очистить
                setButtonForClear(ui->pushButton_23);

                setButtonEnabled(ui->pushButton_22, false);
                setButtonEnabled(ui->pushButton_24, false);

            }else if(array[tabIndex]==1){
                // выход
                setButtonForExit(ui->pushButton_22);

                // очистить
                setButtonForClear(ui->pushButton_24);

                setButtonEnabled(ui->pushButton_21, false);
                setButtonEnabled(ui->pushButton_23, false);
            }else if(array[tabIndex]==2){
                // выход
                setButtonForExit(ui->pushButton_23);

                // очистить
                setButtonForClear(ui->pushButton_21);

                setButtonEnabled(ui->pushButton_22, false);
                setButtonEnabled(ui->pushButton_24, false);
            }else if(array[tabIndex]==3){
                // выход
                setButtonForExit(ui->pushButton_24);

                // очистить
                setButtonForClear(ui->pushButton_22);

                setButtonEnabled(ui->pushButton_21, false);
                setButtonEnabled(ui->pushButton_23, false);
            }
            break;
        case 2:
            disconnect(ui->pushButton_31, SIGNAL(clicked()),0,0);
            disconnect(ui->pushButton_32, SIGNAL(clicked()),0,0);
            disconnect(ui->pushButton_33, SIGNAL(clicked()),0,0);
            disconnect(ui->pushButton_34, SIGNAL(clicked()),0,0);

            if(array[tabIndex]==0){
                // выход
                setButtonForExit(ui->pushButton_31);

                // очистить
                setButtonForClear(ui->pushButton_33);

                setButtonEnabled(ui->pushButton_32, false);
                setButtonEnabled(ui->pushButton_34, false);

            }else if(array[tabIndex]==1){
                // выход
                setButtonForExit(ui->pushButton_32);

                // очистить
                setButtonForClear(ui->pushButton_34);

                setButtonEnabled(ui->pushButton_31, false);
                setButtonEnabled(ui->pushButton_33, false);
            }else if(array[tabIndex]==2){
                // выход
                setButtonForExit(ui->pushButton_33);

                // очистить
                setButtonForClear(ui->pushButton_31);

                setButtonEnabled(ui->pushButton_32, false);
                setButtonEnabled(ui->pushButton_34, false);
            }else if(array[tabIndex]==3){
                // выход
                setButtonForExit(ui->pushButton_34);

                // очистить
                setButtonForClear(ui->pushButton_32);

                setButtonEnabled(ui->pushButton_31, false);
                setButtonEnabled(ui->pushButton_33, false);
            }
            break;


        default:
            exit(-2);
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Устанавливаем время для генератора случайных чисел
    srand(static_cast <unsigned int> (time(0)));

    setButtonsOnTab(0);
    setButtonsOnTab(1);
    setButtonsOnTab(2);
}

MainWindow::~MainWindow(){
    delete ui;
}

// Функция очищает текущий холст
void MainWindow::clearCurrentGraphics() {
    switch(ui->tabWidget->currentIndex()){
        case 0:
            ui->graphics1->control_points.clear();
            ui->graphics1->repaint();
            break;
        case 1:
            ui->graphics2->control_points.clear();
            ui->graphics2->repaint();
            break;
        case 2:
            ui->graphics3->control_points.clear();
            ui->graphics3->repaint();
            break;
        default:
            exit(-2);
    }
}


void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionLeft_triggered()
{
    const int currentTabIndex = ui->tabWidget->currentIndex();
    if(array[currentTabIndex]==0)
        array[currentTabIndex]=3;
    else
        array[currentTabIndex]--;

    setButtonsOnTab(currentTabIndex);
}

void MainWindow::on_actionRight_triggered()
{
    const int currentTabIndex = ui->tabWidget->currentIndex();
    if(array[currentTabIndex]==3)
        array[currentTabIndex]=0;
    else
        array[currentTabIndex]++;

    setButtonsOnTab(currentTabIndex);

}

int MainWindow::randInt(int low, int high)
{
    // Random number between low and high
    return rand() % ((high + 1) - low) + low;
}

void MainWindow::on_actionLines_triggered()
{
    std::cout << "test" << std::endl;
    switch(ui->tabWidget->currentIndex()){
        case 0:
            ui->gridWidget_1->drawLines^=true;
            ui->actionLines->setChecked(ui->gridWidget_1->drawLines);
            ui->gridWidget_1->repaint();
            break;
        case 1:
            ui->gridWidget_2->drawLines^=true;
            ui->actionLines->setChecked(ui->gridWidget_2->drawLines);
            ui->gridWidget_2->repaint();
            break;
        case 2:
            ui->gridWidget_3->drawLines^=true;
            ui->actionLines->setChecked(ui->gridWidget_3->drawLines);
            ui->gridWidget_3->repaint();
            break;
        default:
            exit(-2);
    }

}

// tab сменился
void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index){
        case 0:
            ui->actionLines->setChecked(ui->gridWidget_1->drawLines);
            break;
        case 1:
            ui->actionLines->setChecked(ui->gridWidget_2->drawLines);
            break;
        case 2:
            ui->actionLines->setChecked(ui->gridWidget_3->drawLines);
            break;
    }
}

void MainWindow::on_actionRandom_triggered()
{
    int currentTabIndex = ui->tabWidget->currentIndex();
    array[currentTabIndex]=randInt(0,3);
    setButtonsOnTab(currentTabIndex);
}
