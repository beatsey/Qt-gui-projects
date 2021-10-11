#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "figure.h"

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

    void on_action_figure_61_triggered(bool checked);
    void on_action_figure_51_triggered(bool checked);
    void on_action_figure_add_triggered();

    void on_action_triggered();

    void selection_actions_enabler(int index);

    void on_action_figure_remove_triggered();

    void on_action_2_triggered();

    void on_action_figure_move_triggered();

    void on_action_figure_rotate_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
