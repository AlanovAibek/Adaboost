#include "weakclassifier.h"

void WeakClassifier::generateClassifiers(std::vector<WeakClassifier>& classifiers, Pixel first_pixel, Pixel second_pixel) {
    for (int feature_type = 0; feature_type < Feature::kNumFeatureTypes; ++feature_type) {
        Feature feature;
        feature.setPixels(first_pixel, second_pixel);
        feature.setFeatureType(static_cast<Feature::FeatureType>(feature_type));
        classifiers.push_back(WeakClassifier(feature));
        
        Feature inverse_feature(feature);
        inverse_feature.setInverse(true);
        classifiers.push_back(WeakClassifier(feature));
    }
}

int WeakClassifier::predict(int first_pixel_value, int second_pixel_value) const {
    return feature_.computeFeature(first_pixel_value, second_pixel_value);
}
int WeakClassifier::predict(const Image& image) const {
    return feature_.computeFeature(image);
}

double WeakClassifier::getError() const {
    return error_;
}
double WeakClassifier::getBeta() const {
    return error_ / (1 - error_);
}
double WeakClassifier::getLogBeta() const {
    return (log(1 / getBeta()));
}
bool WeakClassifier::isTaken() const {
    return is_taken_;
}
const Feature& WeakClassifier::getFeature() const {
    return feature_;
}

void WeakClassifier::setError(double error) {
    error_ = error;
}
void WeakClassifier::took() {
    is_taken_ = true;
}
