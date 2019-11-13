#include "wordsplitter.h"
#include "math.h"

WordSplitter::WordSplitter(const FrameProcessor& processor, int frequency) : _entropyLevels(), _frequency(frequency),
    _data(processor)
{
    size_t processor_size = processor.size();
    for (int i = 0; i < processor_size; i++){
        Frame cur = processor.at(i);
        double entropy = _countEntropy(cur);
        _entropyLevels.push_back(entropy);
        if (entropy > _maxEntropy)
            _maxEntropy = entropy;
        if (entropy < _minEntropy)
            _minEntropy = entropy;
    }
}

double WordSplitter::_countEntropy(const Frame & frame)
{
    double entropy = 0;
    vector<double> probabilites(_frequency, 0);
    size_t frame_size = frame.size();
    for (size_t i = 0; i < frame_size; i++){
        size_t idx = floor(((frame.at(i) + 1)/2)*_frequency);
        if (idx >= _frequency)
            idx = _frequency - 1;
        probabilites.at(idx) += 1/frame_size;
    }
    for (auto el: probabilites){
        if (el > 0){
            entropy -= el*log2(el);
        }
    }
    return entropy;
}


vector<vector<Frame>> WordSplitter::getWords(int min_distance, int min_length, double threshold) const
{
    if (threshold == -1){
        threshold = (_minEntropy + _maxEntropy)/1.;
    }
    vector<char> is_silence;
    for (auto el: _entropyLevels){
        is_silence.push_back(el < threshold);
    }
    int i = 0;
    for (; !is_silence[i]; i++);
    vector<Frame> cur_word, cur_silence;
    vector<vector<Frame>> wordsList;
    bool mode = true;
    while (i < is_silence.size()){
        if (mode and is_silence[i]){
            cur_word.push_back(_data.at(i));
        }
        if (not is_silence[i]){
            mode = false;
            cur_silence.push_back(_data.at(i));
        }
        if (not mode and is_silence.at(i)){
            if (cur_silence.size() < min_distance){
                for (auto el: cur_silence){
                    cur_word.push_back(el);
                }
                cur_silence.clear();
                mode = true;
                cur_word.push_back(_data.at(i));
            }
            else if (cur_word.size() < min_length){
                mode = true;
                cur_word.clear();
                cur_silence.clear();
                cur_word.push_back(_data.at(i));
            }
            else if (cur_silence.size() > min_distance and cur_word.size() > min_length){
                wordsList.push_back(cur_word);
                mode = true;
                cur_word.clear();
                cur_silence.clear();
                cur_word.push_back(_data.at(i));
            }

        }
    }
    if (cur_silence.size() > min_distance and cur_word.size() > min_length){
        wordsList.push_back(cur_word);
    }
    return wordsList;
}
