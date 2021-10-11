#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    void on_actionDraw_triggered(bool checked);

    void on_actionColor_triggered();

    void on_actionClear_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
