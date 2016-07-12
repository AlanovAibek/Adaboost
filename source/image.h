#ifndef IMAGE_H_
#define IMAGE_H_

#include <vector>

#include "pixel.h"

typedef unsigned char u_char;

class Image {
public:
    Image(const Image& image):
    image_(image.image_), width_(image.width_), height_(image.height_) {}
    Image(const std::vector<u_char>& image, int width, int height):
    image_(image), width_(width), height_(height) {}
    
    int getPixelValue(const Pixel& pixel) const;
private:
    std::vector<u_char> image_;
    int width_;
    int height_;
};


#endif  // IMAGE_H_