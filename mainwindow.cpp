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
#include <QSet>
#include <QVector>


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
#include <QListWidget>
#include <QListWidgetItem>
#include <QSpacerItem>
#include <QCheckBox>
#include <QScrollArea>

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
    if(!file.open(QIODevice::WriteOnly)){
        QMessageBox::information(0,"Error",file.errorString());
    }

    //file from QFile file., accessing textstream
    QTextStream fileout(&file);

    //reading item from the file same syntax as in reading from textbox
    //everything similar upto here
    for(int i=0; i<ui->listWidget->count(); ++i){
        //similar to cout
        fileout<<ui->listWidget->item(i)->text()<<"\t" << (ui->listWidget->item(i)->checkState() == Qt::Checked ? "1" : "0") << "\n";
    }

    file.close();

    delete ui;

}

int pageWidth;

QString code;
QStringList syllabusTopics;

QSet<QString> syllabusCodesSet;


//buttons to switch  betn pages in stacked widgets.

void MainWindow::on_RoutineBut_clicked()
{
    checkExistingTableData();
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_ToDoBut_clicked()
{
    // delete toDoList;
    // toDoList = new ToDoList(ui->listWidget,
    //                         ui->tasktextbox,
    //                         ui->AddTaskBut,
    //                         ui->DeleteTaskBut,
    //                         ui->DeleteAllTasksBut,
    //                         this);
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_SyllabusBut_clicked()
{
    syllabusPageClicked(syllabusCodesSet);
}

int rowSpan[8][8];

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
            rowSpan[i][j] = 1;

            if(i==0 && j==0){
                courseCode[i][j]->setText(" ");
                rowLayout[i]->addWidget(courseCode[i][j], 0, 0);
            } else if(i==0) {
                courseCode[i][j]->setText(TimeofDay[j]);
                rowLayout[i]->addWidget(courseCode[i][j], 0, j);
            } else if(j==0) {
                courseCode[i][j]->setText(daysOfWeek[i]);
                rowLayout[i]->addWidget(courseCode[i][j], 0, 0);
            } else {
                courseCode[i][j] -> setText("+");

                progressBar[i][j] = new QProgressBar(this);
                progressBar[i][j]->setRange(0, 100);
                // progressBar[i][j]->setValue(10);
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
                extendRight[i][j]->hide();
                extendRight[i][j]->setStyleSheet("QPushButton {"
                                                 "margin-right: 10px;"  // Margin around the button
                                                 "text-align: right;"                                                 // Padding inside the button
                                                 "}");
                // extendRight[i][j]->setStyleSheet("padding-right: 2px");

                rowLayout[i]->addWidget(courseCode[i][j], 0, j);
                rowLayout[i]->addWidget(progressBar[i][j], 1, j);
                rowLayout[i]->addWidget(extendRight[i][j], 2, j);
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
int render1 = 0;

void MainWindow::on_plus_clicked(int a, int b)
{
    p=a;
    q=b;


    if(courseCode[a][b]->text()=="+") {
        ui->stackedWidget->setCurrentIndex(3);
    } else {

        // if (render1) {
        //     QWidget* page = ui->stackedWidget->widget(4);
        //     ui->stackedWidget->removeWidget(page);
        //     // delete page;
        // }


        courseCodeClicked(a,b);

    }

}




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

    syllabusTopics.clear();



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
                syllabusTopics.append(value.toString());
            }
        }
        qDebug() <<data;
    } else {
        qDebug() << "er: " << reply->errorString();
    }
}


void MainWindow::okClicked() {

    courseCode[p][q]->setText(code);
    progressBar[p][q]->show();
    extendRight[p][q]->show();

    ui->stackedWidget->setCurrentIndex(0);


    QString syllabusPath = QCoreApplication::applicationDirPath() + "/" + code + ".txt";
    QFile syllabusFile(syllabusPath);

    if(!syllabusCodesSet.contains(code)) {
        if (syllabusFile.open(QIODevice::WriteOnly)) {

            QTextStream out(&syllabusFile);
            for (const QString &line : syllabusTopics) {
                out << 0 << " " << line << "\n";
            }

            syllabusFile.close();
            qDebug() << "File written to:" << syllabusPath;
        }
    }

    syllabusCodesSet.insert(code);

    storeTableData();

}

