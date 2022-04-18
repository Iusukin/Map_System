#pragma once
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace sf;

class Level
{
private:

	//Size of the map and Vertexarray
	const int mapRows = 10;
	const int mapColumns = 20;
	const int VERTS_IN_QUAD = 4;
	int m_tileSize = 1;
	int worldHeight = mapRows * m_tileSize;
	int worldWidth = mapColumns * m_tileSize;

protected:
	VertexArray rVA;
	Texture m_texture;

public:

	Level(std::string filename, Texture& texture, const int tileSize);
	void draw(RenderTarget& window);
};