#include "QFuncDlg.h"
#include "ui_QFuncDlg.h"
#include <QDebug>
#include <QString>
#include <memory>
#include <QValidator>
#include <QMessageBox>

QFuncDlg::QFuncDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QFuncDlg)
{
    ui->setupUi(this);
}

QFuncDlg::~QFuncDlg()
{
    delete ui;
}

shared_ptr<Function> QFuncDlg::getFunction(){
    return f;
}

void QFuncDlg::on_okButton_clicked()
{
    bool Ok=true;
    double x1,x2,y1,y2;
    QString str=ui->x1Edit->text();
    x1=str.toDouble(&Ok);
    str=ui->x2Edit->text();
    x2=str.toDouble(&Ok);
    str=ui->y1Edit->text();
    y1=str.toDouble(&Ok);
    str=ui->y2Edit->text();
    y2=str.toDouble(&Ok);
    if((x2<x1)||(y2<y1)){
        QMessageBox::information(NULL,QObject::tr("Information"),tr("You entered an empty area!"));
        Ok=false;
    }
    int numFun=ui->listWidget->currentRow();
    if(Ok){
        vector<double>left;
        left.push_back(x1);
        left.push_back(y1);
        vector<double> right;
        right.push_back(x2);
        right.push_back(y2);
        Area D(left,right);
        switch (numFun)
            {
            case 0: {
                f = std::make_shared<Fun1>(D);
                break;
            }
            case 1: {
                f = std::make_shared<Fun3>(D);
                break;
            }
            case 2: {
                f = std::make_shared<Fun4>(D);
                break;
            }
        case 3:{
            f=std::make_shared<Fun6>(D);
            break;
        }
        default:
            break;
            }
        emit goDrawMapF(f);
        emit accept();
    }

}

void QFuncDlg::on_listWidget_currentRowChanged(int currentRow)
{
    shared_ptr<Function> tempg;
    switch (currentRow) {
    case 0:{
        tempg=make_shared<Fun1>();
        break;}
    case 1:{
          tempg=make_shared<Fun3>();
        break;
    }
    case 2:{
          tempg=make_shared<Fun4>();
        break;
    }
    case 3:{
          tempg=make_shared<Fun6>();
        break;
    }
    default:
        break;
    }
Area Dom=tempg->getArea();
    QString str=QString::number(Dom.getLeft()[0]);
    ui->x1Edit->setText(str);
    str=QString::number(Dom.getRight()[0]);
    ui->x2Edit->setText(str);
    str=QString::number(Dom.getLeft()[1]);
    ui->y1Edit->setText(str);
    str=QString::number(Dom.getRight()[1]);
    ui->y2Edit->setText(str);
}
