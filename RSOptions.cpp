#include "RSOptions.h"
#include "ui_RSOptions.h"

RSOptions::RSOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RSOptions)
{
    ui->setupUi(this);
}

RSOptions::~RSOptions()
{
    delete ui;
}
