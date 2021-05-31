#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fourierseries.h"
#include "waveform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addPoint(double x, double y);
    void clearData();
    void plot();
    void createWaveform();
    void printSeriesCoeffs(void);
    void getSeriesCoeffsFromTable();
    void loadHarmonicsFromFile(QString);


private slots:
    void on_btn_clear_clicked();
    void on_btn_plot_clicked();
    void on_btn_generate_clicked();

    void on_pushButton_load_clicked();

    void on_pushButton_addHarmonic_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QVector<double> qv_x, qv_y, qv_coeff, qv_freq;
    FourierSeries FSeries;
    Waveform _Waveform;
};

#endif // MAINWINDOW_H
