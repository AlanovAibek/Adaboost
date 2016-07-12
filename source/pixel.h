#ifndef PIXEL_H_
#define PIXEL_H_

class Pixel {
public:
    Pixel(int row=0, int column=0): row_(row), column_(column) {}
    
    int getRow() const;
    int getColumn() const;
private:
    int row_;
    int column_;
};

#endif  // PIXEL_H_