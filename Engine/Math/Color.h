#pragma once
#include <cstdint>
#include <iostream>
#include <string>

namespace neu 
{

    struct Color 
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;

        static const Color white;
        static const Color black;
        static const Color red;
        static const Color green;
        static const Color blue;

    };
    
    std::istream& operator >> (std::istream& stream, Color& color);

    std::istream& operator >> (std::istream& stream, Color& color);
}