/// @file
/// @copyright (c) Jean Frantz René

#include "image.h"
#include "shared_memory.h"
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

void imageClassOutput()
{
    // Test default constructor
    const Image<uint8_t> defaultImage(100, 100, 3);
    std::cout << "Default Constructor Test:" << '\n';
    std::cout << "Width: " << defaultImage.width() << '\n';
    std::cout << "Height: " << defaultImage.height() << '\n';
    std::cout << "Number of Channels: " << defaultImage.num_channels() << '\n';
    std::cout << "Size: " << defaultImage.size() << '\n';

    // Test custom data constructor
    const std::vector<uint8_t> data(100 * 100 * 3, 255);
    const Image<uint8_t> customImage(data, 100, 100, 3);
    std::cout << "\nCustom Data Constructor Test:" << '\n';
    std::cout << "Width: " << customImage.width() << '\n';
    std::cout << "Height: " << customImage.height() << '\n';
    std::cout << "Number of Channels: " << customImage.num_channels() << '\n';
    std::cout << "Size: " << customImage.size() << '\n';

    // Test pixel value setter and getter
    Image<uint8_t> image(100, 100, 3);
    image.pixelValue(10, 10, 0) = 255;
    image.pixelValue(10, 10, 1) = 128;
    image.pixelValue(10, 10, 2) = 64;
    std::cout << "\nPixel Value Setter/Getter Test:" << '\n';
    std::cout << "Pixel (10, 10, 0): " << static_cast<int>(image.pixelValue(10, 10, 0)) << '\n';
    std::cout << "Pixel (10, 10, 1): " << static_cast<int>(image.pixelValue(10, 10, 1)) << '\n';
    std::cout << "Pixel (10, 10, 2): " << static_cast<int>(image.pixelValue(10, 10, 2)) << '\n';

    // Test readData function
    const auto span = customImage.readData();
    std::cout << "\nRead Data Test:" << '\n';
    std::cout << "Span Size: " << span.size() << '\n';
    bool allValuesCorrect = true;
    for (const auto &value : span)
    {
        if (value != 255)
        {
            allValuesCorrect = false;
            break;
        }
    }
    std::cout << "All values are 255: " << (allValuesCorrect ? "True" : "False") << '\n';
}

int main()
{
    imageClassOutput();

    return 0;
}
