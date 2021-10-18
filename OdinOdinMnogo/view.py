import os
from pathlib import Path
import sys

from PySide2.QtWidgets import QApplication, QMainWindow
from PySide2.QtCore import QFile, Qt
from PySide2.QtUiTools import QUiLoader

class Ui_MainWindow(object):


    def setupUi(self):
        # Загружаем UI из формы
        loader = QUiLoader()
        path = os.fspath(Path(__file__).resolve().parent / "form.ui")
        ui_file = QFile(path)
        ui_file.open(QFile.ReadOnly)
        self.ui=loader.load(ui_file)
        ui_file.close()

    def updateScore(self,x):
        self.ui.label_score.setText("Ошибок: {}".format(x))

    def viewRebus(self,rebus):
        # Отображаем новый ребус
        for i in range(2):
            for j in range(len(rebus[i][0])):
                o = getattr(self.ui,'textEdit_{}_{}'.format(i,j))
                o.setPlaceholderText(rebus[i][0][-1-j])
                o.setText('')
                o.setEnabled(True)
                o.setVisible(True)
                o.setAlignment(Qt.AlignCenter)

            for j in range(len(rebus[i][0]),5):
                o = getattr(self.ui,'textEdit_{}_{}'.format(i,j))
                o.setEnabled(False)
                o.setVisible(False)

        for j in range(len(rebus[2][0])):
            o = getattr(self.ui,'textEdit_2_{}'.format(j))
            o.setPlaceholderText(rebus[2][0][-1-j])
            o.setPlaceholderText(rebus[2][0][-1-j])
            o.setText('')
            o.setEnabled(True)
            o.setVisible(True)
            o.setAlignment(Qt.AlignCenter)

        for j in range(len(rebus[2][0]),6):
            o = getattr(self.ui,'textEdit_2_{}'.format(j))
            o.setEnabled(False)
            o.setVisible(False)

    def updateTextEditSuccess(self,i,j,success,value=None):
        o = getattr(self.ui,'textEdit_{}_{}'.format(i,j))

        if value != None:
            o.setText(value)

        if success:
            o.setStyleSheet('')
        else:
            o.setStyleSheet('background: red')

    def show(self):
        self.ui.show()
