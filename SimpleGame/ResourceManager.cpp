//
// Created by JOSHUA HADDAD on 2019-04-12.
//

#include "ResourceManager.h"

Texture* ResourceManager::GetTexture(string key) {
    Texture* ptr = &textures_[key];
    return ptr;
}

void ResourceManager::AddTexture(string key, Texture texture) {
    textures_[key] = texture;
}

void ResourceManager::AddTexture(string key, string filepath){
    Texture new_texture;
    new_texture.loadFromFile(filepath);
    textures_[key] = new_texture;
}

void ResourceManager::AddTextureList(const vector<string> &keys, const vector<Texture> &textures) {
    for(int i = 0; i < textures.size(); i++)
        textures_[keys.at(i)] = textures.at(i);

}

void ResourceManager::AddTextureList(const vector<string> &keys, const vector<string> &paths) {
    for(int i = 0; i < paths.size(); i++){
        Texture texture;
        texture.loadFromFile(paths.at(i));
        textures_[keys.at(i)] = texture;
    }
}

