#include "wavdecoder.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <string.h>
#include <algorithm>

using namespace std;

WavDecoder::WavDecoder()
{

}

WavDecoder::WavDecoder(const string& filename)
{
    _data = vector<double>();
    _readFromFile(filename);
}

void WavDecoder::_readFromFile(const string& fileName)
{
    ifstream fin;
    //Открываем в бинарном формате
    fin.open(fileName, ios::binary);
    if (fin.fail()) {
        return;
    }
    //Создаем заголовок
    _header = new _Header(fin);
    //Проверка заголовка
    if (!(_header->check())){
        return;
    }
    _readData(fin);
    _hasData = true;
}

WavDecoder::_Header::_Header(ifstream& fin)
{
    fin.read(chunkId, 4);
    fin.read(chunkSize, 4);
    fin.read(format, 4);
    fin.read(subChunk1Id, 4);
    fin.read(subChunk1Size, 4);
    fin.read(reinterpret_cast<char*>(&audioFormat), 2);
    fin.read(reinterpret_cast<char*>(&numChannels), 2);
    fin.read(sampleRate, 4);
    fin.read(byteRate, 4);
    fin.read(blockAlign, 2);
    fin.read(reinterpret_cast<char*>(&bitsPerSample), 2);
    fin.read(subChunk2Id, 4);
    fin.read(subChunk2Size, 4);
}

bool WavDecoder::_Header::check() const
{
    if (_compare_strings(chunkId, "RIFF", 4)){
        return false;
    }
    if (_compare_strings(format, "WAVE", 4)){
        return false;
    }
    char tmp[4] = {'f', 'm', 't', 32};
    if (_compare_strings(subChunk1Id, tmp, 4)){
        return false;
    }
    //Поддерживается только PCM
    if (audioFormat != 1)
    {
        return false;
    }
    //Пока что только одноканальное аудио
    if (numChannels != 1){
        return false;
    }
    if (strcmp(subChunk2Id, "data")){
        return false;
    }
    //Надо будет допилить и остальные
    if (bitsPerSample != 16){
        return false;
    }
    return true;
}

void WavDecoder::_readData(ifstream & fin)
{
    uint8_t tmp_val, max_val = 0, min_val = 0;
    vector<uint8_t> raw_data;
    while (!fin.eof()){
        fin.read((char*)(&tmp_val), 2);
        if (max_val > tmp_val){
            max_val = tmp_val;
        }
        if (min_val < tmp_val){
            min_val = tmp_val;
        }
        raw_data.push_back(tmp_val);
    }
    fin.close();
    uint8_t normalization_coef = max(max_val, (uint8_t)(-min_val));
    for (auto& e: raw_data){
      _data.push_back(static_cast<double>(e)/normalization_coef);
    }
}

WavDecoder::~WavDecoder()
{
    delete _header;
}

bool WavDecoder::hasData() const
{
    return _hasData;
}

vector<double> WavDecoder::getData() const
{
    return _data;
}

bool WavDecoder::_Header::_compare_strings(const char first[], const char second[], int size) const
{
    for (int i=0; i<size; i++){
        if (first[i] != second[i])
            return false;
    }
    return true;
}
