#include "modelevaluation.h"

ModelEvaluation::ModelEvaluation(int argc, char* argv[]) {
    if (argc != 6) {
        std::cout << "Usage:\n" <<
        "Boosting-Sex-Identification-Performance " <<
        "input_filename (with data) output_filename (for results) " <<
        "testset_percent (from [0.1; 0.5]) n_classifiers (from [10; 1000]) " <<
        "classifiers_percent (from [0, 1])" << std::endl;
        exit(1);
    }
    input_filename_ = std::string(argv[1]);
    output_filename_ = std::string(argv[2]);
    testset_percent_ = atof(argv[3]);
    n_classifiers_ = atoi(argv[4]);
    classifiers_percent_ = atof(argv[5]);
    
    std::ifstream input_stream;
    input_stream.open(input_filename_.c_str(), std::ifstream::in | std::ifstream::binary);
    if (!input_stream.is_open()) {
        std::cout << "Error: opening file " << input_filename_ << std::endl;
        exit(1);
    }
    
    Data data(input_stream);
    input_stream.close();
    
    data.splitData(testset_percent_, train_data_, test_data_);
    data.clear();
}

void ModelEvaluation::evaluateModel() {
    StrongClassifier strong_classifier;
    AdaBoost adaboost;
    adaboost.adaBoost(train_data_, test_data_, n_classifiers_, classifiers_percent_,
                      strong_classifier, output_filename_);
}
