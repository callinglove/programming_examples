#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    QList<QLineEdit *> edits  = this->findChildren<QLineEdit *>();

    QRegExpValidator *colorValidator = new QRegExpValidator(QRegExp("[a-fA-F0-9]+$"), this );
    QDoubleValidator *valueValidator = new QDoubleValidator(this);
    foreach(QLineEdit *edit,edits)
    {
        if (edit->objectName().endsWith("Color"))
        {
            edit->setValidator(colorValidator);
        }
        if (edit->objectName().endsWith("Value"))
        {
            edit->setValidator(valueValidator);
        }
        edit->setMaxLength(6);
    }

    dial1 = new Dial(NULL,"电压表","%1V",":V");    
    dial1->setCurrentValue(60);
    dial1->setFlat(true);

    dial2 = new Dial(NULL,"电阻表","%1Ω",":R");
    dial2->setCurrentValue(60);

    dial1->setGradientColorMode(QList<QColor>()<<QColor(0,94,255)<<QColor(0,253,255)<<QColor(0,255,119)<<QColor(255,243,0)<<QColor(255,0,0));
    dial2->setGradientColorMode(QList<QColor>()<<QColor(0,94,255)<<QColor(0,253,255)<<QColor(0,255,119)<<QColor(255,243,0)<<QColor(255,0,0));


    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(dial1);
    layout->addWidget(dial2);
    ui->widget->setLayout(layout);
    ui->widget->setStyleSheet("background:rgb(40,40,40);");
}

Form::~Form()
{
    delete ui;
}

void Form::on_lineEditBackColor_editingFinished()
{
    uint data = ui->lineEditBackColor->text().toUInt(0,16);

    if(data<=0xFFFFFF)
    {
        QColor color(data);

        QString back("background:rgb(%1,%2,%3);");

        ui->widget->setStyleSheet(back.arg(color.red()).arg(color.green()).arg(color.blue()));
        ui->lineEditBackColor->setText(QString().sprintf("%06x",data));
    }
}

void Form::on_lineEdit_15_editingFinished()
{
    uint data = ui->lineEdit_15->text().toUInt(0,16);
   if(data<=0xFFFFFF)
   {
       qDebug()<<data;
       dial1->setobkColor(QColor(data));
       dial2->setobkColor(QColor(data));
       ui->lineEdit_15->setText(QString().sprintf("%06x",data));
   }
}

void Form::on_lineEdit_11_editingFinished()
{
    uint data = ui->lineEdit_11->text().toUInt(0,16);
   if(data<=0xFFFFFF)
   {
       qDebug()<<data;
       dial1->setbkColor(QColor(data));
       dial2->setbkColor(QColor(data));
       ui->lineEdit_11->setText(QString().sprintf("%06x",data));
   }
}

void Form::on_lineEdit_18_editingFinished()
{
    uint data = ui->lineEdit_18->text().toUInt(0,16);
   if(data<=0xFFFFFF)
   {
       qDebug()<<data;
       dial1->setcentercolor(QColor(data));
       dial2->setcentercolor(QColor(data));
       ui->lineEdit_18->setText(QString().sprintf("%06x",data));
   }
}

void Form::on_lineEdit_17_editingFinished()
{
    uint data = ui->lineEdit_17->text().toUInt(0,16);
   if(data<=0xFFFFFF)
   {
       qDebug()<<data;
       dial1->setPointerColor(QColor(data));
       dial2->setPointerColor(QColor(data));
       ui->lineEdit_17->setText(QString().sprintf("%06x",data));
   }
}

void Form::on_lineEdit_12_editingFinished()
{
    uint data = ui->lineEdit_12->text().toUInt(0,16);
   if(data<=0xFFFFFF)
   {
       qDebug()<<data;
       dial1->setLabelColor(QColor(data));
       dial2->setLabelColor(QColor(data));
       ui->lineEdit_12->setText(QString().sprintf("%06x",data));
   }
}

void Form::on_lineEdit_21_editingFinished()
{
    uint data = ui->lineEdit_21->text().toUInt(0,16);
   if(data<=0xFFFFFF)
   {
       dial1->setScaleColor(QColor(data));
       dial2->setScaleColor(QColor(data));
       ui->lineEdit_21->setText(QString().sprintf("%06x",data));
   }
}

void Form::on_lineEdit_8_editingFinished()
{
    uint data = ui->lineEdit_8->text().toUInt(0,16);
   if(data<=0xFFFFFF)
   {
       dial1->setslideScaleColor(QColor(data));
       dial2->setslideScaleColor(QColor(data));
       ui->lineEdit_8->setText(QString().sprintf("%06x",data));
   }

}

void Form::on_lineEdit_16_editingFinished()
{
    uint data = ui->lineEdit_16->text().toUInt(0,16);
   if(data<=0xFFFFFF)
   {
       dial1->setValueColor(QColor(data));
       dial2->setValueColor(QColor(data));
       ui->lineEdit_16->setText(QString().sprintf("%06x",data));
   }

}

void Form::on_lineEditMaxValue_editingFinished()
{
    QLineEdit *edit = qobject_cast<QLineEdit *>(sender());
    qreal data = edit->text().toFloat();

    if (dial1->setMaxValue(data))
    {
        dial2->setMaxValue(data);
    }
    else
    {
        edit->setText("");
    }
}

void Form::on_lineEditMinValue_editingFinished()
{
    qreal data = ui->lineEditMinValue->text().toFloat();

   if(dial1->setMinValue(data))
   {
      dial1->setMinValue(data);
   }
   else
   {
       ui->lineEditMinValue->setText("");
   }
}

void Form::on_lineEditCurValue_editingFinished()
{
   qreal data = ui->lineEditCurValue->text().toFloat();

   dial1->setTimerType(100,(dial1->MaxValue()-dial1->MinValue())/40);
   dial2->setTimerType(100,(dial2->MaxValue()-dial2->MinValue())/40);

   if(dial1->setEndValue(data))
   {
      dial2->setEndValue(data);
   }
   else
   {
       ui->lineEditCurValue->setText("");
   }
}

void Form::on_lineEdit_14_editingFinished()
{
    int data = ui->lineEdit_14->text().toInt();

    if(dial1->set_Center_decimal(data))
    {
        dial2->set_Center_decimal(data);
    }
    else
    {
        ui->lineEdit_14->setText("");
    }
}

void Form::on_lineEdit_13_editingFinished()
{
    int data = ui->lineEdit_13->text().toInt();

    if(dial1->set_Scale_decimal(data))
    {
        dial2->set_Scale_decimal(data);
    }
    else
    {
        ui->lineEdit_13->setText("");
    }
}
