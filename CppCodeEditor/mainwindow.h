#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "highlighter.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QProcess>
#include <QDebug>
namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() { delete ui; };

private:
  Ui::MainWindow *ui;
  Highlighter highlighter;

  QString fileName;
  QString filePath;
  bool fileSaved;
  bool firstLoad;

  void calculateResize();
public slots:
  void setUndoAvailable(bool flag);
  void setRedoAvailable(bool flag);
  void setCopyAvailable(bool flag);

  void changeSaveState(){

    if(firstLoad&&fileSaved){
        setWindowTitle(tr("Текстовый редактор - ")+fileName);
        firstLoad=false;
    }else{
        fileSaved=false;
        setWindowTitle(tr("Текстовый редактор - ")+fileName+tr("*"));
    }
  }

  void newFile();
  void saveFile(bool saveasflag=false);
  void openFile();
  void about();

protected:
  void resizeEvent(QResizeEvent* event)override;
  void closeEvent(QCloseEvent* event)override;

private slots:
  void on_actionExitApp_triggered();
  void on_actionSaveAs_triggered();
  void on_actionWordWrap_triggered(bool checked);
  void on_actionCopy_triggered();
  void on_actionCut_triggered();
  void on_actionPaste_triggered();
  void on_actionSelectAll_triggered();
  void on_actionFind_triggered();
  void on_actionFindReplace_triggered();
  void on_actionFontChoose_triggered();
  void on_actionBackgroundColor_triggered();
  void on_actionCurrentLineColor_triggered();
  void on_actionInstrumentPanel_triggered(bool checked);
  void on_actionStatusString_triggered(bool checked);
  void on_actionSyntaxHighlight_triggered(bool checked);
  void on_actionSyntaxC2011_triggered();
  void on_actionSyntaxCPP2014_triggered();
  void on_actionUndo_triggered();
  void on_actionRedo_triggered();
  void on_actionLineNumeration_triggered(bool checked);

  void LoadStyle();


  void updateStatusString();
  void on_actionDefaultSyntaxStyle_triggered();
  void on_actionOpenSyntaxStyleFromFile_triggered();
  void on_actionChangeSyntaxStyle_triggered();
};

#endif // MAINWINDOW_H
