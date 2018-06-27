/********************************************************************************
** Form generated from reading UI file 'gazetrackgui.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAZETRACKGUI_H
#define UI_GAZETRACKGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "GazeDisplayWidget.h"

QT_BEGIN_NAMESPACE

class Ui_gazeTrackGUIClass
{
public:
    QAction *actionStart;
    QAction *actionRight_Video_Source;
    QAction *actionLeft_Video_Source;
    QAction *actionStart_Recording;
    QAction *actionStop_Recording;
    QAction *actionCapture_Settings;
    QAction *actionLeft_Right_Video_Source;
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    GazeDisplayWidget *widget;
    QLabel *statusLabelCamera;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menuSettings;
    QMenu *menuCapture;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *gazeTrackGUIClass)
    {
        if (gazeTrackGUIClass->objectName().isEmpty())
            gazeTrackGUIClass->setObjectName(QStringLiteral("gazeTrackGUIClass"));
        gazeTrackGUIClass->resize(1338, 576);
        actionStart = new QAction(gazeTrackGUIClass);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        actionRight_Video_Source = new QAction(gazeTrackGUIClass);
        actionRight_Video_Source->setObjectName(QStringLiteral("actionRight_Video_Source"));
        actionLeft_Video_Source = new QAction(gazeTrackGUIClass);
        actionLeft_Video_Source->setObjectName(QStringLiteral("actionLeft_Video_Source"));
        actionStart_Recording = new QAction(gazeTrackGUIClass);
        actionStart_Recording->setObjectName(QStringLiteral("actionStart_Recording"));
        actionStart_Recording->setCheckable(false);
        actionStop_Recording = new QAction(gazeTrackGUIClass);
        actionStop_Recording->setObjectName(QStringLiteral("actionStop_Recording"));
        actionStop_Recording->setCheckable(false);
        actionCapture_Settings = new QAction(gazeTrackGUIClass);
        actionCapture_Settings->setObjectName(QStringLiteral("actionCapture_Settings"));
        actionLeft_Right_Video_Source = new QAction(gazeTrackGUIClass);
        actionLeft_Right_Video_Source->setObjectName(QStringLiteral("actionLeft_Right_Video_Source"));
        actionLeft_Right_Video_Source->setCheckable(true);
        actionLeft_Right_Video_Source->setChecked(true);
        centralWidget = new QWidget(gazeTrackGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 0, 1301, 521));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new GazeDisplayWidget(verticalLayoutWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(640, 480));

        verticalLayout->addWidget(widget);

        statusLabelCamera = new QLabel(verticalLayoutWidget);
        statusLabelCamera->setObjectName(QStringLiteral("statusLabelCamera"));

        verticalLayout->addWidget(statusLabelCamera);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        gazeTrackGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(gazeTrackGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1338, 21));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QStringLiteral("menuSettings"));
        menuCapture = new QMenu(menuBar);
        menuCapture->setObjectName(QStringLiteral("menuCapture"));
        gazeTrackGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(gazeTrackGUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMinimumSize(QSize(50, 0));
        gazeTrackGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(gazeTrackGUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        gazeTrackGUIClass->setStatusBar(statusBar);

        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuCapture->menuAction());
        menuSettings->addAction(actionRight_Video_Source);
        menuSettings->addAction(actionLeft_Video_Source);
        menuSettings->addSeparator();
        menuSettings->addAction(actionLeft_Right_Video_Source);
        menuCapture->addAction(actionStart_Recording);
        menuCapture->addAction(actionStop_Recording);
        menuCapture->addAction(actionCapture_Settings);

        retranslateUi(gazeTrackGUIClass);

        QMetaObject::connectSlotsByName(gazeTrackGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *gazeTrackGUIClass)
    {
        gazeTrackGUIClass->setWindowTitle(QApplication::translate("gazeTrackGUIClass", "gazeTrackGUI", Q_NULLPTR));
        actionStart->setText(QApplication::translate("gazeTrackGUIClass", "Start", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionStart->setToolTip(QApplication::translate("gazeTrackGUIClass", "<html><head/><body><p><img src=\":/gazeTrackGUI/Resources/play_icon.png\"/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        actionRight_Video_Source->setText(QApplication::translate("gazeTrackGUIClass", "Right Video Source", Q_NULLPTR));
        actionLeft_Video_Source->setText(QApplication::translate("gazeTrackGUIClass", "Left Video Source", Q_NULLPTR));
        actionStart_Recording->setText(QApplication::translate("gazeTrackGUIClass", "Start Recording", Q_NULLPTR));
        actionStop_Recording->setText(QApplication::translate("gazeTrackGUIClass", "Stop Recording", Q_NULLPTR));
        actionCapture_Settings->setText(QApplication::translate("gazeTrackGUIClass", "Capture Settings", Q_NULLPTR));
        actionLeft_Right_Video_Source->setText(QApplication::translate("gazeTrackGUIClass", "Same left/right video", Q_NULLPTR));
        statusLabelCamera->setText(QApplication::translate("gazeTrackGUIClass", "TextLabel", Q_NULLPTR));
        menuSettings->setTitle(QApplication::translate("gazeTrackGUIClass", "Settings", Q_NULLPTR));
        menuCapture->setTitle(QApplication::translate("gazeTrackGUIClass", "Capture", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class gazeTrackGUIClass: public Ui_gazeTrackGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAZETRACKGUI_H
