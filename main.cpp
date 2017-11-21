#include "mainwindow.h"
#include <QApplication>
#include "HArea.h"
#include "HCriterion.h"
#include "HFunction.h"
#include "HOptimization.h"
#include "Hother.h"
#include "QMethodDlg.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow win;
    win.showMaximized();

    //QFunctionDlg*  funD=new QFunctionDlg;
    //QMethodDlg* met=new QMethodDlg;
    //met->show();
  // funD.setMinimumWidth(200);
   //funD->show();
    return a.exec();
}
