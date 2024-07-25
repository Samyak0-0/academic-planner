/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QWidget *sidebar;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QPushButton *RoutineBut;
    QPushButton *SyllabusBut;
    QPushButton *ToDoBut;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *RoutinePage;
    QWidget *ToDoPage;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *tasktextbox;
    QPushButton *AddTaskBut;
    QListWidget *listWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *DeleteTaskBut;
    QPushButton *DeleteAllTasksBut;
    QWidget *page;
    QWidget *SyllabusPage;
    QWidget *page_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(952, 746);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background-color:rgb(206, 217, 255);\n"
""));
        horizontalLayout_5 = new QHBoxLayout(centralwidget);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        sidebar = new QWidget(centralwidget);
        sidebar->setObjectName("sidebar");
        QSizePolicy sizePolicy(QSizePolicy::Policy::MinimumExpanding, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sidebar->sizePolicy().hasHeightForWidth());
        sidebar->setSizePolicy(sizePolicy);
        sidebar->setMaximumSize(QSize(250, 10000));
        sidebar->setLayoutDirection(Qt::LeftToRight);
        sidebar->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	background-color:rgb(206, 217, 255)\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(sidebar);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(4, 4, 4, 4);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(20);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 30, -1, 30);
        horizontalSpacer = new QSpacerItem(24, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(sidebar);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(50, 50));
        label_2->setMaximumSize(QSize(50, 50));
        label_2->setStyleSheet(QString::fromUtf8("color:black\n"
""));
        label_2->setPixmap(QPixmap(QString::fromUtf8("images/routineicon.png")));
        label_2->setScaledContents(true);

        horizontalLayout->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(32, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(22);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(-1, 10, -1, -1);
        RoutineBut = new QPushButton(sidebar);
        RoutineBut->setObjectName("RoutineBut");
        RoutineBut->setMinimumSize(QSize(30, 20));
        QFont font;
        font.setFamilies({QString::fromUtf8("Algerian")});
        font.setPointSize(12);
        font.setBold(true);
        font.setItalic(false);
        RoutineBut->setFont(font);
        RoutineBut->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	padding:6px;\n"
"	border:none;\n"
"	text-align:left;\n"
"	font:bold;\n"
"	color:rgb(62, 44, 70);\n"
"	padding-left:18px;\n"
"	border-radius:16px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgb(254, 255, 244);\n"
"	color:rgb(43, 48, 44)\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("images/syllabusicon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        RoutineBut->setIcon(icon);
        RoutineBut->setIconSize(QSize(38, 38));
        RoutineBut->setCheckable(true);
        RoutineBut->setAutoExclusive(true);

        verticalLayout->addWidget(RoutineBut);

        SyllabusBut = new QPushButton(sidebar);
        SyllabusBut->setObjectName("SyllabusBut");
        SyllabusBut->setMinimumSize(QSize(30, 20));
        SyllabusBut->setFont(font);
        SyllabusBut->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	padding:7px;\n"
"	border:none;\n"
"	text-align:left;\n"
"	font:bold;\n"
"	color:rgb(62, 44, 70);\n"
"	padding-left:18px;\n"
"	border-radius:16px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgb(254, 255, 244);\n"
"	color:rgb(43, 48, 44)\n"
"}"));
        SyllabusBut->setIcon(icon);
        SyllabusBut->setIconSize(QSize(34, 34));
        SyllabusBut->setCheckable(true);
        SyllabusBut->setAutoExclusive(true);

        verticalLayout->addWidget(SyllabusBut);

        ToDoBut = new QPushButton(sidebar);
        ToDoBut->setObjectName("ToDoBut");
        ToDoBut->setMinimumSize(QSize(40, 30));
        ToDoBut->setFont(font);
        ToDoBut->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	padding:7px;\n"
"	border:none;\n"
"	text-align:left;\n"
"	font:bold;\n"
"	color:rgb(62, 44, 70);\n"
"	padding-left:18px;\n"
"	border-radius:16px;\n"
"}\n"
"QPushButton:checked{\n"
"	background-color:rgb(254, 255, 244);\n"
"	color:rgb(43, 48, 44)\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("images/todolisticon.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        ToDoBut->setIcon(icon1);
        ToDoBut->setIconSize(QSize(34, 34));
        ToDoBut->setCheckable(true);
        ToDoBut->setAutoExclusive(true);

        verticalLayout->addWidget(ToDoBut);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_3->addLayout(verticalLayout);


        horizontalLayout_3->addWidget(sidebar);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"background-color:rgb(255, 238, 239);\n"
