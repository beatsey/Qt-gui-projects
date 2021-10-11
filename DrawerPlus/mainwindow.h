#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <ctime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void clearPoints();

private slots:
    void on_actionExit_triggered();

    void on_actionLeft_triggered();

    void on_actionRight_triggered();
    void clearCurrentGraphics();

    void on_actionLines_triggered();

    void on_tabWidget_currentChanged(int index);

    void on_actionRandom_triggered();

private:
    Ui::MainWindow *ui;
    void setButtonsOnTab(int tabIndex);
    void setButtonForExit(QPushButton* but);
    void setButtonForClear(QPushButton* but);

    /* По одному числу на каждую вкладку. если array[i]=k, то i-я вкладка имеет состояние кнопок k.
     * k    выход   очистить
     * 0    слева   справа
     * 1    сверху  снизу
     * 2    справа  слева
     * 3    снизу   сверху
     */
    int array[3]={0};

    int randInt(int low, int high);

};

#endif // MAINWINDOW_H
