#include "frame.h"

Frame::Frame(vector<double> &data)
{
    this->id = 1;//count++;
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

size_t Frame::size() const
{
    return data.size();
}

double Frame::at(size_t i) const
{
    return data.at(i);
}
