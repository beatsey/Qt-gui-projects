#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow),
  firstLoad(true)
{
    ui->setupUi(this);

    // set up highlighter

    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    //font.setPointSize(20);
    ui->editor->setFont(font);
    ui->editor->setTabStopDistance(fontMetrics().horizontalAdvance(QLatin1Char('9'))*4);
    highlighter.setDocument(ui->editor->document());

    updateStatusString();

    //ui->statusBar->setStyleSheet("QStatusBar{background:rgb(50,50,50);}");
    //ui->mainToolBar->setStyleSheet("QToolButton:hover {background-color:darkgray} QToolBar {background: rgb(240,240,240);border: none;}");
    ui->mainToolBar->setStyleSheet("QToolBar {background: rgb(240,240,240);border: none;}");

    QPalette windowPalette=palette();
    windowPalette.setColor(QPalette::Active,QPalette::Window,QColor(215,215,215));
    windowPalette.setColor(QPalette::Inactive,QPalette::Window,QColor(215,215,215));
    setPalette(windowPalette);

    //------------------

    fileName=tr("Untitled.cpp");
    filePath=tr("./Untitled.cpp");
    fileSaved=true;

    connect(ui->actionNewFile,SIGNAL(triggered(bool)),this,SLOT(newFile()));
    connect(ui->actionOpen,SIGNAL(triggered(bool)),this,SLOT(openFile()));
    connect(ui->editor,SIGNAL(textChanged()),this,SLOT(changeSaveState()));
    connect(ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(about()));

    connect(ui->actionSave_File,SIGNAL(triggered(bool)),this,SLOT(saveFile()));

    connect(ui->editor, SIGNAL(cursorPositionChanged()), this, SLOT(updateStatusString()));

    fileSaved=true;

    // Ищем дступные стили
    QDir directory("./");
    QStringList styles = directory.entryList(QStringList() << "*.style",QDir::Files);

    foreach(QString filename, styles) {
        QAction *act = new QAction(filename.left(filename.length()-6),this);
        connect(act, SIGNAL(triggered()), this, SLOT(LoadStyle()));
        ui->menu_5->addAction(act);
    }
}

void MainWindow::LoadStyle() {
    ui->editor->loadStyle(((QAction*)sender())->text() + tr(".style"));
}

void MainWindow::setUndoAvailable(bool flag) {
    ui->actionUndo->setEnabled(flag);
}

void MainWindow::setRedoAvailable(bool flag) {
    ui->actionRedo->setEnabled(flag);
}

void MainWindow::setCopyAvailable(bool flag) {
    ui->actionCopy->setEnabled(flag);
    ui->actionCut->setEnabled(flag);
}

void MainWindow::updateStatusString() {
    QString status = tr("(")+QString::number(ui->editor->textCursor().blockNumber())+tr(":")+
            QString::number(ui->editor->textCursor().columnNumber())+tr("); ");

    if (ui->editor->changesWereMade) {
        if(ui->editor->lastchanges.date().day()<QDateTime::currentDateTime().date().day()) // последнее изменение было не сегодня
            status += ui->editor->lastchanges.toString("Последнее сохранение: dd.MM.yyyy hh:mm:ss; ");
        else
            status += ui->editor->lastchanges.toString("Последнее сохранение: hh:mm:ss; ");
    }

    status += tr("строк: ") + QString::number(ui->editor->blockCount()) + tr(", ");

    // Количество слов
    int wordCount = ui->editor->toPlainText().split(QRegularExpression("(\\s|\\n|\\r)+"), Qt::SkipEmptyParts).count();

    status += tr("слов: ") + QString::number(wordCount) + tr(", ");

    int symbolCount = ui->editor->toPlainText().count();

    status += tr("символов: ") + QString::number(symbolCount) + tr(", ");
    status += tr("размер файла: ") + QString::number(symbolCount/1024) + tr("Кб");

    ui->statusBar->showMessage(status);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);
    calculateResize();
}

void MainWindow::calculateResize() {
    int totalHeight = height() - ui->menuBar->height();

    if(ui->actionInstrumentPanel->isChecked())
        totalHeight -= ui->mainToolBar->height();

    if(ui->actionStatusString->isChecked())
        totalHeight -= ui->statusBar->height();

    ui->editor->setGeometry(0,0,width(), totalHeight);
}

