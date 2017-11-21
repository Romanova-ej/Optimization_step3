#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMethodDlg.h"
#include "QFuncDlg.h"
#include <memory>
#include <QPainter>
#include <QPen>
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//f=FunctionDialog.getFunction();
//логику бы не сюда писать вообще-то, но хз тогда, куда
    f=make_shared<Fun4>();
    opt=make_shared<FletcherRivs>();
    breakeCriterion=make_shared<CriterionGradNorm>(0.000001,10000);
//    opt=make_shared<RandomSearch>(f->getArea());
//    breakeCriterion=make_shared<CriterionNumOfIteration>(1000);
    x0.push_back(-0.5);//не задавать, а резервировать место
    x0.push_back(0.5);
    deque<vector<double> > path(opt->getTrajectory());//не задавать, а резервировать место
QCPAbstractPlottable* a=0;
   // opt->minimize(x0,*f,*breakeCriterion);

//на самом деле пусть при открытии ничего не рисуется, это пока так
    // потом при выборе f и  opt рисуется только карта
    //траектория рисуется только если тыкнем

   // deque<vector<double> > path(opt->getTrajectory());//запихнули траектории метода (в некоторых случаях перерисовки,
    //нарпимер, после диалога, нужно каждый раз вызывать перед этим minimize)


    // configure axis rect:
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables); //by dragging/zooming
    ui->customPlot->axisRect()->setupFullAxesBox(true);
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);
    int nx = 500;//сделать какую-нибудь константу адекватную
    int ny = 500;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(f->getArea().getLeft()[0], f->getArea().getRight()[0]), QCPRange(f->getArea().getLeft()[1], f->getArea().getRight()[1])); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
    //colorMap->data()->setRange(QCPRange(0, 2), QCPRange(0, 2));//картинка красивее
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
      for (int yIndex=0; yIndex<ny; ++yIndex)
      {
        colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
    //    double r = 3*qSqrt(x*x+y*y)+1e-2;
        vector<double> arg(2);
        arg[0]=x; arg[1]=y;
        double r=f->f(arg);
       // double r=qSin(x)*qCos(y);//красиво. границы можно взять -+5
       // z = 2*x*(qCos(r+2)/r-qSin(r+2)/r); // the B field strength of dipole radiation (modulo physical constants)
        colorMap->data()->setCell(xIndex, yIndex, r);
      }
    }

    // add a color scale:
    QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
    ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale   (сопоставление карты и цветовой гаммы)
    colorScale->axis()->setLabel("Magnetic Field Strength");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);//gpPolar,gpCold,gpHot,
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:(масштабируем цвет и данные)
    colorMap->rescaleDataRange();

    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->customPlot);
    ui->customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->customPlot->rescaleAxes();




    //траектория
