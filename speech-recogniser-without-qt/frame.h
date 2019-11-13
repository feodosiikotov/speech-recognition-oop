#ifndef FRAME_H
#define FRAME_H

#include <vector>
#include <iostream>
#include <stdint.h>

using namespace std;
/*
 * What frame will do.
 * Have uniq id
 * Store its data
 * Store its RMS value
 * Store its entrophy value
 *
 */

class Frame
{
public:
    Frame(vector<double> &data);
    ~Frame();
    int getId();
    double getRms();
    double getEntropy();
    vector<double> getData();

    /*
     * в FrameProcessor этого дибила снизу будет объявить нулем
     * чтобы id генерировалось автоматически
     *
     */

    static int count;

private:
    int id;
    double rms;
    double entropy;
    //double *mfcc;  у этого шизоида это было, но пока хз
    vector<double> data;
};

#endif // FRAME_H
