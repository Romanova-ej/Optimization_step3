#ifndef QFUNCDLG_H
#define QFUNCDLG_H

#include <QDialog>

namespace Ui {
class QFuncDlg;
}

class QFuncDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QFuncDlg(QWidget *parent = 0);
    ~QFuncDlg();

private:
    Ui::QFuncDlg *ui;
};

#endif // QFUNCDLG_H
