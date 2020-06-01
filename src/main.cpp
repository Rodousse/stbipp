#include <stbipp/Image.hpp>
#include <stbipp/ImageImporter.hpp>

int main()
{
    auto image = stbipp::loadImage<stbipp::ImageFormat::RGB8>("D:/Bureau/easy.png");

    image(0, 0) = stbipp::Color3uc{255, 127, 0};


    stbipp::Image<stbipp::ImageFormat::RGBA32> imageFloat(image);


    return 0;
}
