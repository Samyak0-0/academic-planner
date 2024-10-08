#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGridLayout>
#include <QLabel>
#include <QListWidget>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QSet>
#include <QStackedWidget>
#include <QStandardPaths>
#include <QtCore>
#include "todolist.h"


QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void on_plus_clicked(int a, int b);

    void syllabusPageClicked(QSet<QString> syllabusCodesSetParam);

    void checkBoxChanged(int value, QString syllCode, int row);



private slots:
    void on_RoutineBut_clicked();

    void on_SyllabusBut_clicked();

    void on_ToDoBut_clicked();

    void onComboBoxValueChanged(int index);

    void okClicked();

    void cancelClicked();

    void on_ok_clicked();

    void onItemChanged();

    void checkExistingTableData();

    void storeTableData();

    void courseCodeClicked(int a, int b);

    void deleteCourse();

    void extend(int a, int b);

    /*
    void on_AddTaskBut_clicked();
    void on_DeleteTaskBut_clicked();
    void on_DeleteAllTasksBut_clicked();
    */

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::MainWindow *ui;
    ToDoList *toDoList;
    void TableWidgetDisplay();
    QPushButton *courseCode[8][8];
    QProgressBar *progressBar[8][8];
    QPushButton *extendRight[8][8];

    QString path = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                   + "\\todofile.txt";
    QString routinePath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)
                          + "\\routinePath.txt";

    void selectionForm();
    QLineEdit *courseName;
    QLineEdit *courseCredits;
    QListWidget *syllabus;

    QGridLayout *rowLayout[8];

    // QCheckBox *checkBox[50];
};

#endif // MAINWINDOW_H
