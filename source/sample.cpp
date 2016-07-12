#include "sample.h"

const Image& Sample::getImage() const {
    return image_;
}
int Sample::getLabel() const {
    return label_;
}
double Sample::getWeight() const {
    return weight_;
}

void Sample::setWeight(double weight) {
    weight_ = weight;
}