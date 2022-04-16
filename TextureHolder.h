#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

using namespace sf;
using namespace std;

class TextureHolder
{
private:
	//map holder holding pairs of string and texture
	std::map<std::string, Texture> m_Textures;

	//pointer of the same type as the class
	static TextureHolder* m_s_Instance;

public:
	TextureHolder();
	static Texture& GetTexture(string const& filename);

};


#endif
