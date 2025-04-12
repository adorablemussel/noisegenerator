#include "image.h"

#include <iostream>
#include <fstream>

Color::Color(){
    r = 0.0f;
    g = 0.0f;
    b = 0.0f;
}

Color::Color(float r, float g, float b){
    this->r = r;
    this->g = g;
    this->b = b;
}

Color::~Color(){

}

Image::Image(int width, int height) {
    m_width = width;
    m_height = height;
    m_colors = std::vector<Color>(width * height);
}

Image::~Image() {

}

Color Image::GetColor(int x, int y) const {
    return m_colors[y * m_width + x];
}

void Image::SetColor(const Color& color, int x, int y) {
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

void Image::Export(const char* path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if(!f.is_open()){
        std::cout << "Failed to open the file" << std::endl;
        return;
    }

    unsigned char bmpPad[3] = {0, 0, 0};
    const int paddingAmount = ((4 - (m_width *3) % 4) % 4);

    const int fileHeaderSize = 14;
    const int infoHeaderSize = 40;
    const int fileSize = fileHeaderSize + infoHeaderSize + (m_width * m_height * 3) + (m_height * paddingAmount);

    unsigned char fileHeader[fileHeaderSize];
    // file type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    // file size
    fileHeader[2] = (unsigned char)(fileSize);
    fileHeader[3] = (unsigned char)(fileSize >> 8);
    fileHeader[4] = (unsigned char)(fileSize >> 16);
    fileHeader[5] = (unsigned char)(fileSize >> 24);
    // reserved 1
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    // reserved 2
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // offset to start of pixel data
    fileHeader[10] = (unsigned char)(fileHeaderSize + infoHeaderSize);
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char infoHeader[infoHeaderSize];
    // header size
    infoHeader[0] = (unsigned char)(infoHeaderSize);
    infoHeader[1] = 0;
    infoHeader[2] = 0;
    infoHeader[3] = 0;
    // image width
    infoHeader[4] = (unsigned char)(m_width);
    infoHeader[5] = (unsigned char)(m_width >> 8);
    infoHeader[6] = (unsigned char)(m_width >> 16);
    infoHeader[7] = (unsigned char)(m_width >> 24);
    // image height
    infoHeader[8] = (unsigned char)(m_height);
    infoHeader[9] = (unsigned char)(m_height >> 8);
    infoHeader[10] = (unsigned char)(m_height >> 16);
    infoHeader[11] = (unsigned char)(m_height >> 24);
    // planes
    infoHeader[12] = 1;
    infoHeader[13] = 0;
    // bits per pixel (RGB)
    infoHeader[14] = 24;
    infoHeader[15] = 0;
    // compression (0 = none)
    infoHeader[16] = 0;
    infoHeader[17] = 0;
    infoHeader[18] = 0;
    infoHeader[19] = 0;
    // image size (0 = no compression)
    infoHeader[20] = 0;
    infoHeader[21] = 0;
    infoHeader[22] = 0;
    infoHeader[23] = 0;
    // horizontal resolution (pixels per meter, 0 = default)
    infoHeader[24] = 0;
    infoHeader[25] = 0;
    infoHeader[26] = 0;
    infoHeader[27] = 0;
    // vertical resolution (pixels per meter, 0 = default)
    infoHeader[28] = 0;
    infoHeader[29] = 0;
    infoHeader[30] = 0;
    infoHeader[31] = 0;
    // total colors in palette (0 = default)
    infoHeader[32] = 0;
    infoHeader[33] = 0;
    infoHeader[34] = 0;
    infoHeader[35] = 0;
    // important colors (0 = all)
    infoHeader[36] = 0;
    infoHeader[37] = 0;
    infoHeader[38] = 0;
    infoHeader[39] = 0;

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(infoHeader), infoHeaderSize);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++){
            unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255);
            unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255);
            unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255);

            unsigned char color[] = {b, g, r};

            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }
    f.close();

    std::cout << "Image exported to " << path << std::endl;
    std::cout << "File size: " << fileSize << " bytes" << std::endl;
}