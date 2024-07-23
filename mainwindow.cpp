#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QApplication>
#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QWidget>
#include <QtGui>
#include <QColor>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>


#include <QFile>
#include <QMessageBox>

#include <QLineEdit>
#include <QComboBox>
#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <Qurl>
#include <QtNetwork/QtNetwork>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QListView>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    toDoList = new ToDoList(ui->listWidget,
                            ui->tasktextbox,
                            ui->AddTaskBut,
                            ui->DeleteTaskBut,
                            ui->DeleteAllTasksBut,
                            this);
    //Initializing todolist w/ the widgets from the main window ui

    //first page to be routine page
    ui->stackedWidget->setCurrentIndex(0);

    /*
    //doing in inside the constructor
    //storing tododlist data
    QFile file(path);

    //if no file create it.
    if(!file.open(QIODevice::ReadWrite)){
        QMessageBox::information(0,"Error",file.errorString());
    }

    //file from QFile file., accessing textstream
    QTextStream filein(&file);

    //reading item from the file same syntax as in reading from textbox
    while(!filein.atEnd()){
        QListWidgetItem* item = new QListWidgetItem(filein.readLine(),ui->listWidget);
        ui->listWidget->addItem(item);
    }
    file.close();
    */


    TableWidgetDisplay();
    selectionForm();

}

MainWindow::~MainWindow()
{
    //this destructor might be being called first (delete ui part)
    //before todolist destructor so cant put it in the todolist.cpp at the moment!
    //using destructor to ig save data to the file
    QFile file(path);

    //if no file create it. !!WRITEONLY!!!
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(0, "Error", file.errorString());
    }

    //file from QFile file., accessing textstream
    QTextStream fileout(&file);

    //reading item from the file same syntax as in reading from textbox
    //everything similar upto here
    for (int i = 0; i < ui->listWidget->count(); ++i) {
        //similar to cout
        fileout << ui->listWidget->item(i)->text() << "\n";
    }

    file.close();

    delete ui;
}

int pageWidth;
//buttons to switch  betn pages in stacked widgets.

void MainWindow::on_RoutineBut_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_ToDoBut_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_SyllabusBut_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::TableWidgetDisplay() {


    QGridLayout *layout = new QGridLayout(this);
    QStringList daysOfWeek;
    daysOfWeek << " " << "Sunday" << "Monday" << "Tuesday" << "Wednesday"
               << "Thursday" << "Friday" << "Saturday";
    QStringList TimeofDay;
    TimeofDay << " " << "9-10" << "10-11" << "11-12" << "12-1"
              <<"1-2" << "2-3" << "3-4";

    QStackedWidget *stackedWidget = ui->stackedWidget;
    QWidget *page1 = stackedWidget->widget(0);
    pageWidth = page1->width();

    for(int i=0; i<=7; i++) {

        rowLayout[i] = new QGridLayout(this);

        for(int j=0; j<=7; j++) {

            courseCode[i][j] = new QPushButton("courseCode", this);
            courseCode[i][j]->setStyleSheet("QPushButton {border: none;}");

            if(i==0 && j==0){
                courseCode[i][j]->setText(" ");
                rowLayout[i]->addWidget(courseCode[i][j], 0, 0);
            } else if(i==0) {
                courseCode[i][j]->setText(TimeofDay[j]);
                rowLayout[i]->addWidget(courseCode[i][j], 0, j);
            } else if(j==0) {
                courseCode[i][j]->setText(daysOfWeek[i]);
                rowLayout[i]->addWidget(courseCode[i][j], 1, 0);
            } else {
                courseCode[i][j] -> setText("+");
                assignmentsDue[i][j] = new QPushButton("assignmentsDue",this);
                assignmentsDue[i][j]->setText("Due: . . .");
                assignmentsDue[i][j]->hide();


                progressBar[i][j] = new QProgressBar(this);
                progressBar[i][j]->setRange(0, 100);
                progressBar[i][j]->setValue(10);
                progressBar[i][j]->setStyleSheet("QProgressBar {"
                                                 "min-height: 6px;"
                                                 "max-height: 7px;"
                                                 "color: transparent;"
                                                 "background-color: #a3a7ad"
                                                 "}");
                progressBar[i][j]->setMaximumWidth(pageWidth/8);
                progressBar[i][j]->hide();

                extendRight[i][j] = new QPushButton(this);
                extendRight[i][j]->setText(">");
                // extendRight[i][j]->hide();

                rowLayout[i]->addWidget(courseCode[i][j], 0, j);
                rowLayout[i]->addWidget(assignmentsDue[i][j], 1, j);
                rowLayout[i]->addWidget(progressBar[i][j], 2, j);
                rowLayout[i]->addWidget(extendRight[i][j], 3, j);
                QObject::connect(courseCode[i][j], &QPushButton::clicked, [this,i,j]() {
                    this->on_plus_clicked(i,j);
                });

                QObject::connect(extendRight[i][j], &QPushButton::clicked, [this,i,j]() {
                    this->extend(i,j);
                });
            }


        }

        layout->addLayout(rowLayout[i], i, 0);
    }

    checkExistingTableData();

    page1->setLayout(layout);


}

