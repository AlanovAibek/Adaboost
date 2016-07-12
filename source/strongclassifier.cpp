#include "strongclassifier.h"

void StrongClassifier::addWeakClassifier(const WeakClassifier& classifier) {
    weak_classifiers_.push_back(classifier);
}
int StrongClassifier::predict(const Image& image) const {
    double sum = 0;
    int n_classifiers = static_cast<int>(weak_classifiers_.size());
    for (int i = 0; i < n_classifiers; ++i) {
        sum += (weak_classifiers_[i].predict(image) - 0.5) * weak_classifiers_[i].getLogBeta();
    }
    
    return sum >= 0 ? 1 : 0;
}