#ifndef QMETHODDLG_H
#define QMETHODDLG_H

#include <QDialog>
#include "RSOptions.h"
#include <memory>
#include "HOptimization.h"

namespace Ui {
class QMethodDlg;
}
class RSOptions;
class QMethodDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QMethodDlg(QWidget *parent = 0);
    ~QMethodDlg();
private slots:
   void on_cr1_clicked();

   void on_cr2_clicked();

   void on_cr3_clicked();

   void on_cr4_clicked();

   void on_okButton_clicked();

   void on_RandomS_clicked();

   void on_RSButton_clicked();

   void on_Fletcher_clicked();
signals:
   void goChangeMethodOrCriterion(shared_ptr<Optimization>,shared_ptr<Criterion>);

private:
    Ui::QMethodDlg *ui;
    RSOptions* RSparam;
    shared_ptr<Optimization> opt;
    shared_ptr<Criterion> breakCriterion;
    double eps; int num;
};

#endif // QMETHODDLG_H
