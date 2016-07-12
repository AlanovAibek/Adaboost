#ifndef ADABOOST_H_
#define ADABOOST_H_

#include <vector>
#include <fstream>
#include <string>

#include "weakclassifier.h"
#include "strongclassifier.h"
#include "data.h"
#include "randomgenerator.h"

class AdaBoost {
public:
    void adaBoost(Data& train_data, Data& test_data, int n_classifiers, double classifier_percent,
                  StrongClassifier& strong_classifier, std::string output_filename);
    WeakClassifier FindBestClassifier(const Data& train_data, double classifier_percent);
    WeakClassifier FindNonRandomBestClassifier(const Data& train_data);
    WeakClassifier FindRandomBestClassifier(const Data& train_data, double classifier_percent);
    void generateWeakClassifiers(int width, int height);
    
private:
    std::vector<WeakClassifier> weak_classifiers_;
};

#endif  // ADABOOST_H_