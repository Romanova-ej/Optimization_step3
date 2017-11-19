#include "QFuncDlg.h"
#include "ui_QFuncDlg.h"

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
