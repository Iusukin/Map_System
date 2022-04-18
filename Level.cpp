#include "Level.h"

Level::Level(std::string filename, Texture& texture, const int tileSize)
{
	//load mapfile and read into vector
	std::ifstream mapFile(filename, std::ios::binary);
	std::vector<int> mapNumbers;
	int number;

	if (!mapFile.is_open())
	{
		std::cout << "Unable to open file" << std::endl;
	}
	else
	{
		while (mapFile >> number)
		{
			mapNumbers.push_back(number);
		}
		mapFile.close();
	}

	//Setup VertexArray using quads and resize to size of map
	rVA.setPrimitiveType(Quads);
	rVA.resize(worldHeight * worldWidth * VERTS_IN_QUAD);
	m_tileSize = tileSize;
	m_texture = texture;
	int currentVertex = 0;
	int verticalOffset = 0;

	//Place tile into VertexArray based on map file. Each int in map file corresponds to a tile on spritesheet. Iterate through vector<int>.
	int i = 0;
	for (int h = 0; h < mapRows; h++)
	{
		for (int w = 0; w < mapColumns; w++)
		{
			rVA[currentVertex + 0].position = Vector2f(w * m_tileSize, h * m_tileSize);
			rVA[currentVertex + 1].position = Vector2f((w * m_tileSize) + m_tileSize, h * m_tileSize);
			rVA[currentVertex + 2].position = Vector2f((w * m_tileSize) + m_tileSize, (h * m_tileSize) + m_tileSize);
			rVA[currentVertex + 3].position = Vector2f((w * m_tileSize), (h * m_tileSize) + m_tileSize);

			verticalOffset = mapNumbers[i] * m_tileSize;

			rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			rVA[currentVertex + 1].texCoords = Vector2f(m_tileSize, 0 + verticalOffset);
			rVA[currentVertex + 2].texCoords = Vector2f(m_tileSize, m_tileSize + verticalOffset);
			rVA[currentVertex + 3].texCoords = Vector2f(0, m_tileSize + verticalOffset);

			currentVertex = currentVertex + VERTS_IN_QUAD;

			i++;
		}
	}

	mapNumbers.clear();
}

void Level::draw(RenderTarget& window)
{
	window.draw(rVA, &m_texture);
}