void MainWindow::cancelClicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_ok_clicked()
{
    checkExistingTableData();
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::onItemChanged()
{

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
            QString sbjCode = lineArray[3] + " " + lineArray[4];

            syllabusCodesSet.insert(sbjCode);



            courseCode[m][n]->setText(sbjCode);
            progressBar[m][n]->show();
            extendRight[m][n]->show();
            rowSpan[m][n] = lineArray[2].toInt();

            QString checkBoxPath = QCoreApplication::applicationDirPath() + "/" + sbjCode + ".txt";
            QFile checkBoxFile(checkBoxPath);

            QVector<int> intArray;
            int countt=0;

            if (checkBoxFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

                QTextStream in(&checkBoxFile);

                while (!in.atEnd()) {

                    QString line = in.readLine();

                    QString val = line.at(0);
                    intArray.append(val.toInt());
                    if(val.toInt()) {
                        ++countt;
                    }
                    qDebug()<<val<<"asasdsds";
                }

                checkBoxFile.close();
                qDebug()<<countt<<"pp";

            }
            int calc = (countt*100)/intArray.size();
            progressBar[m][n]->setValue(calc);
            qDebug()<<calc<<"ss";

            if(rowSpan[m][n] != 1) {

                for(int j=2; j<=rowSpan[m][n]; j++) {
                    rowLayout[m]->removeWidget(courseCode[m][n+j-1]);
                    rowLayout[m]->removeWidget(progressBar[m][n+j-1]);
                    rowLayout[m]->removeWidget(extendRight[m][n+j-1]);

                    courseCode[m][n+j-1]->hide();
                    progressBar[m][n+j-1]->hide();
                    extendRight[m][n+j-1]->hide();
                }
            }
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
                QString joined = QString::number(p) + " " + QString::number(q) + " " + QString::number(rowSpan[p][q]) + " " + code;
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
            out << p <<" " << q <<" " << rowSpan[p][q] << " " << code <<"\n";
            // out << "This is a to-do list.\n";
            routineFile.close();
            qDebug() << "File written to:" << path;
        }
    }

}

QGridLayout *layout2 = new QGridLayout;
QGridLayout *layout_2 = new QGridLayout;

