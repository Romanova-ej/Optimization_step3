#ifndef QMETHODDLG_H
#define QMETHODDLG_H

#include <QDialog>

namespace Ui {
class QMethodDlg;
}

class QMethodDlg : public QDialog
{
    Q_OBJECT

public:
    explicit QMethodDlg(QWidget *parent = 0);
    ~QMethodDlg();
public slots:
   void  OKEnabled();
private:
    Ui::QMethodDlg *ui;
};

#endif // QMETHODDLG_H
