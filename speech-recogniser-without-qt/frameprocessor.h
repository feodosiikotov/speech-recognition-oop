#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H
#include <iostream>
#include <vector>
#include <frame.h>
using namespace std;
/*
 * В конструкторе длину фрейма, нахлест и массив с числами инициализировать
 * method getFrames
 *
 */
class FrameProcessor
{
public:

    FrameProcessor(const int& frameWidth, const float& overlap, const vector<double> &data, int sampleRate);
    vector<Frame> getFrameArray();
private:

    vector<Frame> frameArray;

};

#endif // FRAMEPROCESSOR_H
