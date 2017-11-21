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


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();





    /////
    /// вот это всё тоже хотелось бы куда-то в осмысленную часть, а не в главное окно...но иначе, видимо,никак
shared_ptr<Function> f;
shared_ptr<Optimization> opt;
shared_ptr<Criterion> breakeCriterion;
vector<double> x0;
deque<vector<double> > path;
QCPAbstractPlottable* a;

/////////////
//QFuncDlg FunctionDialog;
// void paintEvent(QPaintEvent *event);//рисованиерисованиерисование
private:
    Ui::MainWindow *ui;
public slots:
    void goFunDlg();
    void mousePress(QMouseEvent*);
signals:
    void createFunDlg();
private slots:
    void on_actionFunctions_triggered();
    void on_actionMethods_triggered();
    void on_actionF_triggered();
    void on_actionMethod_triggered();
    void on_offButton_clicked();

};

#endif // MAINWINDOW_H
