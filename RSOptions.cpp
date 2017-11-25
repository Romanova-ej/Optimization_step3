#include "RSOptions.h"
#include "ui_RSOptions.h"

RSOptions::RSOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RSOptions),
    p(0.8),c(0.9)
{
    ui->setupUi(this);
        ui->pEdit->setValidator(new QRegExpValidator(QRegExp("^0(\\.|,)[0-9]{1,}"), this));
        ui->cEdit->setValidator(new QRegExpValidator(QRegExp("^0(\\.|,)[0-9]{1,}"), this));
}

RSOptions::~RSOptions()
{
    delete ui;
}

//void RSOptions::on_okButton_clicked()
//{
//    QString str=ui->pEdit->text();
//    p=str.toDouble();
//    str=ui->cEdit->text();
//    c=str.toDouble();
//}

const double RSOptions::getP() const{
    return p;
}
const double RSOptions::getC() const{
    return c;
}
void RSOptions::on_okeyButton_clicked(){
        QString str=ui->pEdit->text();
        p=str.toDouble();
        str=ui->cEdit->text();
        c=str.toDouble();
}