//    QCPCurve *fermatSpiral1 = new QCPCurve( ui->customPlot->xAxis,  ui->customPlot->yAxis);
//    // generate the curve data points:
//    const int pointCount = path.size();
//    QVector<QCPCurveData> dataSpiral1(pointCount);
//    for (int i=0; i<pointCount; ++i)
//    {
//      dataSpiral1[i] = QCPCurveData(i, path[i][0],(path[i][1]));
//    }
//    // pass the data to the curves; we know t (i in loop above) is ascending, so set alreadySorted=true (saves an extra internal sort):
//    fermatSpiral1->data()->set(dataSpiral1, true);
//    fermatSpiral1->setScatterStyle((QCPScatterStyle(QCPScatterStyle::ssDisc , 5)));
//    // color the curves:
//    fermatSpiral1->setPen(QPen(Qt::red));
connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)));
}
void MainWindow:: goFunDlg(){

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFunctions_triggered()
{
QFuncDlg* funParam = new QFuncDlg(this);
funParam->show();
}

void MainWindow::on_actionMethods_triggered()
{
    QMethodDlg* metParam=new QMethodDlg(this);
    metParam->show();
}

void MainWindow::on_actionF_triggered()
{
    QFuncDlg* funParam = new QFuncDlg(this);
    funParam->show();
   // FunctionDialog.show();


}

void MainWindow::on_actionMethod_triggered()
{
    QMethodDlg* metParam=new QMethodDlg(this);
    metParam->show();
}

void MainWindow::on_offButton_clicked()
{

}

//рисование   рисование  рисование   рисование  рисование
//void MainWindow::paintEvent(QPaintEvent *event)
//{
  //  Q_UNUSED(event);



//deque<vector<double> > path(opt->getTrajectory());//запихнули траектории метода (в некоторых случаях перерисовки,
////нарпимер, после диалога, нужно каждый раз вызывать перед этим minimize)


//// configure axis rect:
//ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables); //by dragging/zooming
//ui->customPlot->axisRect()->setupFullAxesBox(true);
//ui->customPlot->xAxis->setLabel("x");
//ui->customPlot->yAxis->setLabel("y");

//// set up the QCPColorMap:
//QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);
//int nx = 500;//сделать какую-нибудь константу адекватную
//int ny = 500;
//colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
//colorMap->data()->setRange(QCPRange(f->getArea().getLeft()[0], f->getArea().getRight()[0]), QCPRange(f->getArea().getLeft()[1], f->getArea().getRight()[1])); // and span the coordinate range -4..4 in both key (x) and value (y) dimensions
////colorMap->data()->setRange(QCPRange(0, 2), QCPRange(0, 2));//картинка красивее
//// now we assign some data, by accessing the QCPColorMapData instance of the color map:
//double x, y;
//for (int xIndex=0; xIndex<nx; ++xIndex)
//{
//  for (int yIndex=0; yIndex<ny; ++yIndex)
//  {
//    colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
////    double r = 3*qSqrt(x*x+y*y)+1e-2;
//    vector<double> arg(2);
//    arg[0]=x; arg[1]=y;
//    double r=f->f(arg);
//   // double r=qSin(x)*qCos(y);//красиво. границы можно взять -+5
//   // z = 2*x*(qCos(r+2)/r-qSin(r+2)/r); // the B field strength of dipole radiation (modulo physical constants)
//    colorMap->data()->setCell(xIndex, yIndex, r);
//  }
//}

//// add a color scale:
//QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
//ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
//colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
//colorMap->setColorScale(colorScale); // associate the color map with the color scale   (сопоставление карты и цветовой гаммы)
//colorScale->axis()->setLabel("Magnetic Field Strength");

//// set the color gradient of the color map to one of the presets:
//colorMap->setGradient(QCPColorGradient::gpPolar);//gpPolar,gpCold,gpHot,
//// we could have also created a QCPColorGradient instance and added own colors to
//// the gradient, see the documentation of QCPColorGradient for what's possible.

//// rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:(масштабируем цвет и данные)
//colorMap->rescaleDataRange();

//// make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
//QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->customPlot);
//ui->customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
//colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

//// rescale the key (x) and value (y) axes so the whole color map is visible:
//ui->customPlot->rescaleAxes();




////траектория
//QCPCurve *fermatSpiral1 = new QCPCurve( ui->customPlot->xAxis,  ui->customPlot->yAxis);
//// generate the curve data points:
//const int pointCount = path.size();
//QVector<QCPCurveData> dataSpiral1(pointCount);
//for (int i=0; i<pointCount; ++i)
//{
//  dataSpiral1[i] = QCPCurveData(i, path[i][0],(path[i][1]));
//}
//// pass the data to the curves; we know t (i in loop above) is ascending, so set alreadySorted=true (saves an extra internal sort):
//fermatSpiral1->data()->set(dataSpiral1, true);
//fermatSpiral1->setScatterStyle((QCPScatterStyle(QCPScatterStyle::ssDisc , 5)));
//// color the curves:
//fermatSpiral1->setPen(QPen(Qt::red));
//
//}


void MainWindow::mousePress(QMouseEvent* newClick)
{
  // if an axis is selected, only allow the direction of that axis to be dragged
  // if no axis is selected, both directions may be dragged
int xx=newClick->x();//координаты клика в пикселях по оси x
int yy=newClick->y();//координаты клика в пикселях по оси y

double xinPlot=ui->customPlot->xAxis->pixelToCoord(xx);//координаты относительно графика
double yinPlot=ui->customPlot->yAxis->pixelToCoord(yy);

//введем проверку, что мы кликнули в график, а не в остальное пространство виджета
//мб вынести проверку в отдельную булевскую ункцию
if((xinPlot<=f->getArea().getRight()[0])&&(xinPlot>=f->getArea().getLeft()[0])
        &&(yinPlot<=f->getArea().getRight()[1])&&
        (yinPlot>=f->getArea().getLeft()[1])){
    x0[0]=xinPlot; x0[1]=yinPlot;//в главной функции на x0 должна быть зарезервирована память (чтобы так обращаться)

    opt=make_shared<RandomSearch>(f->getArea());
    breakeCriterion=make_shared<CriterionNumOfIteration>(1000);
     opt->minimize(x0,*f,*breakeCriterion);
     path=opt->getTrajectory();
      //рисование
ui->customPlot->removePlottable(a);
 QCPCurve *fermatSpiral1 = new QCPCurve( ui->customPlot->xAxis,  ui->customPlot->yAxis);
      // generate the curve data points:
      const int pointCount = path.size();
      QVector<QCPCurveData> dataSpiral1(pointCount);
      for (int i=0; i<pointCount; ++i)
      {
        dataSpiral1[i] = QCPCurveData(i, path[i][0],(path[i][1]));
      }

      // pass the data to the curves; we know t (i in loop above) is ascending, so set alreadySorted=true (saves an extra internal sort):
      fermatSpiral1->data()->set(dataSpiral1, true);
      fermatSpiral1->setScatterStyle((QCPScatterStyle(QCPScatterStyle::ssDisc , 5)));
      // color the curves:
      fermatSpiral1->setPen(QPen(Qt::red));
 a=fermatSpiral1;

}

}
