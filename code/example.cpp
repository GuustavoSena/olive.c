#include <stdio.h>
#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <complex.h>
#include <assert.h>
#include "olive.cpp"

#define WIDTH 800
#define HEIGHT 600

#define COLS 8
#define ROWS 6
#define CELL_WIDTH (WIDTH/COLS)
#define CELL_HEIGHT (HEIGHT/ROWS)

#define RED_COLOR   0xFF2020FF
#define GREEN_COLOR 0xFF00FF00
#define BLUE_COLOR  0xFFFF2020

#define BACKGROUND_COLOR 0xFF202020
#define FOREGROUND_COLOR 0xFF2020FF

static uint32_t pixels[HEIGHT*WIDTH];

void swap_int(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

bool checker_example(void){
    olivec_fill(pixels, WIDTH, HEIGHT, BACKGROUND_COLOR);
    
    for (int y = 0; y < ROWS; ++y) {
        for (int x = 0; x < COLS; ++x) {
            uint32_t color = BACKGROUND_COLOR;
            if ((x + y)%2 == 0) {
                color = FOREGROUND_COLOR;
            }
            olivec_fill_rect(pixels, WIDTH, HEIGHT, x*CELL_WIDTH, y*CELL_HEIGHT, CELL_WIDTH, CELL_HEIGHT, color);
        }
    }


    const char *file_path = "checker.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err) {
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(errno));
        return false;
    }

    return true;
}

float lerpf(float a, float b, float t){
    return a + (b - a)*t;
}

bool circle_example(void){
    olivec_fill(pixels, WIDTH, HEIGHT, BACKGROUND_COLOR);

    for (int y = 0; y < ROWS; ++y){
        for (int x = 0; x < COLS; ++x) {
            float u = (float)x/COLS;
            float v = (float)y/ROWS;
            float t = (u + v)/2;

            size_t radius = CELL_WIDTH;
            if (CELL_HEIGHT < radius) radius = CELL_HEIGHT;

            olivec_fill_circle(pixels, WIDTH, HEIGHT, x*CELL_WIDTH + CELL_WIDTH/2, y*CELL_HEIGHT + CELL_HEIGHT/2, (size_t) lerpf(radius/4, radius/2, t), FOREGROUND_COLOR);
        }
    }   


    const char *file_path = "circle.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err) {
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(errno));
        return false;
    }

    return true;
}

bool lines_example(void){
    olivec_fill(pixels, WIDTH, HEIGHT, BACKGROUND_COLOR);

    olivec_draw_line(pixels, WIDTH, HEIGHT,
                 0, 0, WIDTH, HEIGHT,
                 0xFF2020FF);

    olivec_draw_line(pixels, WIDTH, HEIGHT,
                 WIDTH, 0, 0, HEIGHT,
                 0xFF2020FF);

    olivec_draw_line(pixels, WIDTH, HEIGHT,
                 0, 0, WIDTH/4, HEIGHT,
                 0xFF20FF20);

    olivec_draw_line(pixels, WIDTH, HEIGHT,
                 WIDTH/4, 0, 0, HEIGHT,
                 0xFF20FF20);

    olivec_draw_line(pixels, WIDTH, HEIGHT,
                 WIDTH, 0, WIDTH/4*3, HEIGHT,
                 0xFF20FF20);

    olivec_draw_line(pixels, WIDTH, HEIGHT,
                 WIDTH/4*3, 0, WIDTH, HEIGHT,
                 0xFF20FF20);

    olivec_draw_line(pixels, WIDTH, HEIGHT,
                 0, HEIGHT/2, WIDTH, HEIGHT/2,
                 0xFFFF3030);

    olivec_draw_line(pixels, WIDTH, HEIGHT,
                 WIDTH/2, 0, WIDTH/2, HEIGHT,
                 0xFFFF3030);


    const char *file_path = "lines.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err) {
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(errno));
        return false;
    }

    return true;
}

bool triangle_example(){
    olivec_fill(pixels, WIDTH, HEIGHT, BACKGROUND_COLOR);

    int radius = 5;

    {
        int x1 = WIDTH/2, y1 = HEIGHT/8;
        int x2 = WIDTH/8, y2 = HEIGHT/2;
        int x3 = WIDTH*7/8, y3 = HEIGHT*7/8;
        olivec_fill_triangle(pixels, WIDTH, HEIGHT, x1, y1, x2, y2, x3, y3, RED_COLOR);
    }

   {
        int x1 = WIDTH/2, y1 = HEIGHT*2/8;
        int x2 = WIDTH*2/8, y2 = HEIGHT/2;
        int x3 = WIDTH*6/8, y3 = HEIGHT/2;
        olivec_fill_triangle(pixels, WIDTH, HEIGHT, x1, y1, x2, y2, x3, y3, GREEN_COLOR);
    }

    {
        int x1 = WIDTH/8,   y1 = HEIGHT/8;
        int x2 = WIDTH/8,   y2 = HEIGHT*3/8;
        int x3 = WIDTH*3/8, y3 = HEIGHT*3/8;
        olivec_fill_triangle(pixels, WIDTH, HEIGHT, x1, y1, x2, y2, x3, y3, BLUE_COLOR);
    }

    const char *file_path = "triangle.ppm";
    Errno err = olivec_save_to_ppm_file(pixels, WIDTH, HEIGHT, file_path);
    if (err) {
        fprintf(stderr, "ERROR: could not save file %s: %s\n", file_path, strerror(errno));
        return false;
    }

    return true;
}


int main(void){
    if(!checker_example()) return -1;
    if(!circle_example()) return -1;
    if(!lines_example()) return -1;
    if(!triangle_example()) return -1;
    return 0;
}