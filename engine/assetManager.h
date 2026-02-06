/* asset manager pre-loads textures/assets on a loading screen, helps with sluggish performance or
   instances where nothing renders because the textures were too large to load in quick enough */

#pragma once

struct TextureData {
    int width;
    int height;
    int nrChannels;
    unsigned char* texData;
};

class AssetManager {
    public:
        AssetManager() = default;

        TextureData loadTexture(const char* filename);
        void freeTexture(TextureData& tex);

        // disabled copying
        AssetManager(const AssetManager&) = delete;
        AssetManager& operator = (const AssetManager&) = delete;

        // moving allowed
        AssetManager(AssetManager&& other) noexcept;
        AssetManager& operator=(AssetManager&& other) noexcept;
};