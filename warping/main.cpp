#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>

GLuint texture[1];
int WIDTH = 400;
int HEIGHT = 400;
const char* FILE_PATH = "/home/quatters/Coding/graphics/warping/moon.bmp";

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
};

typedef struct Image Image;

int ImageLoad(const char *filename, Image *image) {
    FILE *file;
    unsigned long size;
    unsigned long i;
    unsigned short int planes;
    unsigned short int bpp;
    char temp;
    if ((file = fopen(filename, "rb")) == nullptr){
        printf("File Not Found : %s\n", filename);
        return 0;
    }
    fseek(file, 18, SEEK_CUR);
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    image->sizeX = 64;
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    size = image->sizeX * image->sizeY * 3;
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);

        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;

    }
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;

    }
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    fseek(file, 24, SEEK_CUR);
    image->data = new char[size];
    if (image->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    if ((i = fread(image->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i = 0; i < size; i += 3) { 
        temp = image->data[i];
        image->data[i] = image->data[i + 2];
        image->data[i + 2] = temp;
    }
    return 1;
}

Image* loadTexture() {
    Image *image1;
    image1 = (Image*)malloc(sizeof(Image));
    if (image1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    if (!ImageLoad(FILE_PATH, image1)) {
        exit(1);
    }
    return image1;
}

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    Image *image1 = loadTexture();
    if (image1 == NULL){
        printf("Image was not returned from loadTexture\n");
        exit(0);
    }
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, image1->data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
}

void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glPushMatrix();
    int d = 1;

    glBegin(GL_QUADS);
    
    // glTexCoord2f(0, 0);
    // glVertex3f(-d, -d, d);
    
    // glTexCoord2f(1, 0);
    // glVertex3f(d, -d, d);

    // glTexCoord2f(1, 1);
    // glVertex3f(d, d, d);

    // glTexCoord2f(0, 1);
    // glVertex3f(-d, d, d);

    glTexCoord2f(0.2, 0);
    glVertex3f(-d, -d, d);
    
    glTexCoord2f(1, 0);
    glVertex3f(d, -d, d);

    glTexCoord2f(1, 0.6);
    glVertex3f(d, d, d);

    glTexCoord2f(0.2, 1);
    glVertex3f(-d, d, d);

    glEnd();

    glPopMatrix();
    glutSwapBuffers();
}

void myReshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();
    gluPerspective(60.0, 1.0 * (GLfloat)w / (GLfloat)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    gluLookAt(0.0, 0.0, -1.3, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("title");
    myInit();
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}