void MainWindow::newFile() {
    MainWindow *newWindow=new MainWindow();
    QRect newPos=this->geometry();
    newWindow->setGeometry(newPos.x()+10,newPos.y()+10,newPos.width(),newPos.height());
    newWindow->show();
}

void MainWindow::openFile() {
    if(!fileSaved && QMessageBox::Save==QMessageBox::question(this,tr("Сохранить"),tr("Сохранить файл \"")+filePath+tr("\"?"),QMessageBox::Save,QMessageBox::Cancel))
        saveFile();

    QString openPath=QFileDialog::getOpenFileName(this,tr("Открыть"),filePath,tr("Cpp File(*.cpp *.c *.h)"));
    if(!openPath.isEmpty()){
        QFile in(openPath);
        in.open(QIODevice::ReadOnly|QIODevice::Text);
        QTextStream str(&in);
        ui->editor->setPlainText(str.readAll());
        QRegularExpression re(tr("(?<=\\/)\\w+\\.cpp|(?<=\\/)\\w+\\.c|(?<=\\/)\\w+\\.h"));
        fileName=re.match(openPath).captured();
        setWindowTitle(tr("Текстовый редактор - ")+fileName);
        filePath=openPath;
        fileSaved=true;


        // Записали дату и время последнего сохранения
        ui->editor->lastchanges = QDateTime::currentDateTime();
        ui->editor->changesWereMade = true;
        updateStatusString();
    }
}

void MainWindow::saveFile(bool saveasflag) {
    if(!saveasflag) {
        QFileInfo check_file(filePath);
        saveasflag = !check_file.exists() || !check_file.isFile();
    }

    if(saveasflag) {
        filePath=QFileDialog::getSaveFileName(this,tr("Выберите название файла"),fileName,tr("Cpp File(*.cpp *.c *.h)"));
        QRegularExpression re(tr("(?<=\\/)\\w+\\.cpp|(?<=\\/)\\w+\\.c|(?<=\\/)\\w+\\.h"));
        fileName=re.match(filePath).captured();
    }

    QFile out(filePath);
    out.open(QIODevice::WriteOnly|QIODevice::Text);
    QTextStream str(&out);
    str << ui->editor->toPlainText();
    out.close();

    // Записали дату и время последнего сохранения
    ui->editor->lastchanges = QDateTime::currentDateTime();
    ui->editor->changesWereMade = true;
    updateStatusString();

    fileSaved=true;
    setWindowTitle(tr("Текстовый редактор - ")+fileName);
}

void MainWindow::closeEvent(QCloseEvent *event) {
    if(!fileSaved && QMessageBox::Save==QMessageBox::question(this,tr("Сохранить"),tr("Сохранить файл \"")+filePath+tr("\"?"),QMessageBox::Save,QMessageBox::Cancel))
        saveFile();
}

void MainWindow::about() {
    QMessageBox::information(this,tr("О программе"),tr("Здесь автор"),QMessageBox::Ok);
}

void MainWindow::on_actionExitApp_triggered() {
    exit(0);
}

void MainWindow::on_actionSaveAs_triggered() {
    saveFile(true); // true = Сохранить как
}

void MainWindow::on_actionWordWrap_triggered(bool checked)
{
    if(checked){
        ui->editor->setLineWrapMode(QPlainTextEdit::LineWrapMode::WidgetWidth);
    }else{
        ui->editor->setLineWrapMode(QPlainTextEdit::LineWrapMode::NoWrap);
    }
}

// Копировать
void MainWindow::on_actionCopy_triggered()
{
    ui->editor->copy();
}

// Вырезать
void MainWindow::on_actionCut_triggered()
{
    ui->editor->cut();
}

// Вставить
void MainWindow::on_actionPaste_triggered()
{
    ui->editor->paste();
}

// Выделить все
void MainWindow::on_actionSelectAll_triggered()
{
    ui->editor->selectAll();
}

