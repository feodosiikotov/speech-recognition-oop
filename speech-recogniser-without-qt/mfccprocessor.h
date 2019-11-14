#ifndef MFCCPROCESSOR_H
#define MFCCPROCESSOR_H

#include "frame.h"
#include "frameprocessor.h"
#include <vector>
#include <complex>

class MFCCProcessor
{
public:
    MFCCProcessor(const vector<Frame>&, double min_freq, double max_freq, int amount_of_filters,
                  int frequency,
                  double smooth_coef=1);
   vector<vector<double>> getMFCC();
private:
    vector<double> _fourierTransform(const Frame&, double smooth_coef=1);
    vector<vector<int>> _getFilters(double min_freq, double max_freq, int amount_of_filters, int, int);
    vector<double> _getMelCoefs(const vector<vector<int>>& filters, const Frame& frame);
    double _freqToMel(double);
    double _melToFreq(double);
    vector<double> _countMFCC(vector<double> mel_coefs);
    vector<vector<double>> _mfcc;
};

#endif // MFCCPROCESSOR_H
