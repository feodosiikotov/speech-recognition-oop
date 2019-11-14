#include "mfccprocessor.h"
#include "frame.h"
#include <vector>
#include <complex>
#include <cmath>
#include <stdio.h>

using namespace std;

MFCCProcessor::MFCCProcessor(const vector<Frame>& word, double min_freq, double max_freq, int amount_of_filters,
                             int frequency, double smooth_coef) : _mfcc()
{
    for (auto frame: word){
        auto transformed = _fourierTransform(frame, smooth_coef);
        auto filters = _getFilters(min_freq, max_freq, amount_of_filters, frequency, word[0].size());
        auto mel_coefs = _getMelCoefs(filters, transformed);
        auto mfcc_coefs = _countMFCC(mel_coefs);
        _mfcc.push_back(mfcc_coefs);
    }
}

vector<double> MFCCProcessor::_fourierTransform(const Frame & frame, double smooth_coef)
{
    //Мона еще сделать fast версию будет попробовать. Но везде в инете примеры только если размер массива - степень 2
    //либо найти не со степенью 2 пример, либо как-то к степени 2 приводить
    //http://psi-logic.narod.ru/fft/ffta.htm
    //Тут для четного N
    //Ну в любом случае, придется либо прибавлять, либо убирать какие-то значения
    //если надо будет побыстрее
    //Можно будет потом с этим поиграться
    vector<double> transformed_array;
    auto frame_size = frame.size();
    for (int k = 0; k < frame_size; k++){
        complex<double> sum(0, 0);
        for (int n = 0; n < frame_size; n++){
            complex<double> im_one(0, 1);
            complex<double> factor = exp((-2.*M_PI*im_one*double(k*n))/double(frame_size));
            sum += frame.at(n)*factor;
        }
        sum = sum*(smooth_coef - (1-smooth_coef)*cos(2*M_PI*k/(frame_size-1)));
        //http://practicalcryptography.com/miscellaneous/machine-learning/guide-mel-frequency-cepstral-coefficients-mfccs/
        //Крч вообще инфы чет вообще нет по тому, как избавляться от комплексных значений
        //Челик берет квадратный корень от нормы
        //Я сделал вроде так, как написано по этой ссылке
        //Надо будет еще поискать инфу
        double transformed_value = norm(sum)/frame_size;
        transformed_array.push_back(transformed_value);
    }
    return transformed_array;
}

double MFCCProcessor::_freqToMel(double val)
{
    return 1127.*log(1+(val/700.));
}

double MFCCProcessor::_melToFreq(double val)
{
    return 700*(exp(val/1127.) -1);
}

vector<vector<int>> MFCCProcessor::_getFilters(double min_freq, double max_freq, int amount_of_filters, int frequency, int frame_size)
{
    double start = _freqToMel(min_freq), finish = _freqToMel(max_freq);
    double step = (finish-start)/(amount_of_filters+1);
    vector<int> freq_values;
    for (int i = 0; i < amount_of_filters + 2; i++){
        int freq = floor((frame_size+1)*_melToFreq(start+i*step)/frequency);
        freq_values.push_back(freq);
    }
    vector<vector<int>> filter_array(amount_of_filters);

    for (int m = 1; m < amount_of_filters; m++){
        filter_array[m-1].resize(frame_size);
        for (int k = 0; k < frame_size; k++){
            int value;
            if (freq_values[m-1] <= k and freq_values[m] >= k)
                value = (k - freq_values[m - 1]) / (freq_values[m] - freq_values[m - 1]);
            else if (freq_values[m] < k and k <= freq_values[m+1])
                value = (freq_values[m + 1] - k) / (freq_values[m + 1] - freq_values[m]);
            else
                value = 0;
            filter_array[m-1][k] = value;
        }
    }
    return filter_array;
}

vector<double> MFCCProcessor::_getMelCoefs(const vector<vector<int>> &filters, const Frame &frame)
{
    int amount_of_filters = filters.size();
    int frame_size = frame.size();
    vector<double> mel_coefs;
    for (int i = 0; i < amount_of_filters; i++){
        double sum = 0;
        for (int j = 0; j < frame_size; j++){
            sum += frame.at(j)*frame.at(j)*filters[i][j];
        }
        //Челик не уверен, нужно ли брать логарифм, так как значения нормализовали
        //Я тож тогда не уверен
        sum = log(sum);
        mel_coefs.push_back(sum);

    }
    return mel_coefs;
}

vector<double> MFCCProcessor::_countMFCC(vector<double> mel_coefs)
{
    vector<double> mfcc_coefs;
    int size = mel_coefs.size();
    for (int i=0; i<size; i++){
        double sum = 0;
        for (int j = 0; j < size; j++){
            sum += mel_coefs[j]*cos(M_PI*i*(j+0.5)/double(size));
        }
        mfcc_coefs.push_back(sum);
    }
    return mfcc_coefs;
}

vector<vector<double>> MFCCProcessor::getMFCC()
{
    return _mfcc;
}
