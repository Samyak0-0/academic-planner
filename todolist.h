#ifndef TODOLIST_H
#define TODOLIST_H

#include <QObject>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include<QStandardPaths>
#include <QCheckBox>

class ToDoList:public QObject
{
    Q_OBJECT
public:

    explicit ToDoList(QListWidget *listWidget, QLineEdit *tasktextbox, QPushButton *AddTaskBut, QPushButton *DeleteTaskBut, QPushButton *DeleteAllTaskBut, QObject *parent = nullptr);
    ~ToDoList();

private slots:

    void on_AddTaskBut_clicked();
    void on_DeleteTaskBut_clicked();
    void on_DeleteAllTasksBut_clicked();
    void on_ItemChanged(QListWidgetItem *item);

private:
    void rearrangeItems();

    QListWidget *listWidget;
    QLineEdit *taskTextBox;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *deleteAllButton;
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"\\todofile.txt";;
};

#endif // TODOLIST_H
