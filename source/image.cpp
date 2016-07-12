#include "image.h"

int Image::getPixelValue(const Pixel& pixel) const {
    int row = pixel.getRow();
    int column = pixel.getColumn();
    return static_cast<int>(image_[column + width_ * row]);
}