int p,q;

void MainWindow::on_plus_clicked(int a, int b)
{
    p=a;
    q=b;

    if(courseCode[a][b]->text()=="+") {
        ui->stackedWidget->setCurrentIndex(3);
    } else {
        courseCodeClicked();
    }

}



QString code;

void MainWindow::onComboBoxValueChanged(int index) {


    int k=0;
    QFile CSVFile("ku_ce.csv");
    if(CSVFile.open(QIODevice::ReadOnly)) {
        QTextStream Stream(&CSVFile);
        while (Stream.atEnd()==false) {
            QString lineData = Stream.readLine();
            QStringList Data = lineData.split(",");
            if(k==index) {
                courseName->setText(Data.at(0));
                courseCredits->setText(Data.at(3));
                code = Data.at(2);

            }
            k++;
        }
    }



    QNetworkAccessManager networkManager;
    QUrl APIUrl("https://syllabus-provider-server.vercel.app/" + code);

    QNetworkRequest request(APIUrl);
    QNetworkReply *reply = networkManager.get(request);


    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();



    if(reply->error() == QNetworkReply::NoError) {
        QString Response = reply->readAll();
        QByteArray jsonData = Response.toUtf8();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData);
        QJsonObject jsonObj = jsonDoc.object();
        QJsonArray jsonArray = jsonObj["topics"].toArray();

        syllabus->clear();
        QStringList data;
        for (const QJsonValue &value : jsonArray) {
            if (value.isString()) {
                syllabus->addItem(value.toString());
            }
        }
        qDebug() <<data;
    } else {
        qDebug() << "er: " << reply->errorString();
    }
}


void MainWindow::okClicked() {

    courseCode[p][q]->setText(code);
    assignmentsDue[p][q]->setText("Due: . . . ");
    assignmentsDue[p][q]->show();
    progressBar[p][q]->show();

    ui->stackedWidget->setCurrentIndex(0);
    storeTableData();

}

void MainWindow::checkExistingTableData()
{
    int m,n;
    QFile routineFile(routinePath);
    if (!routineFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading:" << routinePath;
    } else {

        QTextStream in(&routineFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList lineArray = line.split(" ");
            m=lineArray[0].toInt();
            n=lineArray[1].toInt();
            QString sbjCode = lineArray[2] + " " + lineArray[3];
            courseCode[m][n]->setText(sbjCode);
            assignmentsDue[m][n]->show();
            progressBar[m][n]->show();
        }
    }

    routineFile.close();

}

void MainWindow::storeTableData()
{
    int k=1;
    QFile routineFile(routinePath);
    QStringList lines;
    if (routineFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&routineFile);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList datalist = line.split(" ");
            if(datalist[0].toInt()==p && datalist[1].toInt()==q) {
                QString joined = QString::number(p) + " " + QString::number(q) + " " + code;
                lines.append(joined);
                k=0;

            } else {
                lines.append(line);
            }

        }
        routineFile.close();
        if (routineFile.open(QIODevice::WriteOnly)) {
            QTextStream out(&routineFile);
            for (const QString &line : lines) {
                out << line << "\n";
            }
            // out << "This is a to-do list.\n";
            routineFile.close();
            qDebug() << "File written to:" << path;
        }

    }
    if(k) {
        if (routineFile.open(QIODevice::Append | QIODevice::Text)) {
            QTextStream out(&routineFile);
            out << p <<" " << q <<" " << code <<"\n";
            // out << "This is a to-do list.\n";
            routineFile.close();
            qDebug() << "File written to:" << path;
        }
    }

}

void MainWindow::courseCodeClicked()
{
    QStackedWidget *stackedWidget = ui->stackedWidget;
    QWidget *page5 = stackedWidget->widget(4);


    QGridLayout *layout2 = new QGridLayout(this);

    QLabel *courseCode0 = new QLabel(this);
    courseCode0->setText(courseCode[p][q]->text());

    QLabel *assignment0 = new QLabel(this);
    assignment0->setText("Assignment");

    QLabel *syllabus0 = new QLabel(this);
    syllabus0->setText("syll");

    layout2->addWidget(courseCode0, 0, 1);
    layout2->addWidget(assignment0, 1, 1);
    layout2->addWidget(syllabus0, 2, 1);

    QPushButton *ok = new QPushButton(this);
    ok->setText("ok");

    QPushButton *deleteBtn = new QPushButton(this);
    deleteBtn->setText("delete");

    layout2->addWidget(ok,3,1);
    layout2->addWidget(deleteBtn,3,2);

    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteCourse);

    page5->setLayout(layout2);

    ui->stackedWidget->setCurrentIndex(4);



}

