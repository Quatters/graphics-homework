#include <iostream>
#include <vector>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

int main() {
    CImg<double> image("img/monkey.jpg");
    int w = image.width(), h = image.height(), ch = image.spectrum();
    double r, g, b;

    for (int y = 0; y < h; y++) {
       for (int x = 0; x < w; x++) {
           r = image(x, y, 0, 0);
           g = image(x, y, 0, 1);
           b = image(x, y, 0, 2);
          
           image(x, y, 0, 0) = 0.299 * r + 0.587 * g + 0.114 * b;
           image(x, y, 0, 1) = 0.5 * r - 0.4187 * g - 0.0813 * b + 128;
           image(x, y, 0, 2) = 0.1687 * r - 0.3313 * g + 0.5 * b + 128;
       }
    }

    // image.RGBtoYCbCr();
    image.display();

    return 0;
}