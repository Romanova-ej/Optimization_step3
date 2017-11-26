#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMethodDlg.h"
#include "QFuncDlg.h"
#include <memory>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    QFunctionDlg (new QFuncDlg( this ) ),
    QMethodOptDlg(new QMethodDlg(this))//
{
    ui->setupUi(this);

    f=make_shared<Fun6>();
    opt=make_shared<FletcherReeves>();
    breakeCriterion=make_shared<CriterionGradNorm>(0.001);

    x0.push_back(-0.5);
    x0.push_back(0.5);
    opt->minimize(x0,*f,*breakeCriterion);
    path=opt->getTrajectory();
    a=0; map=0;


    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this,
            SLOT(mousePress(QMouseEvent*)));
    connect(QFunctionDlg,SIGNAL(goDrawMapF(shared_ptr<Function> )),this,
            SLOT(DrawMapF(shared_ptr<Function>)) );
    connect(this,SIGNAL(goDrawMapF(shared_ptr<Function> )),this,
            SLOT(DrawMapF(shared_ptr<Function>)) );
    connect(QMethodOptDlg,SIGNAL(goChangeMethodOrCriterion(shared_ptr<Optimization>,
                                                           shared_ptr<Criterion>)),
            this,SLOT(setMethodAndCriterion(shared_ptr<Optimization>,
                                            shared_ptr<Criterion>)));
    emit goDrawMapF(f);

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionFunctions_triggered()
{
    QFunctionDlg->show();
}

void MainWindow::on_actionMethods_triggered()
{
    QMethodOptDlg->show();
}

void MainWindow::on_actionF_triggered()
{
    QFunctionDlg->show();


}

void MainWindow::on_actionMethod_triggered()
{
    QMethodOptDlg->show();
}

void MainWindow::on_offButton_clicked()
{

}

void MainWindow::mousePress(QMouseEvent* newClick)
{
    int xx=newClick->x();//координаты клика в пикселях по оси x
    int yy=newClick->y();//координаты клика в пикселях по оси y

    double xinPlot=ui->customPlot->xAxis->pixelToCoord(xx);//координаты относительно графика
    double yinPlot=ui->customPlot->yAxis->pixelToCoord(yy);

    //проверка, что попали в область
    if((xinPlot<=f->getArea().getRight()[0])&&(xinPlot>=f->getArea().getLeft()[0])
            &&(yinPlot<=f->getArea().getRight()[1])&&
            (yinPlot>=f->getArea().getLeft()[1])){
        x0[0]=xinPlot; x0[1]=yinPlot;
        vector<double> result=opt->minimize(x0,*f,*breakeCriterion);
        int numIterations=opt->getCounter();
        path=opt->getTrajectory();

        ui->customPlot->removePlottable(a);
        QCPCurve *fermatSpiral1 = new QCPCurve( ui->customPlot->xAxis,
                                                ui->customPlot->yAxis);
        // generate the curve data points:
        const int pointCount = path.size();
        QVector<QCPCurveData> dataSpiral1(pointCount);
        for (int i=0; i<pointCount; ++i)
        {
            dataSpiral1[i] = QCPCurveData(i, path[i][0],(path[i][1]));
        }

        // pass the data to the curves; we know t (i in loop above) is ascending, so set alreadySorted=true (saves an extra internal sort):
        fermatSpiral1->data()->set(dataSpiral1, true);
        fermatSpiral1->setScatterStyle((QCPScatterStyle
                                        (QCPScatterStyle::ssDisc , 5)));
        // color the curves:
        fermatSpiral1->setPen(QPen(Qt::red));
        a=fermatSpiral1;
        //добавим инфу вниз окна
        QString str;
        QTextStream(&str) << "|| "<<opt->getMethodName() << " || "<<numIterations<<
                             " iterations ||"<<" x = ( "<<result[0]<<" , "<<result[1]
                          <<" ) || f(x) = "<<f->f((result))<<" || f="<<
                            f->getFunctionName()<<" ||";
        ui->statusBar->showMessage(str);
    }

}

void MainWindow::DrawMapF(shared_ptr<Function> g){

    f=g;
    ui->customPlot->removePlottable(a);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom |
                                    QCP::iSelectPlottables); //by dragging/zooming
    ui->customPlot->axisRect()->setupFullAxesBox(true);
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->yAxis->setLabel("y");

    ui->customPlot->removePlottable(map);//
    // set up the QCPColorMap:
    QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis,
                                            ui->customPlot->yAxis);
    int nx = 500;//сделать какую-нибудь константу адекватную
    int ny = 500;
    colorMap->data()->setSize(nx, ny); // we want the color map to have nx * ny data points
    colorMap->data()->setRange(QCPRange(f->getArea().getLeft()[0],
                               f->getArea().getRight()[0]),
            QCPRange(f->getArea().getLeft()[1], f->getArea().getRight()[1]));
    // now we assign some data, by accessing the QCPColorMapData instance of the color map:
    double x, y;
    for (int xIndex=0; xIndex<nx; ++xIndex)
    {
        for (int yIndex=0; yIndex<ny; ++yIndex)
        {
            colorMap->data()->cellToCoord(xIndex, yIndex, &x, &y);
            vector<double> arg(2);
            arg[0]=x; arg[1]=y;
            double r=f->f(arg);
            // double r=qSin(x)*qCos(y);//красиво. границы можно взять -+5
            colorMap->data()->setCell(xIndex, yIndex, r);
        }
    }

    // add a color scale:
    ui->customPlot->removeEventFilter(scaleMap);///////+++++++++++++++++++++++++++++-----------
    QCPColorScale *colorScale = new QCPColorScale(ui->customPlot);
    ui->customPlot->plotLayout()->addElement(0, 1, colorScale); // add it to the right of the main axis rect
    colorScale->setType(QCPAxis::atRight); // scale shall be vertical bar with tick/axis labels right (actually atRight is already the default)
    colorMap->setColorScale(colorScale); // associate the color map with the color scale   (сопоставление карты и цветовой гаммы)
    colorScale->axis()->setLabel("f");

    // set the color gradient of the color map to one of the presets:
    colorMap->setGradient(QCPColorGradient::gpPolar);//gpPolar,gpCold,gpHot,
    // we could have also created a QCPColorGradient instance and added own colors to
    // the gradient, see the documentation of QCPColorGradient for what's possible.

    // rescale the data dimension (color) such that all data points lie in the span visualized by the color gradient:(масштабируем цвет и данные)
    colorMap->rescaleDataRange();

    ui->customPlot->removeEventFilter(marginMap);
    // make sure the axis rect and color scale synchronize their bottom and top margins (so they line up):
    QCPMarginGroup *marginGroup = new QCPMarginGroup(ui->customPlot);
    ui->customPlot->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop,
                                               marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    // rescale the key (x) and value (y) axes so the whole color map is visible:
    ui->customPlot->rescaleAxes();
    map=colorMap;
    scaleMap=colorScale;
    marginMap=marginGroup;

    ui->customPlot->replot();

}

void MainWindow::setMethodAndCriterion(shared_ptr<Optimization>optim,
                                       shared_ptr<Criterion>crit){
    opt=optim; breakeCriterion=crit;
}


