/********************************************************************************
** Form generated from reading UI file 'selection_page.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTION_PAGE_H
#define UI_SELECTION_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_selection_page
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *selection_page)
    {
        if (selection_page->objectName().isEmpty())
            selection_page->setObjectName("selection_page");
        selection_page->resize(400, 300);
        buttonBox = new QDialogButtonBox(selection_page);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(selection_page);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, selection_page, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, selection_page, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(selection_page);
    } // setupUi

    void retranslateUi(QDialog *selection_page)
    {
        selection_page->setWindowTitle(QCoreApplication::translate("selection_page", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class selection_page: public Ui_selection_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTION_PAGE_H
