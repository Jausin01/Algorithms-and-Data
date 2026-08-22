#pragma once
#include "UnorderedMap.h"
#include "Texture.h"


class TextureManager 
{
public:
    static TextureManager& GetInstance() 
    {
        static TextureManager instance;
        return instance;
    }

    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    size_t LoadTexture(const std::string& filePath)
    {
        size_t id = Global::HashFunction(filePath);

        if (!mTextures.Has(id))
        {
            Texture texture(filePath);
            mTextures.Insert(id, texture);
        }

        return id;
    }

    bool GetTexture(size_t id, Texture& outTexture)
    {
        return mTextures.Find(id, outTexture);
    }

private:
    TextureManager() = default;  
    ~TextureManager() = default; 
    UnorderedMap<size_t, Texture> mTextures;
};
