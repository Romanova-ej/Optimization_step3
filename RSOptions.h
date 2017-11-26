#ifndef RSOPTIONS_H
#define RSOPTIONS_H

#include <QDialog>
#include<memory>
#include "HOptimization.h"
#include "RSOptions.h"
#include "QMethodDlg.h"

namespace Ui {
class RSOptions;
}

class RSOptions : public QDialog
{
    Q_OBJECT

public:
    explicit RSOptions(QWidget *parent = 0);
    ~RSOptions();
    const double getP() const;
    const double getC() const;

private slots:
    void on_okeyButton_clicked();

signals:
    void RSOptChange();
private:
    Ui::RSOptions *ui;
    double p;
    double c;
};

#endif // RSOPTIONS_H
