/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *prevBtn;
    QPushButton *playBtn;
    QPushButton *nextBtn;
    QPushButton *modeBtn;
    QSlider *progressBar;
    QLabel *currentTime;
    QLabel *totalTime;
    QSlider *volumnBar;
    QPushButton *lowVolumnBtn;
    QPushButton *highVolumnBtn;
    QLabel *lyric;
    QListWidget *songList;
    QLabel *albumPicture;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1092, 687);
        QFont font;
        font.setPointSize(9);
        MainWindow->setFont(font);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        prevBtn = new QPushButton(centralWidget);
        prevBtn->setObjectName(QString::fromUtf8("prevBtn"));
        prevBtn->setGeometry(QRect(110, 525, 100, 51));
        playBtn = new QPushButton(centralWidget);
        playBtn->setObjectName(QString::fromUtf8("playBtn"));
        playBtn->setGeometry(QRect(240, 525, 100, 51));
        nextBtn = new QPushButton(centralWidget);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));
        nextBtn->setGeometry(QRect(370, 525, 100, 52));
        modeBtn = new QPushButton(centralWidget);
        modeBtn->setObjectName(QString::fromUtf8("modeBtn"));
        modeBtn->setGeometry(QRect(510, 525, 100, 51));
        progressBar = new QSlider(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(110, 485, 501, 22));
        progressBar->setOrientation(Qt::Horizontal);
        currentTime = new QLabel(centralWidget);
        currentTime->setObjectName(QString::fromUtf8("currentTime"));
        currentTime->setGeometry(QRect(90, 465, 72, 15));
        totalTime = new QLabel(centralWidget);
        totalTime->setObjectName(QString::fromUtf8("totalTime"));
        totalTime->setGeometry(QRect(560, 465, 72, 15));
        volumnBar = new QSlider(centralWidget);
        volumnBar->setObjectName(QString::fromUtf8("volumnBar"));
        volumnBar->setGeometry(QRect(740, 485, 160, 22));
        volumnBar->setOrientation(Qt::Horizontal);
        lowVolumnBtn = new QPushButton(centralWidget);
        lowVolumnBtn->setObjectName(QString::fromUtf8("lowVolumnBtn"));
        lowVolumnBtn->setGeometry(QRect(690, 485, 41, 28));
        highVolumnBtn = new QPushButton(centralWidget);
        highVolumnBtn->setObjectName(QString::fromUtf8("highVolumnBtn"));
        highVolumnBtn->setGeometry(QRect(910, 485, 41, 28));
        lyric = new QLabel(centralWidget);
        lyric->setObjectName(QString::fromUtf8("lyric"));
        lyric->setGeometry(QRect(90, 390, 541, 61));
        QFont font1;
        font1.setPointSize(15);
        lyric->setFont(font1);
        songList = new QListWidget(centralWidget);
        songList->setObjectName(QString::fromUtf8("songList"));
        songList->setGeometry(QRect(110, 70, 501, 241));
        songList->setFont(font1);
        albumPicture = new QLabel(centralWidget);
        albumPicture->setObjectName(QString::fromUtf8("albumPicture"));
        albumPicture->setGeometry(QRect(670, 70, 351, 261));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1092, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        prevBtn->setText(QString());
        playBtn->setText(QString());
        nextBtn->setText(QString());
        modeBtn->setText(QString());
        currentTime->setText(QApplication::translate("MainWindow", "0:00", nullptr));
        totalTime->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        lowVolumnBtn->setText(QString());
        highVolumnBtn->setText(QString());
        lyric->setText(QString());
        albumPicture->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
