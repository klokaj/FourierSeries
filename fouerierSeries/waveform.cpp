#include "waveform.h"
#include <QtMath>

Waveform::Waveform()
{

}

void Waveform::setFourierSeries(FourierSeries& FSeries)
{
    _FSeries = FSeries;
}

Waveform::~Waveform()
{
}

void Waveform::setTime(double t0, double delta_t)
{
    _t0 = t0;
    _delta_t = delta_t;
}

void Waveform::setPoints(size_t points)
{
    _points = points;
}

QVector<double> &Waveform::getValuesVector()
{
    return _val;
}

QVector<double> &Waveform::getTimeVector()
{
    return _time;
}

void Waveform::calculateSignal()
{
    _val.clear();
    _time.clear();
    double time = _t0;
    double dt = _delta_t/_points;
    double theta = time*_FSeries.getFrequency()*2*M_PI;
    //double phase = time*_FSeries.getFrequency()*2*M_PI;
    double dtheta = _FSeries.getFrequency()*2*M_PI*dt;
    while(time < _t0 + _delta_t)
    {
        double val = 0;
        for(auto it : _FSeries.getHarmonics())
        {
            val += it.a*qSin(theta*it.nr) + it.b*qCos(theta*it.nr);
        }
        _val.append(val);
        _time.append(time);

        theta += dtheta;
        time += dt;
    }
}



