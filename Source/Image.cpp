#include "Image.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include "Vendor/stb_image.h"
#include "Vendor/stb_image_write.h"
#include "Vendor/stb_image_resize.h"


// Image IO

Image::Image(const std::string& filePath)
    : mWidth(0), mHeight(0), mChannels(0), mData(nullptr), mFilePath(filePath)
{
    if (!Load(filePath))
    {
        std::cout << "(ERSA) ERROR : File " << mFilePath << " cannot be read properly\n";
    }
}

Image::Image(int width, int height, int channels)
    : mWidth(width), mHeight(height), mChannels(channels)
{
    mData = new unsigned char[width * height * channels];
}

Image::Image(const Image& img)
    : mWidth(img.mWidth), mHeight(img.mHeight), mChannels(img.mChannels)
{
    mData = new unsigned char[mWidth * mHeight * mChannels];
    memcpy(mData, img.mData, mWidth * mHeight * mChannels);
}


Image::~Image()
{
    stbi_image_free(mData);
}

bool Image::Load(const std::string& filePath)
{
    mData = stbi_load(mFilePath.c_str(), &mWidth, &mHeight, &mChannels, 0);

    return mData != nullptr;
}

bool Image::Save(const std::string& filePath)
{
    bool result;
    switch (GetImageType(filePath))
    {
    case ImageType::INVALID:
        return false;
    case ImageType::PNG:
        result = stbi_write_png(filePath.c_str(), mWidth, mHeight, mChannels, mData, mWidth * mChannels);
        break;
    case ImageType::BMP:
        result = stbi_write_bmp(filePath.c_str(), mWidth, mHeight, mChannels, mData);
        break;
    case ImageType::TGA:
        result = stbi_write_tga(filePath.c_str(), mWidth, mHeight, mChannels, mData);
        break;
    case ImageType::JPG:
        result = stbi_write_jpg(filePath.c_str(), mWidth, mHeight, mChannels, mData, 100);
        break;
    case ImageType::HDR:
        result = stbi_write_hdr(filePath.c_str(), mWidth, mHeight, mChannels, (const float*)mData);
        break;
    default:
        return false;
    }

    return result;
}

Image::ImageType Image::GetImageType(const std::string& filePath)
{
    std::string extension;
    if (filePath.find_last_of(".") != std::string::npos)
    {
        extension = filePath.substr(filePath.find_last_of(".") + 1);
    }
    else
    {
        std::cout << "(ERSA) ERROR : Cannot get extension from " << filePath << std::endl;
        return ImageType::INVALID;
    }

    if (extension == "png")
    {
        return ImageType::PNG;
    }
    else if (extension == "bmp")
    {
        return ImageType::BMP;
    }
    else if (extension == "tga")
    {
        return ImageType::TGA;
    }
    else if (extension == "jpg")
    {
        return ImageType::JPG;
    }
    else if (extension == "hdr")
    {
        return ImageType::HDR;
    }
    else
    {
        std::cout << "(ERSA) ERROR : Invalid extension from " << filePath << std::endl;
        return ImageType::INVALID;
    }

}


// Image Processing

Image::Pixel Image::GetPixel(int x, int y)
{
    Pixel pixel = { 0,0,0,0 };

    // error check
    if (x > mWidth)
    {
        return pixel;
    }
    if (y > mHeight)
    {
        return pixel;
    }


    unsigned int location = (y * mWidth * mChannels) + (x * mChannels);
    pixel.r = mData[location + 0];
    pixel.g = mData[location + 1];
    pixel.b = mData[location + 2];
    if (mChannels == 4)
        pixel.a = mData[(y * mWidth * mChannels) + (x * mChannels) + 3];

    return pixel;
}

void Image::SetPixel(const Pixel& pixel, int x, int y)
{
    // error check
    if (x > mWidth)
    {
        std::cout << "(ERSA) ERROR : x should be less than width = " << mWidth << std::endl;
    }
    if (y > mHeight)
    {
        std::cout << "(ERSA) ERROR : y should be less than height = " << mHeight << std::endl;
    }

    unsigned int location = (y * mWidth * mChannels) + (x * mChannels);
    mData[location + 0] = pixel.r;
    mData[location + 1] = pixel.g;
    mData[location + 2] = pixel.b;
    if (mChannels == 4)
        mData[(y * mWidth * mChannels) + (x * mChannels) + 3] = pixel.a;
}
