#ifndef FOURIERSERIES_H
#define FOURIERSERIES_H

#include <cmath>
#include <stddef.h>
#include <string>
#include "harmonic.h"
#include <stddef.h>
#include <vector>

enum class FourierSeriesType{
    pulse,
    triangle,
    sawtooth,
    sine,
};

using namespace std;
class FourierSeries{
protected:
    double _freq;
    vector<harmonic> harmonics{};
    FourierSeriesType _FSType;

public:
    ~FourierSeries(){}
    FourierSeries() : FourierSeries(0) {}
    FourierSeries(double freq): _freq(freq), harmonics{} {}
    void setFrequency(double freq);

    double getFrequency() const;


    void calculateCoeff(FourierSeriesType FSType, size_t maxHarmonic, double amp);

    void clear();
    void pushBack(size_t nr, double a, double b);


    void print();

    vector<harmonic>& getHarmonics();



private:
    void calculateCoeffPulse(size_t maxHarmonic, double amp);
    void calculateCoeffTriangle(size_t maxHarmonic, double amp);
    void calculateCoeffSawtooth(size_t maxHarmonic, double amp);
    void calculateCoeffSine(size_t maxHarmonic, double amp);

    //virtual void saveToFile(ofstream& ) = 0;

};

#endif
