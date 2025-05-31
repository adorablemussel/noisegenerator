#include "inc/image.h"
#include "inc/piDigit.h"

#include <iostream>
#include <cstdint>
#include <limits>
#include <vector>
#include <string>
#include <filesystem>

// 8k resolution, 7680x4320, maximum number of pixels is 33,177,600
#define MAX_WIDTH 7680
#define MAX_HEIGHT 4320

void dimensionAssign(int16_t& value, int maxDimension){
    do{
        std::cout << "Enter the value: ";
        std::cin >> value;
        if (value <= 0 || value >  maxDimension || std::cin.fail() || value < std::numeric_limits<int16_t>::min() || value > std::numeric_limits<int16_t>::max()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "\nInvalid input. You probably entered:\n - a non-positive number.\n - a value greater than " << maxDimension << ".\n - a text value.\nPlease try again.\n" << std::endl;
            continue;
        }
        break;
    }
    while (true);
}

int main() {
    int16_t width, height;

    std::cout << "WIDTH (in pixels)" << std::endl;
    dimensionAssign(width, MAX_WIDTH);
    std::cout << std::endl;
    std::cout << "HEIGHT (in pixels)" << std::endl;
    dimensionAssign(height, MAX_HEIGHT);
    std::cout << std::endl;

    std::cout << "Provided resolution: " << width << "x" << height << std::endl;

    int32_t pixelsNumber = static_cast<int32_t>(width) * height;
    std::cout << "Number of pixels to be computed: " << pixelsNumber << std:: endl;

    Image image(width, height);
    for (int y = 0; y < height; y++) { 
        for (int x = 0; x < width; x++) {
            float piValue = normalizedPiDigitCalculate(x, y, width);
            image.SetColor(Color(piValue, piValue, piValue), x, y);
        }
    }

    std::filesystem::path outDir;
    if (std::filesystem::exists("../out") && std::filesystem::is_directory("../out")) {
        outDir = "../out";
    } else {
        outDir = "out";
        if (!std::filesystem::exists(outDir)) {
            std::filesystem::create_directory(outDir);
        }
    }

    std::string filename = (outDir / ("output_" + std::to_string(width) + "x" + std::to_string(height) + ".bmp")).string();
    image.Export(filename.c_str());

    return 0;
}