#include <iostream>
#include "CImg.h"

using namespace std;
using namespace cimg_library;

void* gamma_correction() {
  CImg<float> img = CImg<>("img/monkey.jpg").normalize(0,1);
  CImg<unsigned char> gamma_corrector(500, 200, 1, 3, 0);
  CImgList<unsigned char> visu(img * 255.0, gamma_corrector);
  CImgDisplay disp(visu, "Color correction");
  const int offset = 25, multiplier = 50;

  const unsigned char
    yellow[] = { 255, 255, 0 }, blue[] = { 0, 155, 255 }, blue2[] = { 0, 0, 255 },
    blue3[] = { 0, 0, 155 }, white[] = { 255, 255, 255 }, green[] = { 50, 128, 50 };

  for (double gamma = 1; !disp.is_closed() && !disp.is_keyQ() && !disp.is_keyESC(); ) {
    cimg_forXYZC(visu[0], x, y, z, k) visu[0](x, y, z, k) = 
        (unsigned char)(pow((double)img(x, y, z, k), 1.0 / gamma) * 256);

    visu[1].fill(20).draw_text(offset, 5, "Gamma = %.3g", white, 0, 1, 24, gamma);

    const int xb = (int)(offset + gamma * multiplier);
    visu[1].draw_rectangle(offset, 31, xb - 1, 39, blue);

    if (disp.button() 
        && disp.mouse_y() <= gamma_corrector.height()
        && disp.mouse_x() >= img.width() + offset 
        && disp.mouse_x() <= img.width() + gamma_corrector.width() - offset) {
        gamma = (disp.mouse_x() - img.width() - offset) / (double)multiplier;
    }
    disp.resize(disp, false).display(visu).wait();
  }
  return 0;
}

int main() {
    gamma_correction();

    return 0;
}