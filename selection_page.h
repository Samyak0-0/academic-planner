#ifndef SELECTION_PAGE_H
#define SELECTION_PAGE_H

#include <QDialog>
#include <QLineEdit>
#include <QtCore>

namespace Ui {
class selection_page;
}

class selection_page : public QDialog
{
    Q_OBJECT

public:
    explicit selection_page(QWidget *parent = nullptr);
    ~selection_page();

private slots:
    void onComboBoxValueChanged(int index);

private:
    Ui::selection_page *ui;
    void selectionForm();
    QLineEdit *courseName;
    QLineEdit *courseCredits;
};

#endif // SELECTION_PAGE_H
