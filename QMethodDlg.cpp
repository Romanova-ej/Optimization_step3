#include "QMethodDlg.h"
#include "ui_QMethodDlg.h"

QMethodDlg::QMethodDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMethodDlg)
{
    ui->setupUi(this);
    ui->okButton->setEnabled(false);
    QRegExp expr ("[0-9]{1,2}");
    ui->eEdit->setValidator(new QRegExpValidator(expr,this));
    connect(ui->eEdit,SIGNAL(textChanged(QString)),this,SLOT(OKEnabled()));
}

QMethodDlg::~QMethodDlg()
{
    delete ui;
}

void QMethodDlg::OKEnabled(){
    ui->okButton->setEnabled(ui->eEdit->hasAcceptableInput());
}
