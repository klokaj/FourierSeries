
#include "fourierSeries.h"

void FourierSeries::setFrequency(double freq){
    _freq = freq;
}

double FourierSeries::getFrequency() const{
    return _freq;
}


void FourierSeries::calculateCoeff(FourierSeriesType FSType, size_t maxHarmonic, double amp){
    _FSType = FSType;
    switch(_FSType){
    case FourierSeriesType::pulse:
        calculateCoeffPulse(maxHarmonic, amp);
        break;
    case FourierSeriesType::sine:
        calculateCoeffSine(maxHarmonic, amp);
        break;
    case FourierSeriesType::triangle:
        calculateCoeffTriangle(maxHarmonic, amp);
        break;
    case FourierSeriesType::sawtooth:
        calculateCoeffSawtooth(maxHarmonic, amp);
        break;
    }
}

void FourierSeries::clear()
{
    harmonics.clear();
}

void FourierSeries::pushBack(size_t nr, double a, double b)
{
    harmonics.push_back(harmonic(nr, a, b));
}

void FourierSeries::print(){
    for(auto it : harmonics){
        cout << it << ", freq = " << (it.nr + 1) * _freq <<endl;
    }
}

vector<harmonic> &FourierSeries::getHarmonics(){
    return harmonics;
}

void FourierSeries::calculateCoeffPulse(size_t maxHarmonic, double amp)
{
    harmonics.clear();
    harmonics.reserve(maxHarmonic);
    for(size_t i = 0; i<= maxHarmonic; i++){
        if(i%2){
            harmonics.push_back(harmonic(i , (4*amp)/(i*M_PI),0));
        }
        else{
            harmonics.push_back(harmonic(i, 0, 0));
        }
    }
}

void FourierSeries::calculateCoeffTriangle(size_t maxHarmonic, double amp)
{
    harmonics.clear();
    harmonics.reserve(maxHarmonic);

    for(size_t i = 0; i< maxHarmonic; i ++){

        if(! (i%2)){
        harmonics.push_back( harmonic(i , 0,0));

        }
        else{
            harmonics.push_back( harmonic(i, 0, amp*40/((pow(M_PI,2)*pow(i,2)))));
        }
    }
}

void FourierSeries::calculateCoeffSawtooth(size_t maxHarmonic,double amp)
{
    harmonics.clear();
    harmonics.reserve(maxHarmonic);
    harmonics.push_back(harmonic(0,0,0));

    for(size_t i = 1; i < maxHarmonic; i += 1){
        harmonics.push_back(harmonic(i , (amp*2/(i*M_PI))*pow(-1, i), 0));
    }
}

void FourierSeries::calculateCoeffSine(size_t maxHarmonic, double amp)
{
    harmonics.clear();
    harmonics.reserve(maxHarmonic);
    for(size_t i = 0; i<= maxHarmonic; i++){
           harmonics.push_back(harmonic(i , 0 ,0));
    }
    harmonics[1] = harmonic(1, amp,0);
}



