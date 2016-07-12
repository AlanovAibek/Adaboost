#ifndef FEATURE_H_
#define FEATURE_H_

#include <math.h>
#include <stdlib.h>

#include "pixel.h"
#include "image.h"

class Feature {
public:
    static const int kNumFeatureTypes = 5;
    enum FeatureType {
        greater,
        within5,
        within10,
        within25,
        within50,
    };
    
    Feature(): first_pixel_(Pixel()), second_pixel_(Pixel()), is_inverse_(false) {}
    Feature(const Feature& feature): feature_type_(feature.feature_type_),
    first_pixel_(feature.first_pixel_), second_pixel_(feature.second_pixel_),
    is_inverse_(feature.is_inverse_) {}
    
    int computeFeature(const Image& image) const;
    int computeFeature(int first_pixel_value, int second_pixel_value) const;
    
    const Pixel& getFirstPixel() const;
    const Pixel& getSecondPixel() const;
    
    void setPixels(Pixel first_pixel, Pixel second_pixel);
    void setFeatureType(FeatureType feature_type);
    void setInverse(bool is_inverse);
private:
    FeatureType feature_type_;
    Pixel first_pixel_;
    Pixel second_pixel_;
    bool is_inverse_;
};

#endif  // FEATURE_H_