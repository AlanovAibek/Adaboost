#include "data.h"

Data::Data(std::ifstream& input_stream) {
    int width, height;
    char current_byte;
    
    if (!input_stream.get(current_byte)) {
        std::cout << "Error: reading width.";
        exit(1);
    }
    width = static_cast<int>(static_cast<u_char>(current_byte));
    if (!input_stream.get(current_byte)) {
        std::cout << "Error: reading height.";
        exit(1);
    }
    height = static_cast<int>(static_cast<u_char>(current_byte));
    
    sample_width_ = width;
    sample_height_ = height;
    
    int patch_size = width * height + 1;
    char* current_patch = new char[patch_size];
    
    while (input_stream.good()) {
        input_stream.read(current_patch, patch_size);
        if (patch_size == input_stream.gcount()) {
            addSample(current_patch, width, height);
        } else if (input_stream.eof()) {
            break;
        } else {
            std::cout << "Error: reading data file";
        }
    }
    
    delete[] current_patch;
}

void Data::addSample(const Sample& sample) {
    data_.push_back(sample);
}
void Data::addSample(const char* patch, int width, int height) {
    std::vector<u_char> image(width * height);
    
    for (int row = height - 1; row >= 0; --row) {
        for (int column = 0; column < width; ++column) {
            image[column + row * width] = static_cast<u_char>(*patch++);
        }
    }
    
    int label = (*patch == 1) ? 1 : 0;
    
    if (label == 1) {
        ++n_males_;
    } else {
        ++n_females_;
    }
    
    data_.push_back(Sample(Image(image, width, height), label));
}

void Data::splitData(double test_set_percent, Data& train_data, Data& test_data, bool shuffle) {
    int sample_size = getSampleSize();
    int test_sample_size = static_cast<int>(floor(sample_size * test_set_percent));
    int train_sample_size = sample_size - test_sample_size;
    
    train_data.sample_width_ = sample_width_;
    train_data.sample_height_ = sample_height_;
    test_data.sample_width_ = sample_width_;
    test_data.sample_height_ = sample_height_;
    
    if (shuffle) {
        std::random_shuffle(data_.begin(), data_.end());
    }
    train_data.setSampleSize(train_sample_size);
    for (int i = 0; i < train_sample_size; ++i) {
        train_data.addSample(data_[i]);
        if (data_[i].getLabel() == 1) {
            ++train_data.n_males_;
        } else {
            ++train_data.n_females_;
        }
    }
    for (int i = train_sample_size; i < sample_size; ++i) {
        test_data.addSample(data_[i]);
        if (data_[i].getLabel() == 1) {
            ++test_data.n_males_;
        } else {
            ++test_data.n_females_;
        }
    }
}
void Data::initializeWeights() {
    double male_weight = 0.5 / n_males_;
    double female_weight = 0.5 / n_females_;
    
    int sample_size = getSampleSize();
    for (int i = 0; i < sample_size; ++i) {
        if (data_[i].getLabel() == 1) {
            data_[i].setWeight(male_weight);
        } else {
            data_[i].setWeight(female_weight);
        }
    }
}
void Data::normalizeWeights() {
    double sum_weights = 0;
    int sample_size = getSampleSize();
    for (int i = 0; i < sample_size; ++i) {
        sum_weights += data_[i].getWeight();
    }
    for (int i = 0; i < sample_size; ++i) {
        data_[i].setWeight(data_[i].getWeight() / sum_weights);
    }
}
void Data::updateWeights(const WeakClassifier& classifier) {
    double beta = classifier.getBeta();
    int sample_size = getSampleSize();
    
    for (int i = 0; i < sample_size; ++i) {
        int predict = classifier.predict(data_[i].getImage());
        if (predict == data_[i].getLabel()) {
            data_[i].setWeight(data_[i].getWeight() * beta);
        }
    }
}

double Data::evaluateAccuracy(const StrongClassifier& classifier) const {
    double accuracy = 0;
    int sample_size = getSampleSize();
    for (int i = 0; i < sample_size; ++i) {
        int predict = classifier.predict(data_[i].getImage());
        if (data_[i].getLabel() == predict) {
            ++accuracy;
        }
    }
    return accuracy / sample_size;
}

int Data::getSampleSize() const {
    return static_cast<int>(data_.size());
}
int Data::getSampleWidth() const {
    return sample_width_;
}
int Data::getSampleHeight() const {
    return sample_height_;
}
const Sample& Data::getSample(int index) const {
    return data_[index];
}

void Data::setSampleSize(int sample_size) {
    data_.reserve(sample_size);
}

void Data::clear() {
    n_males_ = 0;
    n_females_ = 0;
    sample_width_ = 0;
    sample_height_ = 0;
    data_.clear();
}

