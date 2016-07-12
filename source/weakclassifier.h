#ifndef WEAKCLASSIFIER_H_
#define WEAKCLASSIFIER_H_

#include <vector>
#include <math.h>

#include "feature.h"

class WeakClassifier {
public:
    WeakClassifier(Feature feature, double error=0, bool is_taken=false):
    feature_(feature), error_(error), is_taken_(is_taken) {}
    WeakClassifier(const WeakClassifier& weak_classifier): feature_(weak_classifier.feature_),
    error_(weak_classifier.error_), is_taken_(weak_classifier.is_taken_) {}
    
    static void generateClassifiers(std::vector<WeakClassifier>& classifiers, Pixel first_pixel, Pixel second_pixel);
    
    int predict(int first_pixel_value, int second_pixel_value) const;
    int predict(const Image& image) const;
    
    double getError() const;
    double getBeta() const;
    double getLogBeta() const;
    bool isTaken() const;
    const Feature& getFeature() const;
    
    void setError(double error);
    void took();
private:
    Feature feature_;
    double error_;
    bool is_taken_;
};

#endif  // WEAKCLASSIFIER_H_