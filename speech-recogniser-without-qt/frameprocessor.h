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
    FrameProcessor(vector<Frame>);
    vector<Frame> getFrameArray();
    size_t size() const;
    Frame at(size_t) const;
private:

    vector<Frame> frameArray;
};

#endif // FRAMEPROCESSOR_H
