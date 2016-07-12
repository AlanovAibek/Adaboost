#ifndef DATA_H_
#define DATA_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <math.h>

#include "sample.h"
#include "weakclassifier.h"
#include "strongclassifier.h"

class Data {
public:
    Data(): data_(std::vector<Sample>()), n_males_(0), n_females_(0) {}
    Data(std::ifstream& input_stream);
    
    void addSample(const Sample& sample);
    void addSample(const char* patch, int width, int height);
    
    void splitData(double test_set_percent, Data& train_data, Data& test_data, bool shuffle=true);
    
    void initializeWeights();
    void normalizeWeights();
    void updateWeights(const WeakClassifier& classifier);
    double evaluateAccuracy(const StrongClassifier& classifier) const;
    
    int getSampleSize() const;
    int getSampleWidth() const;
    int getSampleHeight() const;
    const Sample& getSample(int index) const;
    
    void setSampleSize(int sample_size);
    
    void clear();
    
private:
    std::vector<Sample> data_;
    u_char sample_width_;
    u_char sample_height_;
    int n_males_;
    int n_females_;
};

#endif  // DATA_H_