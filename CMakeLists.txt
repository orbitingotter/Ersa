cmake_minimum_required(VERSION 3.10)

project(Ersa)


SET(SOURCE
    Source/App.cpp
    Source/Image.cpp
)

SET(HEADERS
    Source/Image.h

    
    Source/Vendor/stb_image.h
    Source/Vendor/stb_image_write.h
    Source/Vendor/stb_image_resize.h

)

add_executable(Ersa ${SOURCE} ${HEADERS})