void MainWindow::courseCodeClicked(int a, int b)
{
    QStackedWidget *stackedWidget = ui->stackedWidget;
    QWidget *page5 = stackedWidget->widget(4);



    // QGridLayout *layout2 = new QGridLayout(this);

    QString cCode = courseCode[a][b]->text();
    QLabel *courseCode0 = new QLabel(this);
    courseCode0->setText(courseCode[a][b]->text());

    // QLabel *assignment0 = new QLabel(this);
    // assignment0->setText("Assignment");

    // QFile file(path);
    // QListWidget *listWidget = new QListWidget();
    // if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
    //     QMessageBox::information(nullptr, "Error", file.errorString());
    // } else {
    //     QTextStream filein(&file);
    //     while (!filein.atEnd()) {
    //         QString line = filein.readLine();
    //         QStringList parts = line.split("\t"); // Assume that each line is in the format: "text\tcheckState"
    //         if (parts.size() == 2) {
    //             QListWidgetItem* item = new QListWidgetItem(parts[0], listWidget);
    //             item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    //             item->setCheckState(parts[1] == "1" ? Qt::Checked : Qt::Unchecked);
    //             listWidget->addItem(item);
    //         }
    //     }
    // }
    //     file.close();

    // // connect(listWidget, &QListWidget::itemChanged, this, &MainWindow::onItemChanged);

    // layout2->addWidget(listWidget,2,1);





    QLabel *syllabus0 = new QLabel(this);
    syllabus0->setText("Syllabus");

    layout2->addWidget(courseCode0, 0, 1);
    // layout2->addWidget(assignment0, 1, 1);
    layout2->addWidget(syllabus0, 1, 1);

    QPushButton *ok = new QPushButton(this);
    ok->setText("ok");
    connect(ok, &QPushButton::clicked, this, &MainWindow::on_ok_clicked);

    QPushButton *deleteBtn = new QPushButton(this);
    deleteBtn->setText("delete");

    layout2->addWidget(ok,3,1,2,1);
    layout2->addWidget(deleteBtn,3,2,2,1);

    connect(deleteBtn, &QPushButton::clicked, this, &MainWindow::deleteCourse);

    page5->setLayout(layout2);



    int row=0;

        QString topicsPath = QCoreApplication::applicationDirPath() + "/" +  cCode + ".txt";
        QFile topicsFile(topicsPath);

        if (topicsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

            QTextStream in(&topicsFile);

            while (!in.atEnd()) {
                QString line = in.readLine();
                QString numVal = line.at(0);

                line.remove(0,2);

                QCheckBox *checkBox = new QCheckBox(this);
                if(numVal.toInt()) {
                    checkBox->setChecked(true);
                }
                QObject::connect(checkBox, &QCheckBox::stateChanged, [=](int state) {
                    if(state == Qt::Checked) {
                        checkBoxChanged(1, cCode, row);
                    } else {
                        checkBoxChanged(0,cCode, row);
                    }

                });
                ++row;
                layout_2->addWidget(checkBox,row,0);


                QLabel *topicsLabel = new QLabel(this);
                topicsLabel->setText(line);
                layout_2->addWidget(topicsLabel,row,1);


            }

        }
        topicsFile.close();

        layout2->addLayout(layout_2,2,1,2,1);

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

    for(int j=1;j<=rowSpan[p][q];++j) {
        if(j==1) {

            rowLayout[p]->removeWidget(courseCode[p][q]);
            rowLayout[p]->removeWidget(progressBar[p][q]);
            rowLayout[p]->removeWidget(extendRight[p][q]);

            rowLayout[p]->addWidget(courseCode[p][q],0,q);
            rowLayout[p]->addWidget(progressBar[p][q],2,q);
            rowLayout[p]->addWidget(extendRight[p][q],3,q);

            courseCode[p][q]->setText("+");
            progressBar[p][q]->setMaximumWidth(pageWidth/8);
            progressBar[p][q]->hide();


        } else {

            rowLayout[p]->addWidget(courseCode[p][q+j-1], 0, q+j-1);
            rowLayout[p]->addWidget(progressBar[p][q+j-1], 2, q+j-1);
            rowLayout[p]->addWidget(extendRight[p][q+j-1], 3, q+j-1);

            courseCode[p][q+j-1]->show();
            progressBar[p][q+j-1]->hide();
            progressBar[p][q+j-1]->setMaximumWidth(pageWidth/8);
            extendRight[p][q+j-1]->show();
        }
    }

    rowSpan[p][q] = 1;

    ui->stackedWidget->setCurrentIndex(0);


}

void MainWindow::extend(int a, int b)
{

    ++rowSpan[a][b];
    int var = rowSpan[a][b];
    int barWidth=0;
    p=a;
    q=b;

    for(int k=1; k<=var; k++) {
        barWidth += pageWidth/8;
    }

    rowLayout[a]->removeWidget(courseCode[a][b]);
    rowLayout[a]->removeWidget(progressBar[a][b]);
    rowLayout[a]->removeWidget(extendRight[a][b]);

    rowLayout[a]->removeWidget(courseCode[a][b+var-1]);
    rowLayout[a]->removeWidget(progressBar[a][b+var-1]);
    rowLayout[a]->removeWidget(extendRight[a][b+var-1]);

    courseCode[a][b+var-1]->hide();
    progressBar[a][b+var-1]->hide();
    extendRight[a][b+var-1]->hide();


    rowLayout[a]->addWidget(courseCode[a][b],0,b, 1, var);
    rowLayout[a]->addWidget(progressBar[a][b],2,b, 1, var);
    progressBar[a][b]->setMaximumWidth(barWidth);
    rowLayout[a]->addWidget(extendRight[a][b],3,b, 1, var);

    code = courseCode[a][b]->text();
    qDebug()<<a<<b << code;
    storeTableData();

}

