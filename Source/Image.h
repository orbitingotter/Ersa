#pragma once

#include <string>

class Image
{
public:
    struct Pixel
    {
        unsigned char r, g, b, a;
    };

public:

    Image(const std::string& filePath);         // loads existing image
    Image(int width, int height, int channels); // creates empty buffer
    Image(const Image& img);                    // copy constructor
    ~Image();

    bool Load(const std::string& filePath);
    bool Save(const std::string& filePath);

    Pixel GetPixel(int x, int y);
    void SetPixel(const Pixel& pixel, int x, int y);

private:
    enum class ImageType
    {
        INVALID = -1, PNG, BMP, TGA, JPG, HDR
    };
    ImageType GetImageType(const std::string& filePath);

public:
    int GetWidth() const { return mWidth; }
    int GetHeight() const { return mHeight; }
    int GetChannels() const { return mChannels; }
    unsigned char* GetImageData() { return mData; }
    const std::string& GetFilePath() const { return mFilePath; }

private:
    int mWidth, mHeight;
    int mChannels;
    unsigned char* mData;

    std::string mFilePath;
};