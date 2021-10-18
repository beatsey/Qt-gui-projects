from view import Ui_MainWindow
import math
import random

class Model(Ui_MainWindow):
    def __init__(self):
        self.__rebuses=[
            [("ОДИН",'6823'),("ОДИН",'6823'),("МНОГО",'13646')],
            [("BB",'99'),("BB",'99'),("ABC",'198')],
            [("AS",'92'),("A",'9'),("MOM",'101')],
            [("EAT",'819'),("THAT",'9219'),("APPLE",'10038')],
            [("ВЕТКА",'74235'),("ВЕТКА",'74235'),("ДЕРЕВО",'148470')],
            [("РЮМКА",'85931'),("РЮМКА",'85931'),("АВАРИЯ",'171862')],
            [("СЛОВО",'14565'),("СЛОВО",'14565'),("ПЕСНЯ",'29130')],
            [("АЛЬДЕ",'50316'),("БАРАН",'45752'),("ТЕЛЕЦ",'96068')],
            [("КАПЛЯ",'35486'),("КАПЛЯ",'35486'),("ДОЖДЬ",'70972')],
            [("ОХОХО",'90909'),("АХАХА",'10101'),("АХАХАХ",'101010')],
            [("БАЛЕТ",'23674'),("БАЛЕТ",'23674'),("ТЕАТР",'47348')]
        ]
        self.score=0

    def generateAndViewRebus(self):
        self.rebus = self.__rebuses[random.randint(0,len(self.__rebuses)-1)]
        self.viewRebus(self.rebus)
        self.updateScore(0)
        self.score=0

    def check(self,i,j,text):
        flag = (self.rebus[i][1][-1-j]==text) or (text=='')
        for k in range(3):
            for m in range(len(self.rebus[k][1])):
                if self.rebus[k][1][-1-m]==self.rebus[i][1][-1-j]:
                    self.updateTextEditSuccess(k,m,flag,value=text)

        if not flag:
            self.score+=1
            self.updateScore(self.score)
