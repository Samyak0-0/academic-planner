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
    , //task"T"ext"B"ox kind of a label(used eg line82) here and tasktextbox actual object in todopage
    addButton(AddTaskBut)
    , deleteButton(DeleteTaskBut)
    , deleteAllButton(DeleteAllTaskBut)

{
    // Connect buttons to their slots
    connect(addButton, &QPushButton::clicked, this, &ToDoList::on_AddTaskBut_clicked);
    connect(deleteButton, &QPushButton::clicked, this, &ToDoList::on_DeleteTaskBut_clicked);
    connect(deleteAllButton, &QPushButton::clicked, this, &ToDoList::on_DeleteAllTasksBut_clicked);

    //implementattion for checkbobxes
    listWidget->clear();
    connect(listWidget, &QListWidget::itemChanged, this, &ToDoList::on_ItemChanged);

    // Load to-do list data thtrough constructor
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QMessageBox::information(nullptr, "Error", file.errorString());
    } else {
        QTextStream filein(&file);
        while (!filein.atEnd()) {
            QString line = filein.readLine();
            QStringList parts = line.split(
                "\t"); // Assume that each line is in the format: "text\tcheckState"
            if (parts.size() == 2) {
                QListWidgetItem *item = new QListWidgetItem(parts[0], listWidget);
                item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
                item->setCheckState(parts[1] == "1" ? Qt::Checked : Qt::Unchecked);
                listWidget->addItem(item);
            }
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
//self explantory but comments are in mainwindow.cpp

void ToDoList::on_AddTaskBut_clicked()
{
    QListWidgetItem *item = new QListWidgetItem(taskTextBox->text(), listWidget);
    //for checkbox

    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
    item->setCheckState(Qt::Unchecked); //unchecked intially

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
/*
void ToDoList::on_ItemChanged(QListWidgetItem *item) {

    //QFont font = item->font();//font object
    //item->text();

    QFont font = item->font();
    font.setStrikeOut(item->checkState() == Qt::Checked);


    if (item->checkState() == Qt::Checked){
        //item->setTextAlignment(Qt::AlignBottom);

        font.setStrikeOut(true);
        item->setFont(QFont("Times", 12, QFont::Bold ));
        item->setBackground(Qt::lightGray);
        //item->setFont(font); Crashes the entire program??? Segmentaitoon fault.
        //item->setText(item->text().setStrikeThrough(ture));
    } else {
        font.setStrikeOut(false);
        item->setFont(QFont("Times", 12, QFont::Normal));
        item->setBackground(Qt::white);
    }
    //item->setFont(font);
}
*/
//strikethrough works here but not in above code

void ToDoList::on_ItemChanged(QListWidgetItem *item)
{
    QFont font = item->font(); //font obj declaration

    if (item->checkState() == Qt::Checked) {
        font.setStrikeOut(true);
        item->setBackground(Qt::lightGray); //ticked
    } else {
        font.setStrikeOut(false);
        item->setBackground(Qt::white); //uncheked
    }
    rearrangeItems();
    item->setFont(font);
}

void ToDoList::rearrangeItems()
{
    QList<QListWidgetItem *> checkedItems;
    QList<QListWidgetItem *> uncheckedItems;

    for (int i = listWidget->count() - 1; i >= 0; --i) {
        QListWidgetItem *item = listWidget->takeItem(i);
        if (item->checkState() == Qt::Checked) {
            checkedItems.prepend(
                item); //prepend adds the item always to first, so descending i means order is preserved
        } else {
            uncheckedItems.prepend(item);
        }
    }

    for (QListWidgetItem *item : uncheckedItems) {
        listWidget->addItem(item);
    }

    for (QListWidgetItem *item : checkedItems) {
        listWidget->addItem(item);
    }
}
