#include "todolist.h"
#include <QListWidgetItem>
#include <QStandardPaths>

ToDoList::ToDoList(QListWidget *listWidget,
                   QLineEdit *tasktextbox,
                   QPushButton *AddTaskBut,
                   QPushButton *DeleteTaskBut,
                   QPushButton *DeleteAllTaskBut,
                   QObject *parent)
    : QObject(parent)
    , listWidget(listWidget)
    , taskTextBox(tasktextbox)
    , addButton(AddTaskBut)
    , deleteButton(DeleteTaskBut)
    , deleteAllButton(DeleteAllTaskBut)
//path(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation) + "/todofile.txt")

{
    // Connect buttons to their slots
    connect(addButton, &QPushButton::clicked, this, &ToDoList::on_AddTaskBut_clicked);
    connect(deleteButton, &QPushButton::clicked, this, &ToDoList::on_DeleteTaskBut_clicked);
    connect(deleteAllButton, &QPushButton::clicked, this, &ToDoList::on_DeleteAllTasksBut_clicked);

    // Load to-do list data
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::information(nullptr, "Error", file.errorString());
    } else {
        QTextStream filein(&file);
        while (!filein.atEnd()) {
            QListWidgetItem *item = new QListWidgetItem(filein.readLine(), listWidget);
            listWidget->addItem(item);
        }
        file.close();
    }
}

ToDoList::~ToDoList()
{
    /*
    QFile file(path);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::information(nullptr, "Error", file.errorString());
        return;
    }

    QTextStream fileout(&file);
    for (int i = 0; i < listWidget->count(); ++i) {
        fileout << listWidget->item(i)->text() << "\n";
    }

    file.close();
    */
    //cant put the destructor here for some reason
    /*
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
    for(int i=0; i<listWidget->count(); ++i){
        //similar to cout
        QListWidgetItem* item = new QListWidgetItem(fileout.readLine(), listWidget);
        fileout<<listWidget->item(i)->text()<<"\n";
    }

    file.close();
    */
}

//todolist function buttons.

void ToDoList::on_AddTaskBut_clicked()
{
    QListWidgetItem *item = new QListWidgetItem(taskTextBox->text(), listWidget);
    listWidget->addItem(item);
    taskTextBox->clear();
    taskTextBox->setFocus();
}

void ToDoList::on_DeleteTaskBut_clicked()
{
    QListWidgetItem *item = listWidget->takeItem(listWidget->currentRow());
    delete item;
}

void ToDoList::on_DeleteAllTasksBut_clicked()
{
    listWidget->clear();
}
