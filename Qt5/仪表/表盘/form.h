#ifndef FORM_H
#define FORM_H

#include <QtGui>
#include <QObject>
#include "Dial.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT
    

    Dial *dial1;
    Dial *dial2;


public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    
private slots:
    void on_lineEditBackColor_editingFinished();

    void on_lineEdit_15_editingFinished();

    void on_lineEdit_11_editingFinished();

    void on_lineEdit_18_editingFinished();

    void on_lineEdit_17_editingFinished();

    void on_lineEdit_12_editingFinished();

    void on_lineEdit_21_editingFinished();

    void on_lineEdit_8_editingFinished();

    void on_lineEdit_16_editingFinished();

    void on_lineEditMaxValue_editingFinished();

    void on_lineEditMinValue_editingFinished();

    void on_lineEditCurValue_editingFinished();

    void on_lineEdit_14_editingFinished();

    void on_lineEdit_13_editingFinished();


private:
    Ui::Form *ui;
};

#endif // FORM_H
