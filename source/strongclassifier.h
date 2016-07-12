#ifndef STRONGCLASSIFIER_H_
#define STRONGCLASSIFIER_H_

#include <vector>
#include <math.h>

#include "weakclassifier.h"

class StrongClassifier {
public:
    StrongClassifier() {}
    
    void addWeakClassifier(const WeakClassifier& classifier);
    int predict(const Image& image) const;
    
private:
    std::vector<WeakClassifier> weak_classifiers_;
};

#endif  // STRONGCLASSIFIER_H_