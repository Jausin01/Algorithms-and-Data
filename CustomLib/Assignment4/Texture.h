#pragma once
#include <string>
#include <iostream>

class Texture
{
public:
    Texture()
    {
    }

    Texture(const std::string& filePath)
        : mFilePath(filePath)
    {
    }

    void Print()
    {
        std::cout << "Rendering: " << mFilePath << "\n";
    }

    void SetFilePath(std::string filePath)
    {
        mFilePath = filePath;
    }

private:
    std::string mFilePath;
};