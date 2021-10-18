from model import Model


class Controller(Model):
    def _connectAll(self):
        def funcTextChanged(i,j):
            self._disconnectAll()
            self.check(i,j,getattr(self.ui,'textEdit_{}_{}'.format(i,j)).toPlainText())
            self._connectAll()

        self.ui.textEdit_0_0.textChanged.connect(lambda: funcTextChanged(0,0))
        self.ui.textEdit_0_1.textChanged.connect(lambda: funcTextChanged(0,1))
        self.ui.textEdit_0_2.textChanged.connect(lambda: funcTextChanged(0,2))
        self.ui.textEdit_0_3.textChanged.connect(lambda: funcTextChanged(0,3))
        self.ui.textEdit_0_4.textChanged.connect(lambda: funcTextChanged(0,4))

        self.ui.textEdit_1_0.textChanged.connect(lambda: funcTextChanged(1,0))
        self.ui.textEdit_1_1.textChanged.connect(lambda: funcTextChanged(1,1))
        self.ui.textEdit_1_2.textChanged.connect(lambda: funcTextChanged(1,2))
        self.ui.textEdit_1_3.textChanged.connect(lambda: funcTextChanged(1,3))
        self.ui.textEdit_1_4.textChanged.connect(lambda: funcTextChanged(1,4))

        self.ui.textEdit_2_0.textChanged.connect(lambda: funcTextChanged(2,0))
        self.ui.textEdit_2_1.textChanged.connect(lambda: funcTextChanged(2,1))
        self.ui.textEdit_2_2.textChanged.connect(lambda: funcTextChanged(2,2))
        self.ui.textEdit_2_3.textChanged.connect(lambda: funcTextChanged(2,3))
        self.ui.textEdit_2_4.textChanged.connect(lambda: funcTextChanged(2,4))
        self.ui.textEdit_2_5.textChanged.connect(lambda: funcTextChanged(2,5))


    def _disconnectAll(self):
        self.ui.textEdit_0_0.textChanged.disconnect()
        self.ui.textEdit_0_1.textChanged.disconnect()
        self.ui.textEdit_0_2.textChanged.disconnect()
        self.ui.textEdit_0_3.textChanged.disconnect()
        self.ui.textEdit_0_4.textChanged.disconnect()

        self.ui.textEdit_1_0.textChanged.disconnect()
        self.ui.textEdit_1_1.textChanged.disconnect()
        self.ui.textEdit_1_2.textChanged.disconnect()
        self.ui.textEdit_1_3.textChanged.disconnect()
        self.ui.textEdit_1_4.textChanged.disconnect()

        self.ui.textEdit_2_0.textChanged.disconnect()
        self.ui.textEdit_2_1.textChanged.disconnect()
        self.ui.textEdit_2_2.textChanged.disconnect()
        self.ui.textEdit_2_3.textChanged.disconnect()
        self.ui.textEdit_2_4.textChanged.disconnect()
        self.ui.textEdit_2_5.textChanged.disconnect()

    def controller(self):
        self.ui.pushButton.clicked.connect(self.generateAndViewRebus)
        self._connectAll()

        # Отображаем некоторый случайный ребус
        self.generateAndViewRebus()



        """
        self.pushButton_18.clicked.connect(lambda: self.add_char(self.pushButton_18.text()))
        self.pushButton_20.clicked.connect(lambda: self.add_char(self.pushButton_20.text()))
        self.pushButton_22.clicked.connect(lambda: self.add_char(self.pushButton_22.text()))
        self.pushButton_23.clicked.connect(lambda: self.add_char(self.pushButton_23.text()))
        self.pushButton_24.clicked.connect(lambda: self.add_char(self.pushButton_24.text()))
        self.pushButton_25.clicked.connect(lambda: self.add_char(self.pushButton_25.text()))
        self.pushButton_27.clicked.connect(lambda: self.add_char(self.pushButton_27.text()))
        self.pushButton_28.clicked.connect(lambda: self.add_char(self.pushButton_28.text()))
        self.pushButton_29.clicked.connect(lambda: self.add_char(self.pushButton_29.text()))
        self.pushButton_30.clicked.connect(lambda: self.add_char(self.pushButton_30.text()))
        self.pushButton_32.clicked.connect(lambda: self.add_char(self.pushButton_32.text()))
        self.pushButton_33.clicked.connect(lambda: self.add_char(self.pushButton_33.text()))
        self.pushButton_34.clicked.connect(lambda: self.add_char(self.pushButton_34.text()))
        self.pushButton_35.clicked.connect(lambda: self.add_char(self.pushButton_35.text()))
        self.pushButton_38.clicked.connect(lambda: self.add_char(self.pushButton_38.text()))
        self.pushButton_39.clicked.connect(lambda: self.add_char(self.pushButton_39.text()))
        self.pushButton.clicked.connect(lambda: self.M_op(self.pushButton.text()))
        self.pushButton_2.clicked.connect(lambda: self.M_op(self.pushButton_2.text()))
        self.pushButton_3.clicked.connect(lambda: self.M_op(self.pushButton_3.text()))
        self.pushButton_4.clicked.connect(lambda: self.M_op(self.pushButton_4.text()))
        self.pushButton_5.clicked.connect(lambda: self.M_op(self.pushButton_5.text()))
        self.pushButton_40.clicked.connect(lambda: self.get_result())
        self.pushButton_7.clicked.connect(lambda: self.pi())
        self.pushButton_8.clicked.connect(lambda: self.e())
        self.pushButton_9.clicked.connect(lambda: self.delete(self.pushButton_9.text()))
        self.pushButton_10.clicked.connect(lambda: self.delete(self.pushButton_10.text()))
        self.pushButton_16.clicked.connect(lambda: self.sqrt())
        self.pushButton_37.clicked.connect(lambda: self.abs())

        self.comboBox.activated.connect(lambda: self.show_combo_text(self.comboBox.currentText()))
        self.comboBox_2.activated.connect(lambda: self.show_combo_text2(self.comboBox_2.currentText()))

        self.pushButton_14.clicked.connect(lambda: self.exp())
        self.pushButton_31.clicked.connect(lambda: self.log())
        self.pushButton_36.clicked.connect(lambda: self.ln())
        self.pushButton_26.clicked.connect(lambda: self.pow(self.pushButton_26.text()))
        self.pushButton_11.clicked.connect(lambda: self.pow(self.pushButton_11.text()))
        self.pushButton_21.clicked.connect(lambda: self.pow(self.pushButton_21.text()))
        self.pushButton_12.clicked.connect(lambda: self.delenie())
        self.pushButton_15.clicked.connect(lambda: self.mod())
        self.pushButton_13.clicked.connect(lambda: self.modyl())
        self.pushButton_41.clicked.connect(lambda: self.save())
        """

        pass
