#include "frame.h"

Frame::Frame(vector<double> &data)
{
    this->id = count++;
    this->data = data;
}

int Frame::getId()
{
    return id;
}

vector<double> Frame::getData()
{
    return data;
}

double Frame::getRms(){
    return rms;
}

double Frame::getEntropy(){
    return entropy;
}