void MainWindow::resizeEvent(QResizeEvent *event) {
    QMainWindow::resizeEvent(event);

    QStackedWidget *stackedWidget = ui->stackedWidget;
    QWidget *page1 = stackedWidget->widget(0);
    pageWidth = page1->width();
    int barWidth=0;

    for(int i=1; i<=7; i++) {
        for(int j=1; j<=7; j++) {

            for(int k=1; k<=rowSpan[i][j]; k++) {
                barWidth += pageWidth/8;
            }

            progressBar[i][j]->setMaximumWidth(barWidth);
            barWidth = 0;
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
    layout1->addWidget(ok, 6,2,1,2);
    connect(ok, &QPushButton::clicked, this, &MainWindow::okClicked);

    QPushButton *cancel = new QPushButton();
    cancel->setText("cancel");
    layout1->addWidget(cancel, 6,1);
    connect(cancel, &QPushButton::clicked, this, &MainWindow::cancelClicked);

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



// syllabus page



QGridLayout *layout_3 = new QGridLayout;
int initialRender = 0;

void MainWindow::syllabusPageClicked(QSet<QString> syllabusCodesSetParam)
{

    QStackedWidget *stackedWidget = ui->stackedWidget;
    QWidget *syllabusPage = stackedWidget->widget(2);

    QWidget *layout_2Container = new QWidget;
    QGridLayout *layout_2 = new QGridLayout(layout_2Container);

    QLabel *syllLabel = new QLabel(this);
    syllLabel->setText("Syllabus : ");
    layout_2->addWidget(syllLabel);



    int o=1;
    int row=0;

    for(const QString &syllCodes: syllabusCodesSetParam) {

        QString topicsPath = QCoreApplication::applicationDirPath() + "/" + syllCodes + ".txt";
        QFile topicsFile(topicsPath);

        QLabel *sbjLabel = new QLabel(this);
        sbjLabel->setText(syllCodes);
        layout_2->addWidget(sbjLabel,o,0);
        ++o;

        if (topicsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

            QTextStream in(&topicsFile);

            while (!in.atEnd()) {
                QString line = in.readLine();
                QString numVal = line.at(0);

                line.remove(0,2);

                QCheckBox *checkBox = new QCheckBox(this);
                if(numVal.toInt()) {
                    checkBox->setChecked(true);
                }
                QObject::connect(checkBox, &QCheckBox::stateChanged, [=](int state) {
                    if(state == Qt::Checked) {
                        checkBoxChanged(1, syllCodes, row);
                    } else {
                        checkBoxChanged(0, syllCodes, row);
                    }
                    qDebug()<<syllCodes;
                });
                ++row;
                layout_2->addWidget(checkBox,o,0);


                QLabel *topicsLabel = new QLabel(this);
                topicsLabel->setText(line);
                layout_2->addWidget(topicsLabel,o,1);
                ++o;

            }

        }
        row=0;
        topicsFile.close();
    }

    QScrollArea *scrollableArea = new QScrollArea();
    scrollableArea->setWidget(layout_2Container);
    scrollableArea->setWidgetResizable(true);

    if(initialRender) {
        QLayoutItem *item;
        item = layout_3->takeAt(0);
        QWidget *widget = item->widget();
        widget->hide();
    }

    layout_3->addWidget(scrollableArea);
    syllabusPage->setLayout(layout_3);

    ++initialRender;

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::checkBoxChanged(int value, QString syllCode, int row)
{
    QString checkBoxPath = QCoreApplication::applicationDirPath() + "/" + syllCode + ".txt";
    QFile checkBoxFile(checkBoxPath);
    int r=0;

    qDebug() << syllCode <<" " <<row;

    QStringList linesList;
    if (checkBoxFile.open(QIODevice::ReadOnly | QIODevice::Text)) {

        QTextStream in(&checkBoxFile);

        while (!in.atEnd()) {

            QString line = in.readLine();

            if(r==row) {
                QString v = QString::number(value);
                line.replace(0,1,v);
            }

            linesList.append(line);

            ++r;
        }

        checkBoxFile.close();

    }


    if (checkBoxFile.open(QIODevice::WriteOnly)) {

        QTextStream out(&checkBoxFile);
        for (const QString &line : linesList) {
            out << line << "\n";
        }
        checkBoxFile.close();
    }


}
