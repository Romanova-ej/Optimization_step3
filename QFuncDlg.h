#ifndef QFUNCDLG_H
#define QFUNCDLG_H

#include <QDialog>
#include <memory>
#include "HFunction.h"
#include "HArea.h"

namespace Ui {
class QFuncDlg;
}

class QFuncDlg : public QDialog
{
    Q_OBJECT
Area D;
shared_ptr<Function> f;
public:
    explicit QFuncDlg(QWidget *parent = 0);
    ~QFuncDlg();
//int getNumFunction() const;
//void setNumFunction(int numF);
//const Area& getAreaD() const;
//void setAreaD(const Area&);
shared_ptr<Function> getFunction();

private slots:
void on_okButton_clicked();
void on_listWidget_currentRowChanged(int currentRow);

signals:
void goDrawMapF(shared_ptr<Function> f);
private:
    Ui::QFuncDlg *ui;
};

#endif // QFUNCDLG_H
