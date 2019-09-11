//
// Created by JOSHUA HADDAD on 2019-04-12.
//
#pragma once

#include <map>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

using std::string;
using std::map;
using std::vector;
using sf::Texture;


class ResourceManager {
    
public:
    map<string, Texture> textures_;
    Texture* GetTexture(string key);
    void AddTexture(string key, Texture texture);
    void AddTexture(string key, string filepath);
    void AddTextureList(const vector<string>& keys, const vector<Texture>& textures);
    void AddTextureList(const vector<string>& keys, const vector<string>& paths);

};



