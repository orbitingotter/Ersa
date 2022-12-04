#include <iostream>
#include "Image.h"
#include <algorithm>

int main()
{
    Image image("Images/land.jpg");
    Image::Pixel pixel;


    for (int i = 0;i < image.GetHeight(); i++)
    {
        for (int j = 0; j < image.GetWidth(); j++)
        {
            pixel = image.GetPixel(j, i);
            // turn sepia
            unsigned char r = (unsigned char)std::min((int)(((float)pixel.r * 0.393f) + ((float)pixel.g * 0.769f) + ((float)pixel.b * 0.189f)), 255);
            unsigned char g = (unsigned char)std::min((int)(((float)pixel.r * 0.349f) + ((float)pixel.g * 0.686f) + ((float)pixel.b * 0.168f)), 255);
            unsigned char b = (unsigned char)std::min((int)(((float)pixel.r * 0.272f) + ((float)pixel.g * 0.534f) + ((float)pixel.b * 0.131f)), 255);

            image.SetPixel({ r, g , b, 0 }, j, i);
        }
    }

    image.Save("Images/output.png");
    return 0;
}