#include "assetManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

TextureData AssetManager::loadTexture(const char* filename){
    TextureData tex;

    stbi_set_flip_vertically_on_load(true);
    tex.texData = stbi_load(filename, &tex.width, &tex.height, &tex.nrChannels, 0);

    return tex;
}

void AssetManager::freeTexture(TextureData& tex){
    stbi_image_free(tex.texData);
    tex.texData = nullptr;
}