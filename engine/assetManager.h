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
        TextureData loadTexture(const char* filename);
        void freeTexture(TextureData& tex);
};