#include <stdio.h>
#include <opencv2/opencv.hpp>
using namespace cv;

int main() {

    Mat img1 = imread("monkey.jpg");
    // 215 145 левый глаз
    // 273 142 правый глаз
    // 245 211 рот
    // 241 177 нос

    Mat img2 = imread("wolf.jpg");
    // 216 144 левый глаз
    // 276 141 правый глаз
    // 246 210 рот
    // 244 178 нос

    Point2f img1_coord[4] = { Point2f(215, 145), Point2f(273, 142), Point2f(245, 211), Point2f(241, 177)}; // координаты на первом изображении

    Point2f img2_coord[4] = { Point2f(216, 144), Point2f(276, 141), Point2f(211, 190), Point2f(385, 361)}; // координаты на втором изображении

    Point2f img1_coord_cur[4] = { Point2f(0, 0), Point2f(0, 0), Point2f(0, 0)}; // изменённые координаты на первом изображении

    Point2f img2_coord_cur[4] = { Point2f(0, 0), Point2f(0, 0), Point2f(0, 0)}; // изменённые координаты на втором изображении

    int steps = 1000; // итерации
    float weight = 1.0f / (float)steps; // вес

    for (int i = 0; i < steps; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int x = (img1_coord[j].x - img2_coord[j].x) * (-1);
            int y = (img1_coord[j].y - img2_coord[j].y) * (-1);

            float img1_move_x = ((float)x / steps) * (i + 1);
            float img1_move_y = ((float)y / steps) * (i + 1);

            float img2_move_x = x - img1_move_x;
            float img2_move_y = y - img1_move_y;

            img1_coord_cur[j].x = img1_coord[j].x + img1_move_x;
            img1_coord_cur[j].y = img1_coord[j].y + img1_move_y;

            img2_coord_cur[j].x = img2_coord[j].x + img2_move_x;
            img2_coord_cur[j].y = img2_coord[j].y + img2_move_y;

        }

        Mat img1_warp, img2_warp, img_warp;
        Mat trans1 = getAffineTransform(img1_coord, img1_coord_cur);
        Mat trans2 = getAffineTransform(img2_coord, img2_coord_cur);

        warpAffine(img1, img1_warp, trans1, img1.size(), BORDER_REPLICATE);
        warpAffine(img2, img2_warp, trans2, img2.size(), BORDER_REPLICATE);

        addWeighted(img1_warp, 1 - (weight * i), img2_warp, weight * (i + 1), 0, img_warp);
        imshow("", img_warp);
        waitKey(1);

    }
    waitKey(0);
    return 0;
}