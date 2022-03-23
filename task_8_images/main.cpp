#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

const string BASE_INPUT = "images/source/";
const string BASE_OUTPUT = "images/output/";
const string FORMAT = ".ppm";

struct Size {
    int width;
    int height;
};

Size write_header(ifstream &image, ofstream &new_image)
{
    string type = "", width = "", height = "", colors = "";

    image >> type;
    image >> width;
    image >> height;
    image >> colors;

    new_image << type << '\n';
    new_image << width << ' ';
    new_image << height << '\n';
    new_image << colors << '\n';

    return {stoi(width), stoi(height)};
}

void threshold128(string image_name) {
    ifstream image;
    ofstream new_image;

    image.open(BASE_INPUT + image_name + FORMAT);
    new_image.open(BASE_OUTPUT + image_name + "_threshold_128" + FORMAT);

    write_header(image, new_image);

    string temp = "";
    int rgb[3];

    while (!image.eof()) {
        for (int i = 0; i < 3; i++) {
            image >> temp;
            rgb[i] = stoi(temp);

            if (rgb[i] > 127) new_image << 255;
            else new_image << 0;

            new_image << ' ';
        }
    }

    image.close();
    new_image.close();
}

void random_threshold(string image_name) {
    ifstream image;
    ofstream new_image;

    image.open(BASE_INPUT + image_name + FORMAT);
    new_image.open(BASE_OUTPUT + image_name + "_random_threshold" + FORMAT);

    write_header(image, new_image);

    string temp = "";
    int rgb[3];

    while (!image.eof()) {
        for (int i = 0; i < 3; i++) {
            image >> temp;
            rgb[i] = stoi(temp);

            if (rgb[i] > rand() % 255) new_image << 255;
            else new_image << 0;

            new_image << ' ';
        }
    }

    image.close();
    new_image.close();
}

void dither2x2(string image_name) {
    ifstream image;
    ofstream new_image;

    image.open(BASE_INPUT + image_name + FORMAT);
    new_image.open(BASE_OUTPUT + image_name + "_dither_2x2" + FORMAT);

    Size size = write_header(image, new_image);

    string temp = "";
    int rgb[3];
    int x = 0, y = 0;

    int M[2][2] = {
        {0, 2},
        {3, 1}
    };

    while (!image.eof()) {
        for (int i = 0; i < 3; i++) {
            image >> temp;
            rgb[i] = stoi(temp);

            if (rgb[i] * 5 / 256 > M[y % 2][x % 2]) {
                new_image << 255;
            }
            else {
                new_image << 0;
            }
            new_image << ' ';
        }
        x++;
        if (x >= size.width) {
            x = 0;
            y++;
        }
    }

    image.close();
    new_image.close();
}

void dither16x16(string image_name) {
    ifstream image;
    ofstream new_image;

    image.open(BASE_INPUT + image_name + FORMAT);
    new_image.open(BASE_OUTPUT + image_name + "_dither_16x16" + FORMAT);

    Size size = write_header(image, new_image);

    string temp = "";
    int rgb[3];
    int x = 0, y = 0;

    int M[16][16] = {
        {     0, 191,  48, 239,  12, 203,  60, 251,   3, 194,  51, 242,  15, 206,  63, 254  }, 
        {   127,  64, 175, 112, 139,  76, 187, 124, 130,  67, 178, 115, 142,  79, 190, 127  },
        {    32, 223,  16, 207,  44, 235,  28, 219,  35, 226,  19, 210,  47, 238,  31, 222  },
        {   159,  96, 143,  80, 171, 108, 155,  92, 162,  99, 146,  83, 174, 111, 158,  95  },
        {     8, 199,  56, 247,   4, 195,  52, 243,  11, 202,  59, 250,   7, 198,  55, 246  },
        {   135,  72, 183, 120, 131,  68, 179, 116, 138,  75, 186, 123, 134,  71, 182, 119  },
        {    40, 231,  24, 215,  36, 227,  20, 211,  43, 234,  27, 218,  39, 230,  23, 214  },
        {   167, 104, 151,  88, 163, 100, 147,  84, 170, 107, 154,  91, 166, 103, 150,  87  },
        {     2, 193,  50, 241,  14, 205,  62, 253,   1, 192,  49, 240,  13, 204,  61, 252  },
        {   129,  66, 177, 114, 141,  78, 189, 126, 128,  65, 176, 113, 140,  77, 188, 125  },
        {    34, 225,  18, 209,  46, 237,  30, 221,  33, 224,  17, 208,  45, 236,  29, 220  },
        {   161,  98, 145,  82, 173, 110, 157,  94, 160,  97, 144,  81, 172, 109, 156,  93  },
        {    10, 201,  58, 249,   6, 197,  54, 245,   9, 200,  57, 248,   5, 196,  53, 244  },
        {   137,  74, 185, 122, 133,  70, 181, 118, 136,  73, 184, 121, 132,  69, 180, 117  },
        {    42, 233,  26, 217,  38, 229,  22, 213,  41, 232,  25, 216,  37, 228,  21, 212  },
        {   169, 106, 153,  90, 165, 102, 149,  86, 168, 105, 152,  89, 164, 101, 148,  85  }
    };

    while (!image.eof()) {
        for (int i = 0; i < 3; i++) {
            image >> temp;
            rgb[i] = stoi(temp);

            if (rgb[i] > M[y % 16][x % 16]) {
                new_image << 255;
            }
            else {
                new_image << 0;
            }
            new_image << ' ';
        }
        x++;
        if (x >= size.width) {
            x = 0;
            y++;
        }
    }

    image.close();
    new_image.close();
}