void MainWindow::deleteCourse()
{
    QFile routineFile(routinePath);
    QStringList lines;
    if (routineFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&routineFile);

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList datalist = line.split(" ");
            if(datalist[0].toInt()!=p || datalist[1].toInt()!=q) {
                lines.append(line);
            }
        }
        routineFile.close();

        if (routineFile.open(QIODevice::WriteOnly)) {
            QTextStream out(&routineFile);
            for (const QString &line : lines) {
                out << line << "\n";
            }
            routineFile.close();
        }

    }

    courseCode[p][q]->setText("+");
    assignmentsDue[p][q]->hide();
    progressBar[p][q]->hide();

    ui->stackedWidget->setCurrentIndex(0);


}

void MainWindow::extend(int a, int b)
{
    qDebug()<<a<<b;

    rowLayout[a]->removeWidget(courseCode[a][b]);
    rowLayout[a]->removeWidget(assignmentsDue[a][b]);
    rowLayout[a]->removeWidget(progressBar[a][b]);
    rowLayout[a]->removeWidget(extendRight[a][b]);

    rowLayout[a]->removeWidget(courseCode[a][b+1]);
    rowLayout[a]->removeWidget(assignmentsDue[a][b+1]);
    rowLayout[a]->removeWidget(progressBar[a][b+1]);
    rowLayout[a]->removeWidget(extendRight[a][b+1]);

    courseCode[a][b+1]->hide();
    assignmentsDue[a][b+1]->hide();
    progressBar[a][b+1]->hide();
    extendRight[a][b+1]->hide();


    rowLayout[a]->addWidget(courseCode[a][b],0,b, 1, 2);
    rowLayout[a]->addWidget(assignmentsDue[a][b],1,b, 1, 2);
    rowLayout[a]->addWidget(progressBar[a][b],2,b, 1, 2);
    progressBar[a][b]->setMaximumWidth(pageWidth/8+pageWidth/8);
    rowLayout[a]->addWidget(extendRight[a][b],3,b, 1, 2);

}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    QStackedWidget *stackedWidget = ui->stackedWidget;
    QWidget *page1 = stackedWidget->widget(0);
    pageWidth = page1->width();

    for(int i=1; i<=7; i++) {
        for(int j=1; j<=7; j++) {
            progressBar[i][j]->setMaximumWidth(pageWidth/8);
        }
    }

}


void MainWindow::selectionForm() {

    QGridLayout *layout1 = new QGridLayout(this);

    QLabel *label1 = new QLabel(this);
    label1->setText("Course Code: ");
    QLabel *label2 = new QLabel(this);
    label2->setText("Course Name: ");
    QLabel *label3 = new QLabel(this);
    label3->setText("Credits: ");
    QLabel *label4 = new QLabel(this);
    label4->setText("Syllabus: ");
    // QLabel *label5= new QLabel(this);
    // label5->setText("Syllabus: ");


    courseName = new QLineEdit(this);
    courseName->setReadOnly(true);
    courseCredits = new QLineEdit(this);
    courseCredits->setReadOnly(true);

    QComboBox *comboBox = new QComboBox();

    QFile CSVFile("ku_ce.csv");
    if(CSVFile.open(QIODevice::ReadOnly)) {
        QTextStream Stream(&CSVFile);
        while (Stream.atEnd()==false) {
            QString lineData = Stream.readLine();
            QStringList Data = lineData.split(",");
            comboBox->addItem(Data.at(2));
        }
    }

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onComboBoxValueChanged(int)));
    comboBox->setCurrentIndex(-1);


    layout1->addWidget(label1, 0, 0);
    layout1->addWidget(comboBox, 0, 1);
    layout1->addWidget(label2,1,0);
    layout1->addWidget(courseName,1,1);
    layout1->addWidget(label3,2,0);
    layout1->addWidget(courseCredits,2,1);
    layout1->addWidget(label4,3,0);

    syllabus = new QListWidget(this);
    layout1->addWidget(syllabus,5,0);

    QPushButton *ok = new QPushButton();
    ok->setText("OK");
    layout1->addWidget(ok, 6,1);
    connect(ok, &QPushButton::clicked, this, &MainWindow::okClicked);

    QStackedWidget *stackedWidget = ui->stackedWidget;
    QWidget *page4 = stackedWidget->widget(3);
    page4->setLayout(layout1);


}


/*

void MainWindow::on_AddTaskBut_clicked()
{
    //Lising the item in the listwidget
    QListWidgetItem* item = new QListWidgetItem(ui->tasktextbox->text(),ui->listWidget);
    ui->listWidget->addItem(item);

    //to be editable (stackoflol)
    //item->setFlags(item->flags() | Qt::ItemIsEditable);
    //clearing textbox after adding

    ui->tasktextbox->clear();

    //focusing on textbox after adding

    ui->tasktextbox->setFocus();
}


void MainWindow::on_DeleteTaskBut_clicked()
{
    //taking the item from current row and passing it
    //ot the actual "item" element in 'QListWidgetItem* item'
    QListWidgetItem* item = ui->listWidget->takeItem(ui->listWidget->currentRow());
    delete item;
}


void MainWindow::on_DeleteAllTasksBut_clicked()
{
    //self explanatory
    ui->listWidget->clear();
}
*/
