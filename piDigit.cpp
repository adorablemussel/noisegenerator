#include "piDigit.h"

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <string>
#include <iostream>


float piDigitCalculate(int x, int y, int width, int height) {
    int start = x + y * width;
    int count = 1;
    float colorValue = 0.0f;

    std::string url = "https://api.pi.delivery/v1/pi?start=" + std::to_string(start) + "&numberOfDigits=" + std::to_string(count);

    cpr::Response r = cpr::Get(cpr::Url{url});

    if (r.status_code == 200) {
        auto json = nlohmann::json::parse(r.text);
        std::string pi_digits = json["content"];
        std::cout << "Pixel (" << x << ", " << y << "): " << pi_digits << std::endl;
        colorValue = static_cast<float>(pi_digits[0] - '0') / 9.0f; // Normalize to [0, 1]
    } else {
        std::cerr << "Failed to fetch Pi digits. HTTP Status: " << r.status_code << std::endl;
    }

    return colorValue;
};