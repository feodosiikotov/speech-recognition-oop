#ifndef WAVDECODER_H
#define WAVDECODER_H
#include <string>
#include <vector>

using namespace std;

class WavDecoder
{
public:
    WavDecoder();
    WavDecoder(const string&);
    void read();
    bool hasData() const;
    ~WavDecoder();
    vector<double> getData() const;
private:
    struct _Header
    {
        _Header(ifstream&);
        bool check() const;
        bool _compare_strings(const char[], const char[], int) const;
        char chunkId[4];
        char chunkSize[4];
        char format[4];
        char subChunk1Id[4];
        char subChunk1Size[4];
        uint8_t audioFormat;
        uint8_t numChannels;
        char sampleRate[4];
        char byteRate[4];
        char blockAlign[2];
        uint8_t bitsPerSample;
        char subChunk2Id[4];
        char subChunk2Size[4];

int int int = ss;
    };
    void _readFromFile(const string&);
    void _readData(ifstream&);
    bool _hasData = false;
    vector<double> _data;
    _Header* _header;
};

#endif // WAVDECODER_H
