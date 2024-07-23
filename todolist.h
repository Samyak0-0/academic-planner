#ifndef TODOLIST_H
#define TODOLIST_H

#include <QFile>
#include <QLineEdit>
#include <QListWidget>
#include <QMessageBox>
#include <QObject>
#include <QPushButton>
#include <QStandardPaths>
#include <QTextStream>

class ToDoList : public QObject
{
    Q_OBJECT
public:
    explicit ToDoList(QListWidget *listWidget,
                      QLineEdit *tasktextbox,
                      QPushButton *AddTaskBut,
                      QPushButton *DeleteTaskBut,
                      QPushButton *DeleteAllTaskBut,
                      QObject *parent = nullptr);
    ~ToDoList();
    //ToDoList();

private slots:
    void on_AddTaskBut_clicked();
    void on_DeleteTaskBut_clicked();
    void on_DeleteAllTasksBut_clicked();

private:
    QListWidget *listWidget;
    QLineEdit *taskTextBox;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *deleteAllButton;
    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                   + "\\todofile.txt";
    ;
};

#endif // TODOLIST_H