int truncate(int value) {
    if (value > 255) return 255;
    else if (value < 0) return 0;
    else return value;
}

void apply_error_diffusion(int** &pixels, Size size) {
    int error = 0;
    int actual_color = 0;
    for (int j = 0; j < size.height; j++) {
        for (int i = 0; i < size.width; i++) {
            actual_color = pixels[i][j];
            if (actual_color > 127) pixels[i][j] = 255;
            else pixels[i][j] = 0;

            error = actual_color - pixels[i][j];

            if (i + 1 < size.width)
                pixels[i + 1][j]     = pixels[i + 1][j]     + error * 7 / 16;

            if (i - 1 > 0 && j + 1 < size.height)
                pixels[i - 1][j + 1] = pixels[i - 1][j + 1] + error * 3 / 16;

            if (j + 1 < size.height)
                pixels[i][j + 1]     = pixels[i][j + 1]     + error * 5 / 16;

            if (i + 1 < size.width && j + 1 < size.height)
                pixels[i + 1][j + 1] = pixels[i + 1][j + 1] + error * 1 / 16;
        }
    }
}

void error_diffusion(string image_name) {
    ifstream image;
    ofstream new_image;

    image.open(BASE_INPUT + image_name + FORMAT);
    new_image.open(BASE_OUTPUT + image_name + "_error_diffusion" + FORMAT);

    Size size = write_header(image, new_image);

    string temp = "";
    int rgb[3];
    int x = 0, y = 0;

    int** r = new int*[size.width];
      for(int i = 0; i < size.width; i++)
          r[i] = new int[size.height];

    int** g = new int*[size.width];
      for(int i = 0; i < size.width; i++)
          g[i] = new int[size.height];

    int** b = new int*[size.width];
      for(int i = 0; i < size.width; i++)
          b[i] = new int[size.height];

    while (!image.eof()) {
        image >> temp;
        r[x][y] = stoi(temp);

        image >> temp;
        g[x][y] = stoi(temp);

        image >> temp;
        b[x][y] = stoi(temp);

        x++;
        if (x >= size.width) {
            x = 0;
            y++;
        }
    }

    apply_error_diffusion(r, size);
    apply_error_diffusion(g, size);
    apply_error_diffusion(b, size);

    for (int j = 0; j < size.height; j++) {
        for (int i = 0; i < size.width; i++) {
            new_image << r[i][j] << ' ';
            new_image << g[i][j] << ' ';
            new_image << b[i][j] << ' ';
        }
    }

    for(int i = 0; i < size.width; i++)
        delete [] r[i];
    delete [] r;

    for(int i = 0; i < size.width; i++)
        delete [] g[i];
    delete [] g;

    for(int i = 0; i < size.width; i++)
        delete [] b[i];
    delete [] b;

    image.close();
    new_image.close();
}

int main(int argc, char** argv) {
    srand(time(0));

    string images[] = {"apollo", "bird", "landscape", "monument", "skylight"};

    for (auto &&image : images)
    {
        threshold128(image);
        random_threshold(image);
        dither2x2(image);
        dither16x16(image);
        error_diffusion(image);
    }

    return 0;
}
