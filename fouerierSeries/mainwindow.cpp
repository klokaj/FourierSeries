#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Fourier Series");
    ui->plot->addGraph();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addPoint(double x, double y)
{
     qv_x.append(x);
     qv_y.append(y);
}

void MainWindow::clearData()
{
      qv_x.clear();
      qv_y.clear();
}

void MainWindow::plot()
{
     ui->plot->graph(0)->setData(qv_x, qv_y);
     ui->plot->rescaleAxes();
     ui->plot->replot();
     ui->plot->update();
}

void MainWindow::createWaveform()
{
    double t0 = ui->t_0->value();
    double delta_t = ui->delta_t->value();
    double points = ui->points->value();

    qv_x.clear();
    qv_y.clear();

    _Waveform.setTime(t0, delta_t);
    _Waveform.setPoints(size_t(points));
    _Waveform.setFourierSeries(FSeries);
    _Waveform.calculateSignal();


    qv_x = _Waveform.getTimeVector();
    qv_y = _Waveform.getValuesVector();
}


void MainWindow::printSeriesCoeffs()
{

    int coulomnNr = 0;
    QTableWidgetItem item;
    ui->table->setColumnCount(int(FSeries.getHarmonics().size()));

    for(auto it: FSeries.getHarmonics()){
        ui->table->setItem(0, coulomnNr, new QTableWidgetItem(QString::number(int(it.nr))));
        ui->table->setItem(1, coulomnNr, new QTableWidgetItem(QString::number(double(it.a))));
        ui->table->setItem(2, coulomnNr, new QTableWidgetItem(QString::number(double(it.b))));
        coulomnNr++;
    }
}


void MainWindow::getSeriesCoeffsFromTable()
{
   QString QSnr, QSa, QSb;
   FSeries.clear();
   for(int i = 0; i < ui->table->columnCount(); i++){
        QSnr = ui->table->item(0,i)->text();
        QSa = ui->table->item(1,i)->text();
        QSb = ui->table->item(2,i)->text();
        FSeries.pushBack(size_t(QSnr.toInt()), QSa.toDouble(), QSb.toDouble());
   }
}

void MainWindow::loadHarmonicsFromFile(QString)
{

}


void MainWindow::on_btn_clear_clicked()
{
    clearData();
    plot();
}





void MainWindow::on_btn_plot_clicked()
{
    getSeriesCoeffsFromTable();
createWaveform();
    plot();
}

void MainWindow::on_btn_generate_clicked()
{
    double freq = ui->doubleSpinBox_freq->value();
    double maxHarmonic = ui->spinBox_maxHarmonic->value();
    double amp = ui->doubleSpinBox_amp->value();

    FourierSeriesType FSType;
    switch(ui->comboBox_waveType->currentIndex()){
    case 0:
        FSType = FourierSeriesType::sine;
    break;
    case 1:
        FSType = FourierSeriesType::pulse;
    break;
    case 2:
        FSType = FourierSeriesType::triangle;
    break;
    case 3:
        FSType = FourierSeriesType::sawtooth;
    break;
    default:
        FSType = FourierSeriesType::sine;
    };

    FSeries.setFrequency(freq);
    FSeries.calculateCoeff(FSType, size_t(maxHarmonic), amp);

    printSeriesCoeffs();


}

void MainWindow::on_pushButton_load_clicked()
{

    QString   filename = QFileDialog::getOpenFileName(this,
            tr("Open Text File"), "/home/file", tr("Image Files (*.txt)"));

    QFile file(filename);
        if(!file.open(QIODevice::ReadOnly)){
             QMessageBox::information(0, "error", file.errorString());
             return;
        }

        QTextStream in(&file);
        QString line;
        QStringList list;

        FSeries.clear();
        line = in.readLine();
        list =  line.split("=");
        FSeries.setFrequency(list[1].toInt());

        while(!in.atEnd()){
            line = in.readLine();
            list =  line.split(",");
            FSeries.pushBack(size_t(list[0].toInt()), list[1].toDouble(), list[2].toDouble());
        }

        file.close();

   printSeriesCoeffs();
}

void MainWindow::on_pushButton_addHarmonic_clicked()
{
    FSeries.pushBack(0,0,0);
    printSeriesCoeffs();

}

void MainWindow::on_pushButton_clicked()
{

}
