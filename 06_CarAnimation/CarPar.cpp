#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <thread>
#include <omp.h>
#include <algorithm>

#define RGB_COMPONENT_COLOR 255
#define NUM_FRAMES 50
#define SAVE_EVERY 1

static const auto THREADS = std::thread::hardware_concurrency();

struct PPMPixel {
  int red;
  int green;
  int blue;
};

typedef struct {
  int x, y, all;
  PPMPixel *data;
} PPMImage;

void readPPM(const char *filename, PPMImage &img){
    std::ifstream file(filename);
    if (file) {
        std::string s;
        int rgb_comp_color;
        file >> s;
        if (s != "P3") {
            std::cout << "error in format" << std::endl;
            exit(9);
        }
        file >> img.x >> img.y;
        file >> rgb_comp_color;
        img.all = img.x * img.y;
        std::cout << s << std::endl;
        std::cout << "x=" << img.x << " y=" << img.y << " all=" << img.all
                  << std::endl;
        img.data = new PPMPixel[img.all];
        for (int i = 0; i < img.all; i++) {
            file >> img.data[i].red >> img.data[i].green >> img.data[i].blue;
        }
    } else {
        std::cout << "the file:" << filename << "was not found" << std::endl;
    }
    file.close();
}

void writePPM(const char *filename, PPMImage &img) {
    std::ofstream file(filename, std::ofstream::out);
    file << "P3" << std::endl;
    file << img.x << " " << img.y << " " << std::endl;
    file << RGB_COMPONENT_COLOR << std::endl;

    for (int i = 0; i < img.all; i++) {
        file << img.data[i].red << " " << img.data[i].green << " "
             << img.data[i].blue << (((i + 1) % img.x == 0) ? "\n" : " ");
    }
    file.close();
}

int main(int argc, char *argv[]) {
    PPMImage image;
    readPPM("car.ppm", image);
 
    double total_start = omp_get_wtime();
 
    PPMPixel *new_data = new PPMPixel[image.all];

    for (int frame = 0; frame < NUM_FRAMES; frame++) {
 
        
        #pragma omp parallel for collapse(2) //the collapse is for parallelizing both loops
        for (int i = 0; i < image.y; i++) {
            for (int j = 0; j < image.x; j++) {
                int old_idx = i * image.x + j;
                int new_col = (j + 1) % image.x;  // wrapping last col to first
                int new_idx = i * image.x + new_col;
                new_data[new_idx] = image.data[old_idx];
            }
        }
 
        // swapping pointers in O(1) rather than copying pixels
        std::swap(image.data, new_data);
 
    
        if (frame % SAVE_EVERY == 0) {
            char filename[50];
            sprintf(filename, "frame_%03d.ppm", frame);
            writePPM(filename, image);
            std::cout << "Saved frame " << frame << std::endl;
        }
    }

    delete[] new_data;
    delete[] image.data;
 
    double total_end = omp_get_wtime();
    printf("\nTotal time (%d frames, save every %d): %.4f seconds\n", NUM_FRAMES, SAVE_EVERY, total_end - total_start);
    
 
    return 0;
}