"border-radius:30px\n"
"}"));
        RoutinePage = new QWidget();
        RoutinePage->setObjectName("RoutinePage");
        stackedWidget->addWidget(RoutinePage);
        ToDoPage = new QWidget();
        ToDoPage->setObjectName("ToDoPage");
        verticalLayout_2 = new QVBoxLayout(ToDoPage);
        verticalLayout_2->setSpacing(10);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(22, 20, 30, 20);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        tasktextbox = new QLineEdit(ToDoPage);
        tasktextbox->setObjectName("tasktextbox");
        tasktextbox->setMinimumSize(QSize(300, 50));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial Black")});
        font1.setPointSize(10);
        font1.setBold(true);
        tasktextbox->setFont(font1);
        tasktextbox->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"background:rgb(255, 251, 251);\n"
"border: 2px solid gray;\n"
" border-radius: 10px;\n"
"}"));

        horizontalLayout_4->addWidget(tasktextbox);

        AddTaskBut = new QPushButton(ToDoPage);
        AddTaskBut->setObjectName("AddTaskBut");
        AddTaskBut->setMinimumSize(QSize(90, 50));
        AddTaskBut->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
"border-radius: 10px;\n"
"background-color:rgb(255, 255, 255);\n"
"font:bold;\n"
"color:black;\n"
""));

        horizontalLayout_4->addWidget(AddTaskBut);


        verticalLayout_2->addLayout(horizontalLayout_4);

        listWidget = new QListWidget(ToDoPage);
        listWidget->setObjectName("listWidget");
        listWidget->setFont(font1);
        listWidget->setStyleSheet(QString::fromUtf8("QListWidget{\n"
"padding-top:10px;\n"
"padding-left:10px;\n"
"background:rgb(255, 251, 251);\n"
"border: 2px solid gray;\n"
" border-radius: 25px;\n"
"}"));

        verticalLayout_2->addWidget(listWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        DeleteTaskBut = new QPushButton(ToDoPage);
        DeleteTaskBut->setObjectName("DeleteTaskBut");
        DeleteTaskBut->setMinimumSize(QSize(120, 45));
        DeleteTaskBut->setMaximumSize(QSize(1000, 800));
        DeleteTaskBut->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
"border-radius: 10px;\n"
"background-color:rgb(255, 255, 255);\n"
"font:bold;\n"
"color:black;\n"
""));

        horizontalLayout_2->addWidget(DeleteTaskBut);

        DeleteAllTasksBut = new QPushButton(ToDoPage);
        DeleteAllTasksBut->setObjectName("DeleteAllTasksBut");
        DeleteAllTasksBut->setMinimumSize(QSize(120, 45));
        DeleteAllTasksBut->setMaximumSize(QSize(1000, 800));
        DeleteAllTasksBut->setStyleSheet(QString::fromUtf8("border: 2px solid gray;\n"
"border-radius: 10px;\n"
"background-color:rgb(255, 255, 255);\n"
"font:bold;\n"
"color:black;\n"
""));

        horizontalLayout_2->addWidget(DeleteAllTasksBut);


        verticalLayout_2->addLayout(horizontalLayout_2);

        stackedWidget->addWidget(ToDoPage);
        page = new QWidget();
        page->setObjectName("page");
        stackedWidget->addWidget(page);
        SyllabusPage = new QWidget();
        SyllabusPage->setObjectName("SyllabusPage");
        stackedWidget->addWidget(SyllabusPage);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        stackedWidget->addWidget(page_2);

        horizontalLayout_3->addWidget(stackedWidget);


        horizontalLayout_5->addLayout(horizontalLayout_3);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QString());
        RoutineBut->setText(QCoreApplication::translate("MainWindow", " Routine", nullptr));
        SyllabusBut->setText(QCoreApplication::translate("MainWindow", " Syllabus", nullptr));
        ToDoBut->setText(QCoreApplication::translate("MainWindow", " ToDo", nullptr));
        AddTaskBut->setText(QCoreApplication::translate("MainWindow", "AddTask", nullptr));
        DeleteTaskBut->setText(QCoreApplication::translate("MainWindow", "Delete Task", nullptr));
        DeleteAllTasksBut->setText(QCoreApplication::translate("MainWindow", "Delete All Tasks", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
