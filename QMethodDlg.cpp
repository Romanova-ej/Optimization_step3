#include "QMethodDlg.h"
#include "ui_QMethodDlg.h"

QMethodDlg::QMethodDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMethodDlg)
{
    ui->setupUi(this);
}

QMethodDlg::~QMethodDlg()
{
    delete ui;
}
