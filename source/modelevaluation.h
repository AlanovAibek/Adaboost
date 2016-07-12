#ifndef MODELEVALUATION_H_
#define MODELEVALUATION_H_

#include "adaboost.h"

#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>

class ModelEvaluation {
public:
    ModelEvaluation(int argc, char* argv[]);
    void evaluateModel();
    
private:
    Data train_data_;
    Data test_data_;
    
    std::string input_filename_;
    std::string output_filename_;
    int n_classifiers_;
    double testset_percent_;
    double classifiers_percent_;
};

#endif  // MODELEVALUATION_H_