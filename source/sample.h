#ifndef SAMPLE_H_
#define SAMPLE_H_

#include "image.h"

class Sample {
public:
    Sample(Image image, int label): image_(image), label_(label) {}
    
    const Image& getImage() const;
    int getLabel() const;
    double getWeight() const;
    
    void setWeight(double weight);
private:
    Image image_;
    int label_;
    double weight_;
};

#endif  // SAMPLE_H_