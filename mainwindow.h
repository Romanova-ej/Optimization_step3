#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "HFunction.h"
#include "QFuncDlg.h"
#include <QPainter>
#include "qcustomplot.h"
#include "HOptimization.h"
#include "HCriterion.h"
#include <QSettings>
#include "QMethodDlg.h"

namespace Ui {
class MainWindow;
}
class QFunDlg;
class QMethodDlg;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



shared_ptr<Function> f;
shared_ptr<Optimization> opt;
shared_ptr<Criterion> breakCriterion;
vector<double> x0;
deque<vector<double> > path;
QCPAbstractPlottable* a;
QCPAbstractPlottable* map;//
QCPColorScale* scaleMap;//
QCPMarginGroup* marginMap;////
QSharedPointer<QFuncDlg> FDlg;


/////////////
//QFuncDlg FunctionDialog;
// void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
    QFuncDlg * QFunctionDlg;//
    QMethodDlg * QMethodOptDlg;
public:
    void drawhelp();//

public slots:
    void mousePress(QMouseEvent*);
    void DrawMapF(shared_ptr<Function> f);
    void setMethodAndCriterion(shared_ptr<Optimization>,shared_ptr<Criterion>);
private slots:
    void on_actionFunctions_triggered();
    void on_actionMethods_triggered();
    void on_actionF_triggered();
    void on_actionMethod_triggered();
    void on_offButton_clicked();
signals:
    void goDrawMapF(shared_ptr<Function> );
};

#endif // MAINWINDOW_H
