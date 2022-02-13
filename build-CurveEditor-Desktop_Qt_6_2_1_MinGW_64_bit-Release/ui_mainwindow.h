/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>
#include "qpointtablewidget.h"
#include "sgraph2dwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    SGraph2dWidget *graph_widget;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPointTableWidget *twPoints;
    QPushButton *pbDeletePoint;
    QPushButton *pbPolygon;
    QCheckBox *cbOnFlyRebuild;
    QPushButton *pBCubicCurve;
    QPushButton *pbTriangle;
    QPushButton *pbNewControlLine;
    QCheckBox *cBDeriv;
    QPushButton *pbHermitCurve;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpinBox *sBpolygonCount;
    QCheckBox *cbShowBroken;
    QPushButton *pbLagrange;
    QPushButton *pBevolute;
    QPushButton *pbDelaunay;
    QPushButton *pbRotate;
    QPushButton *pBrationalBezier;
    QPushButton *phHermitEnergy;
    QPushButton *pbBezierCurve;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1020, 650);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        graph_widget = new SGraph2dWidget(centralWidget);
        graph_widget->setObjectName(QString::fromUtf8("graph_widget"));

        gridLayout_2->addWidget(graph_widget, 0, 0, 1, 1);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(300, 0));
        groupBox->setLayoutDirection(Qt::LeftToRight);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(3);
        gridLayout->setContentsMargins(3, 3, 3, 3);
        twPoints = new QPointTableWidget(groupBox);
        if (twPoints->columnCount() < 2)
            twPoints->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        twPoints->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        twPoints->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        twPoints->setObjectName(QString::fromUtf8("twPoints"));
        twPoints->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twPoints->sizePolicy().hasHeightForWidth());
        twPoints->setSizePolicy(sizePolicy1);
        twPoints->setMinimumSize(QSize(0, 0));
        twPoints->setLayoutDirection(Qt::LeftToRight);
        twPoints->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        twPoints->setEditTriggers(QAbstractItemView::DoubleClicked);
        twPoints->setProperty("showDropIndicator", QVariant(false));
        twPoints->setDragEnabled(false);
        twPoints->setDragDropOverwriteMode(false);
        twPoints->setDragDropMode(QAbstractItemView::NoDragDrop);
        twPoints->setAlternatingRowColors(false);
        twPoints->setSelectionMode(QAbstractItemView::SingleSelection);
        twPoints->setSelectionBehavior(QAbstractItemView::SelectItems);
        twPoints->setShowGrid(true);
        twPoints->setCornerButtonEnabled(false);
        twPoints->setRowCount(0);
        twPoints->setColumnCount(2);
        twPoints->horizontalHeader()->setCascadingSectionResizes(false);
        twPoints->horizontalHeader()->setMinimumSectionSize(120);
        twPoints->horizontalHeader()->setDefaultSectionSize(120);
        twPoints->horizontalHeader()->setHighlightSections(false);
        twPoints->horizontalHeader()->setStretchLastSection(true);
        twPoints->verticalHeader()->setVisible(false);
        twPoints->verticalHeader()->setMinimumSectionSize(24);
        twPoints->verticalHeader()->setDefaultSectionSize(24);
        twPoints->verticalHeader()->setHighlightSections(false);
        twPoints->verticalHeader()->setStretchLastSection(false);

        gridLayout->addWidget(twPoints, 0, 0, 1, 2);

        pbDeletePoint = new QPushButton(groupBox);
        pbDeletePoint->setObjectName(QString::fromUtf8("pbDeletePoint"));

        gridLayout->addWidget(pbDeletePoint, 3, 1, 1, 1);

        pbPolygon = new QPushButton(groupBox);
        pbPolygon->setObjectName(QString::fromUtf8("pbPolygon"));

        gridLayout->addWidget(pbPolygon, 8, 0, 1, 1);

        cbOnFlyRebuild = new QCheckBox(groupBox);
        cbOnFlyRebuild->setObjectName(QString::fromUtf8("cbOnFlyRebuild"));
        cbOnFlyRebuild->setChecked(true);

        gridLayout->addWidget(cbOnFlyRebuild, 2, 0, 1, 1);

        pBCubicCurve = new QPushButton(groupBox);
        pBCubicCurve->setObjectName(QString::fromUtf8("pBCubicCurve"));

        gridLayout->addWidget(pBCubicCurve, 12, 0, 1, 1);

        pbTriangle = new QPushButton(groupBox);
        pbTriangle->setObjectName(QString::fromUtf8("pbTriangle"));

        gridLayout->addWidget(pbTriangle, 10, 0, 1, 1);

        pbNewControlLine = new QPushButton(groupBox);
        pbNewControlLine->setObjectName(QString::fromUtf8("pbNewControlLine"));

        gridLayout->addWidget(pbNewControlLine, 3, 0, 1, 1);

        cBDeriv = new QCheckBox(groupBox);
        cBDeriv->setObjectName(QString::fromUtf8("cBDeriv"));
        cBDeriv->setEnabled(false);

        gridLayout->addWidget(cBDeriv, 12, 1, 1, 1);

        pbHermitCurve = new QPushButton(groupBox);
        pbHermitCurve->setObjectName(QString::fromUtf8("pbHermitCurve"));

        gridLayout->addWidget(pbHermitCurve, 14, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        sBpolygonCount = new QSpinBox(groupBox);
        sBpolygonCount->setObjectName(QString::fromUtf8("sBpolygonCount"));
        sBpolygonCount->setFocusPolicy(Qt::NoFocus);
        sBpolygonCount->setContextMenuPolicy(Qt::NoContextMenu);
        sBpolygonCount->setToolTipDuration(0);
        sBpolygonCount->setReadOnly(false);
        sBpolygonCount->setSpecialValueText(QString::fromUtf8(""));
        sBpolygonCount->setMinimum(3);

        horizontalLayout->addWidget(sBpolygonCount);


        gridLayout->addLayout(horizontalLayout, 8, 1, 1, 1);

        cbShowBroken = new QCheckBox(groupBox);
        cbShowBroken->setObjectName(QString::fromUtf8("cbShowBroken"));
        cbShowBroken->setChecked(true);

        gridLayout->addWidget(cbShowBroken, 2, 1, 1, 1);

        pbLagrange = new QPushButton(groupBox);
        pbLagrange->setObjectName(QString::fromUtf8("pbLagrange"));

        gridLayout->addWidget(pbLagrange, 15, 0, 1, 1);

        pBevolute = new QPushButton(groupBox);
        pBevolute->setObjectName(QString::fromUtf8("pBevolute"));

        gridLayout->addWidget(pBevolute, 4, 0, 1, 1);

        pbDelaunay = new QPushButton(groupBox);
        pbDelaunay->setObjectName(QString::fromUtf8("pbDelaunay"));

        gridLayout->addWidget(pbDelaunay, 4, 1, 1, 1);

        pbRotate = new QPushButton(groupBox);
        pbRotate->setObjectName(QString::fromUtf8("pbRotate"));

        gridLayout->addWidget(pbRotate, 11, 0, 1, 1);

        pBrationalBezier = new QPushButton(groupBox);
        pBrationalBezier->setObjectName(QString::fromUtf8("pBrationalBezier"));

        gridLayout->addWidget(pBrationalBezier, 11, 1, 1, 1);

        phHermitEnergy = new QPushButton(groupBox);
        phHermitEnergy->setObjectName(QString::fromUtf8("phHermitEnergy"));

        gridLayout->addWidget(phHermitEnergy, 15, 1, 1, 1);

        pbBezierCurve = new QPushButton(groupBox);
        pbBezierCurve->setObjectName(QString::fromUtf8("pbBezierCurve"));

        gridLayout->addWidget(pbBezierCurve, 14, 1, 1, 1);


        gridLayout_2->addWidget(groupBox, 0, 1, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200 \320\272\321\200\320\270\320\262\321\213\321\205", nullptr));
        groupBox->setTitle(QString());
        QTableWidgetItem *___qtablewidgetitem = twPoints->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = twPoints->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        pbDeletePoint->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\202\320\276\321\207\320\272\320\270", nullptr));
        pbPolygon->setText(QCoreApplication::translate("MainWindow", "\320\242\320\276\321\207\320\272\320\260 \320\262\320\275\321\203\321\202\321\200\320\270 \320\274\320\275\320\276\320\263\320\276\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\260", nullptr));
        cbOnFlyRebuild->setText(QCoreApplication::translate("MainWindow", "\320\240\320\270\321\201\320\276\320\262\320\260\321\202\321\214 \320\275\320\260 \321\205\320\276\320\264\321\203", nullptr));
        pBCubicCurve->setText(QCoreApplication::translate("MainWindow", "\320\232\321\203\320\261\320\270\321\207\320\265\321\201\320\272\320\270\320\271 \321\201\320\277\320\273\320\260\320\271\320\275", nullptr));
        pbTriangle->setText(QCoreApplication::translate("MainWindow", "\320\242\320\276\321\207\320\272\320\260 \320\262\320\275\321\203\321\202\321\200\320\270 \321\202\321\200\320\265\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\260", nullptr));
        pbNewControlLine->setText(QCoreApplication::translate("MainWindow", "\320\227\320\260\320\264\320\260\321\202\321\214 \321\202\320\276\321\207\320\272\320\270", nullptr));
        cBDeriv->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\276\320\270\320\267\320\262\320\276\320\264\320\275\321\213\320\265 / \320\222\320\265\321\201\320\260", nullptr));
        pbHermitCurve->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\273\320\260\320\271\320\275 \320\255\321\200\320\274\320\270\321\202\320\260", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\222\320\265\321\200\321\210\320\270\320\275\321\213", nullptr));
