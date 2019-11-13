#ifndef WORDSPLITTER_H
#define WORDSPLITTER_H

#include "frame.h"
#include "frameprocessor.h"
#include <vector>
#include <limits>

using namespace std;

class WordSplitter
{
/*
 * Принимает массив фреймов, считает для каждого энтропию.
 * Возвращает массив массивов фреймов, в котором каждый массив -
 * слово.
 * Фреймы с тишиной удаляет
*/
public:
    WordSplitter(const FrameProcessor&, int);
    vector<vector<Frame>> getWords(int=0, int=0, double=-1) const;
private:
    double _countEntropy(const Frame&);
    vector<double> _entropyLevels;
    double _minEntropy = numeric_limits<double>::max(), _maxEntropy = numeric_limits<double>::min();
    int _frequency;
    FrameProcessor _data;
};

#endif // WORDSPLITTER_H
