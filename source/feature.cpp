#include "feature.h"

int Feature::computeFeature(const Image& image) const {
    int first_pixel_value = image.getPixelValue(first_pixel_);
    int second_pixel_value = image.getPixelValue(second_pixel_);
    
    return computeFeature(first_pixel_value, second_pixel_value);
}
int Feature::computeFeature(int first_pixel_value, int second_pixel_value) const {
    int feature_value = 0;
    int difference = first_pixel_value - second_pixel_value;
    
    switch (feature_type_) {
        case greater:
            if (difference > 0) {
                feature_value = 1;
            }
            break;
        case within5:
            if (abs(difference) <= 5) {
                feature_value = 1;
            }
            break;
        case within10:
            if (abs(difference) <= 10) {
                feature_value = 1;
            }
            break;
        case within25:
            if (abs(difference) <= 25) {
                feature_value = 1;
            }
            break;
        case within50:
            if (abs(difference) <= 50) {
                feature_value = 1;
            }
            break;
        default:
            break;
    }
    
    return is_inverse_ ? 1 - feature_value : feature_value;
}

const Pixel& Feature::getFirstPixel() const {
    return first_pixel_;
}
const Pixel& Feature::getSecondPixel() const {
    return second_pixel_;
}

void Feature::setPixels(Pixel first_pixel, Pixel second_pixel) {
    first_pixel_ = first_pixel;
    second_pixel_ = second_pixel;
}
void Feature::setFeatureType(FeatureType feature_type) {
    feature_type_ = feature_type;
}
void Feature::setInverse(bool is_inverse) {
    is_inverse_ = is_inverse;
}

