#ifndef WAVEFORM_H
#define WAVEFORM_H
#include "fourierseries.h"
#include <QVector>


class Waveform
{
    double _t0 = 0;
    double _delta_t = 1;
    size_t _points = 0;
    FourierSeries _FSeries;
    QVector<double> _val;
    QVector<double> _time;
public:
    Waveform();
    ~Waveform();
    void setFourierSeries(FourierSeries& );
    void setTime(double, double);
    void setPoints(size_t);

    QVector<double>& getValuesVector();
    QVector<double>& getTimeVector();

    void calculateSignal();




};

#endif // WAVEFORM_H
