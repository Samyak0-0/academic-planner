#include "selection_page.h"
#include "ui_selection_page.h"
#include <QLineEdit>
#include <QLabel>
#include <QGridLayout>
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

selection_page::selection_page(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::selection_page)
{
    ui->setupUi(this);
    selectionForm();
}

selection_page::~selection_page()
{
    delete ui;
}

void selection_page::onComboBoxValueChanged(int index) {

    QString code;
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

        QStringList data;
        for (const QJsonValue &value : jsonArray) {
            if (value.isString()) {
                data.append(value.toString());
            }
        }
        qDebug() <<data;
    } else {
        qDebug() << "er: " << reply->errorString();
    }
}

void selection_page::selectionForm() {

    QGridLayout *layout = new QGridLayout(this);

    QLabel *label1 = new QLabel(this);
    label1->setText("Course Code: ");
    QLabel *label2 = new QLabel(this);
    label2->setText("Course Name: ");
    QLabel *label3 = new QLabel(this);
    label3->setText("Credits: ");
    QLabel *label4 = new QLabel(this);
    label4->setText("Syllabus: ");
    QLabel *label5= new QLabel(this);
    label5->setText("Syllabus: ");


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


    layout->addWidget(label1, 0, 0);
    layout->addWidget(comboBox, 0, 1);
    layout->addWidget(label2,1,0);
    layout->addWidget(courseName,1,1);
    layout->addWidget(label3,2,0);
    layout->addWidget(courseCredits,2,1);
    layout->addWidget(label4,3,0);
    layout->addWidget(label5,4,0);


}
