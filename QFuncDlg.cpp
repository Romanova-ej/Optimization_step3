#include "QFuncDlg.h"
#include "ui_QFuncDlg.h"
#include <memory>

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
    //и остальные параметры из списка сюда
    int numFun=ui->listWidget->currentRow();
    if(Ok){
        vector<double>left;
        left.push_back(x1);
        left.push_back(x2);
        vector<double> right;
        right.push_back(y1);
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
        default:
            break;
            }
    }//и сигнал о перерисовке

}
