#include "adaboost.h"

void AdaBoost::adaBoost(Data& train_data, Data& test_data, int n_classifiers, double classifier_percent,
                        StrongClassifier& strong_classifier, std::string output_filename) {
    train_data.initializeWeights();
    generateWeakClassifiers(train_data.getSampleWidth(), train_data.getSampleHeight());
    
    std::ofstream output_stream(output_filename);
    
    for (int t = 0; t < n_classifiers; ++t) {
        train_data.normalizeWeights();
        WeakClassifier best_weak_classifier = FindBestClassifier(train_data, classifier_percent);
        
        train_data.updateWeights(best_weak_classifier);
        
        strong_classifier.addWeakClassifier(best_weak_classifier);
        
        output_stream << "Trained " << t + 1 << " weak classifiers." <<
        "\nAccuracy on train set:\t" << train_data.evaluateAccuracy(strong_classifier) <<
        "\nAccuracy on test set:\t" << test_data.evaluateAccuracy(strong_classifier) << '\n';
    }
    output_stream.close();
}

WeakClassifier AdaBoost::FindBestClassifier(const Data& train_data, double classifier_percent) {
    if (classifier_percent == 1.0) {
        return FindNonRandomBestClassifier(train_data);
    } else {
        return FindRandomBestClassifier(train_data, classifier_percent);
    }
}
WeakClassifier AdaBoost::FindNonRandomBestClassifier(const Data& train_data) {
    int n_classifiers = static_cast<int>(weak_classifiers_.size());
    int sample_size = train_data.getSampleSize();
    
    for (int sample_iter = 0; sample_iter < sample_size; ++sample_iter) {
        const Sample& sample = train_data.getSample(sample_iter);
        const Image& image = sample.getImage();
        int label = sample.getLabel();
        
        int first_pixel_value, second_pixel_value;
        int first_pixel_change_interval = train_data.getSampleWidth() * train_data.getSampleHeight() - 1;
        int second_pixel_change_interval = 2 * Feature::kNumFeatureTypes;
        for (int classifier_iter = 0; classifier_iter < n_classifiers; classifier_iter += 2) {
            if (classifier_iter % first_pixel_change_interval == 0) {
                const Pixel& first_pixel = weak_classifiers_[classifier_iter].getFeature().getFirstPixel();
                first_pixel_value = image.getPixelValue(first_pixel);
            }
            if (classifier_iter % second_pixel_change_interval == 0) {
                const Pixel& second_pixel = weak_classifiers_[classifier_iter].getFeature().getSecondPixel();
                second_pixel_value = image.getPixelValue(second_pixel);
            }
            int predict = weak_classifiers_[classifier_iter].predict(first_pixel_value, second_pixel_value);
            if (!weak_classifiers_[classifier_iter].isTaken() && label != predict) {
                double old_error = weak_classifiers_[classifier_iter].getError();
                weak_classifiers_[classifier_iter].setError(old_error + sample.getWeight());
            } else if (!weak_classifiers_[classifier_iter + 1].isTaken() && label == predict) {
                double old_error = weak_classifiers_[classifier_iter + 1].getError();
                weak_classifiers_[classifier_iter + 1].setError(old_error + sample.getWeight());
            }
        }
    }
    WeakClassifier best_classifier(Feature(), 1.0);
    int best_classifier_index = 0;
    for (int classifier_iter = 0; classifier_iter < n_classifiers; ++classifier_iter) {
        if (!weak_classifiers_[classifier_iter].isTaken()) {
            if (weak_classifiers_[classifier_iter].getError() < best_classifier.getError()) {
                best_classifier = weak_classifiers_[classifier_iter];
                best_classifier_index = classifier_iter;
            }
        }
        weak_classifiers_[classifier_iter].setError(0);
    }
    weak_classifiers_[best_classifier_index].took();
    return best_classifier;
}
WeakClassifier AdaBoost::FindRandomBestClassifier(const Data& train_data, double classifier_percent) {
    int n_classifiers = static_cast<int>(weak_classifiers_.size());
    int n_classifiers_part = static_cast<int>(floor(classifier_percent * n_classifiers));
    int sample_size = train_data.getSampleSize();
    
    RandomGenerator gen;
    WeakClassifier best_classifier(Feature(), 1.0);
    int best_classifier_index = 0;
    for (int classifier_iter = 0; classifier_iter < n_classifiers_part; ++classifier_iter) {
        int random_classifier = static_cast<int>(gen() % n_classifiers);
        if (weak_classifiers_[random_classifier].isTaken()) {
            --classifier_iter;
            continue;
        }
        for (int sample_iter = 0; sample_iter < sample_size; ++sample_iter) {
            const Sample& sample = train_data.getSample(sample_iter);
            const Image& image = sample.getImage();
            int label = sample.getLabel();
            
            int predict = weak_classifiers_[random_classifier].predict(image);
            
            if (label != predict) {
                double old_error = weak_classifiers_[random_classifier].getError();
                weak_classifiers_[random_classifier].setError(old_error + sample.getWeight());
            }
        }
        if (weak_classifiers_[random_classifier].getError() < best_classifier.getError()) {
            best_classifier = weak_classifiers_[random_classifier];
            best_classifier_index = classifier_iter;
        }
        weak_classifiers_[random_classifier].setError(0);
    }
    weak_classifiers_[best_classifier_index].took();
    return best_classifier;
}

void AdaBoost::generateWeakClassifiers(int width, int height) {
    for (int row = 0; row < height; ++row) {
        for (int column = 0; column < width; ++column) {
            Pixel first_pixel(row, column);
            for (int inner_row = 0; inner_row < height; ++inner_row) {
                for (int inner_column = 0; inner_column < width; ++inner_column) {
                    if ((row != inner_row) || (column != inner_column)) {
                        Pixel second_pixel(inner_row, inner_column);
                        WeakClassifier::generateClassifiers(weak_classifiers_, first_pixel, second_pixel);
                    }
                }
            }
        }
    }
}