#if QT_CONFIG(tooltip)
        sBpolygonCount->setToolTip(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273-\320\262\320\276 \320\262\320\265\321\200\321\210\320\270\320\275", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        sBpolygonCount->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        sBpolygonCount->setSuffix(QString());
        sBpolygonCount->setPrefix(QString());
        cbShowBroken->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\272\320\260\320\267\321\213\320\262\320\260\321\202\321\214 \320\273\320\276\320\274\320\260\320\275\321\203\321\216", nullptr));
        pbLagrange->setText(QCoreApplication::translate("MainWindow", "\320\241\320\277\320\273\320\260\320\271\320\275 \320\233\320\260\320\263\321\200\320\260\320\275\320\266\320\260", nullptr));
        pBevolute->setText(QCoreApplication::translate("MainWindow", "\320\255\320\262\320\276\320\273\321\216\321\202\320\260", nullptr));
        pbDelaunay->setText(QCoreApplication::translate("MainWindow", "\320\242\321\200\320\270\320\260\320\275\320\263\321\203\320\273\321\217\321\206\320\270\321\217 \320\224\320\265\320\273\320\276\320\275\320\265", nullptr));
        pbRotate->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\265\320\264\320\270\320\272\320\260\321\202 \320\277\320\276\320\262\320\276\321\200\320\276\321\202\320\260", nullptr));
        pBrationalBezier->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\206. \320\272\321\200\320\270\320\262\320\260\321\217 \320\221\320\265\320\267\321\214\320\265", nullptr));
        phHermitEnergy->setText(QCoreApplication::translate("MainWindow", "\320\237\321\201\320\265\320\262\320\264\320\276\321\203\320\277\321\200\321\203\320\263\320\270\320\271", nullptr));
        pbBezierCurve->setText(QCoreApplication::translate("MainWindow", "\320\232\321\200\320\270\320\262\320\260\321\217 \320\221\320\265\320\267\321\214\320\265", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
