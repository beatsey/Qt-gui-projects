import os
from pathlib import Path
import sys

from PySide2.QtWidgets import QApplication, QMainWindow
from PySide2.QtCore import QFile
from PySide2.QtUiTools import QUiLoader
from controller import Controller

if __name__ == "__main__":
    app = QApplication(sys.argv)
    ui = Controller()
    ui.setupUi()
    ui.controller()
    ui.show()
    sys.exit(app.exec_())
