#include "frameprocessor.h"
#include <iostream>
#include <vector>
using namespace std;
// как передавать Sample Rate (возможно сделать дружественным)
FrameProcessor::FrameProcessor(const int &frameWidth, const float &overlap, const vector<double> &data, int sampleRate)
{
/*lets implement some logic here
 * wavdecoder.sampleRate -what amount of samples does consist in 1 second
 */

    int frameSize = int(sampleRate * frameWidth / 1000);
    vector<double> frameData;
    int i = 0;
    int j = 0;
    int shift = (int)(frameSize-frameSize*overlap);
    while (i < (data.size()-frameSize)) {
        j = i;
        while (j<frameSize) {
            frameData.push_back(data.at(j));
            j++;
        }
        frameArray.push_back(Frame(frameData));
        frameData.clear();
        i += shift;
    }
}

vector<Frame> FrameProcessor::getFrameArray()
{
    return frameArray;
}
