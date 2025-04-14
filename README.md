# Noise Generator

**Noise Generator** is a tool that creates grayscale noise textures based on the digits of mathematical constants, such as **π (Pi)**.

## 🧠 How It Works

The core idea is to extract digits after the decimal point of a number and use each digit to determine the brightness of a pixel in a grayscale image.

Each digit from 0 to 9 maps linearly to a brightness level:

<div align="center">
  
| Digit | Brightness | 8-bit RGB Value | Normalized RGB Value |
|-------|------------|------------------|-----------------------|
| 0     | 0%         | (0, 0, 0)        | (0.0, 0.0, 0.0)       |
| 1     | ~11%       | (28, 28, 28)     | (0.1, 0.1, 0.1)       |
| 2     | ~22%       | (57, 57, 57)     | (0.2, 0.2, 0.2)       |
| ...   | ...        | ...              | ...                   |
| 9     | 100%       | (255, 255, 255)  | (1.0, 1.0, 1.0)       |
  
</div>

After processing the digits, the result is saved as a `.bmp` image like the ones below:

<p align="center">
  <img src="https://github.com/user-attachments/assets/1fae23a5-b357-4caa-afa0-0ead2e4c621e" alt="Pi Noise Example 1">
  <br>
  60x40
</p>

<p align="center">
  <img src="https://github.com/user-attachments/assets/a191f514-319f-450a-8c6e-794435b9b7cb" alt="Pi Noise Example 2">
  <br>
  1280x720
</p>
