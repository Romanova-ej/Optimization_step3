#include "QMethodDlg.h"
#include "ui_QMethodDlg.h"
#include <QDebug>
#include <QLineEdit>
#include <QString>
#include <QMessageBox>

QMethodDlg::QMethodDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QMethodDlg),
    RSparam(new RSOptions(this)),eps(0.001),num(1000)
{
    ui->setupUi(this);
    ui->eEdit->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*|0)(\\.|,)[0-9]{8,}"), this));
    ui->RSButton->hide();
    connect(this,SIGNAL(accepted()),this,SLOT(on_okButton_clicked()));
}

QMethodDlg::~QMethodDlg()
{
    delete ui;
}

void QMethodDlg::on_cr1_clicked()
{
    ui->EorNlabel->setText("Epsilon");
    ui->eEdit->setText(QString::number(eps));
        ui->eEdit->setValidator(new QRegExpValidator(QRegExp("^0(\\.|,)[0-9]{1,}"), this));
}

void QMethodDlg::on_cr2_clicked()
{
    ui->EorNlabel->setText("Number");
        ui->eEdit->setText(QString::number(num));
           ui->eEdit->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*)[0-9]{8,}"), this));
}

void QMethodDlg::on_cr3_clicked()
{
    ui->EorNlabel->setText("Number");
        ui->eEdit->setText(QString::number(num));
         ui->eEdit->setValidator(new QRegExpValidator(QRegExp("^([1-9][0-9]*)[0-9]{8,}"), this));
}

void QMethodDlg::on_cr4_clicked()
{
    ui->EorNlabel->setText("Epsilon");
        ui->eEdit->setText(QString::number(eps));
                ui->eEdit->setValidator(new QRegExpValidator(QRegExp("^0(\\.|,)[0-9]{1,}"), this));
}

void QMethodDlg::on_okButton_clicked()
{
    bool Ok(true);
//выбор метода
if(ui->Fletcher->isChecked()){
opt=make_shared<FletcherRivs>();
}
if(ui->RandomS->isChecked())
    opt=make_shared<RandomSearch>(RSparam->getP(),RSparam->getC());
//выбор критерия
QString str=ui->eEdit->text();
if(ui->cr1->isChecked()){
    eps=str.toDouble();
    breakeCriterion=make_shared<CriterionGradNorm>(eps);
}
if(ui->cr2->isChecked()){
      num=str.toInt();
    breakeCriterion=make_shared<CriterionNumOfIteration>(num);
}
if(ui->cr3->isChecked()){
     num=str.toInt();
    breakeCriterion=make_shared<CriterionNumOfNochangeIteration>(num);
}
if(ui->cr4->isChecked()){
     eps=str.toDouble();
    breakeCriterion=make_shared<CriterionDifferenceOfValuef>(eps);
}
if(eps==0){
    Ok=false;
     QMessageBox::information(NULL,QObject::tr("Information"),tr("Epsilon must be positive!"));
}
if(Ok){
emit goChangeMethodOrCriterion(opt,breakeCriterion);
emit close();
}
}

void QMethodDlg::on_RandomS_clicked()
{
    ui->RSButton->show();
}

void QMethodDlg::on_RSButton_clicked()
{
    RSparam->show();
}

void QMethodDlg::on_Fletcher_clicked()
{
    ui->RSButton->hide();
}