// Найти
void MainWindow::on_actionFind_triggered()
{
    bool ok;
    QString findWord = QInputDialog::getText(this, tr("Найти"),
                                             tr("Найти:"), QLineEdit::Normal,
                                             "", &ok);
    if (ok){
        QList<QTextEdit::ExtraSelection> extraSelections;
        ui->editor->moveCursor(QTextCursor::Start);
        QTextEdit::ExtraSelection extra;
        extra.format.setFontUnderline(true);
        extra.format.setBackground(Qt::yellow);

        while (ui->editor->find(findWord))
        {
            extra.cursor = ui->editor->textCursor();
            extraSelections.append(extra);
        }

        ui->editor->setExtraSelections(extraSelections);
    }
}

// Найти и заменить
void MainWindow::on_actionFindReplace_triggered()
{
    bool ok;
    QString findWord = QInputDialog::getText(this, tr("Найти"),tr("Найти:"),
                                             QLineEdit::Normal,"", &ok);
    if (ok){
        QString replaceWord = QInputDialog::getText(this, tr("Заменить"), tr("Заменить:"),
                                                    QLineEdit::Normal,findWord, &ok);
        if (ok){

            QList<QTextEdit::ExtraSelection> extraSelections;
            ui->editor->moveCursor(QTextCursor::Start);
            QTextEdit::ExtraSelection extra;

            extra.format.setFontUnderline(true);
            extra.format.setBackground(Qt::yellow);

            while (ui->editor->find(findWord))
            {
                extra.cursor = ui->editor->textCursor();
                extra.cursor.insertText(replaceWord);

                extraSelections.append(extra);
            }

            ui->editor->setExtraSelections(extraSelections);
        }
    }
}

// Выбор шрифта
void MainWindow::on_actionFontChoose_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->editor->document()->defaultFont(), this);
    if (ok) ui->editor->document()->setDefaultFont(font);
}

// Выбор цвета фона
void MainWindow::on_actionBackgroundColor_triggered()
{
    QColor q = QColorDialog::getColor(ui->editor->backgroundColor, this);
    if(q.spec() ==QColor::Invalid)
        return;

    ui->editor->backgroundColor = q;
    ui->editor->updateBackgroundColor();
}

// Выбор цвета текущей строки
void MainWindow::on_actionCurrentLineColor_triggered()
{
    QColor q = QColorDialog::getColor(ui->editor->backgroundColor, this);
    if(q.spec() ==QColor::Invalid)
        return;

    ui->editor->lineColor = q;
    ui->editor->highlightCurrentLine();
}

void MainWindow::on_actionInstrumentPanel_triggered(bool checked)
{
    ui->mainToolBar->setVisible(checked);
    calculateResize();
}

// Строка состояния
void MainWindow::on_actionStatusString_triggered(bool checked)
{
    ui->statusBar->setVisible(checked);
    calculateResize();
}

// Подсветка синтаксиса
void MainWindow::on_actionSyntaxHighlight_triggered(bool checked)
{
    if(checked)
        highlighter.setDocument(ui->editor->document());
    else
        highlighter.setDocument(nullptr);
}

// Выбран синтаксис Си2011
void MainWindow::on_actionSyntaxC2011_triggered()
{
    ui->actionSyntaxCPP2014->setChecked(false);
    ui->actionSyntaxC2011->setChecked(true);
    highlighter.syntax = Highlighter::C2011;
    highlighter.setDocument(ui->editor->document());
}

// Выбран синтаксис Си++2014
void MainWindow::on_actionSyntaxCPP2014_triggered()
{
    ui->actionSyntaxCPP2014->setChecked(true);
    ui->actionSyntaxC2011->setChecked(false);
    highlighter.syntax = Highlighter::CPP2014;
    highlighter.setDocument(ui->editor->document());
}

void MainWindow::on_actionUndo_triggered()
{
    ui->editor->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->editor->redo();
}

void MainWindow::on_actionLineNumeration_triggered(bool checked)
{
    ui->editor->numeration = checked;
    ui->editor->updateLineNumberAreaWidth();
}

void MainWindow::on_actionDefaultSyntaxStyle_triggered()
{
    ui->editor->loadStyle(""); // загрузка стандартного стиля
}

void MainWindow::on_actionOpenSyntaxStyleFromFile_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"./","*.style");
    ui->editor->loadStyle(fileName); // загрузка пользовательского стиля
}

void MainWindow::on_actionChangeSyntaxStyle_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),"./","*.style");
    ui->editor->saveStyle(fileName);
}
