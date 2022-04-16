#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "TextureHolder.h"


using namespace sf;


int main()
{
	RenderWindow window(VideoMode::getDesktopMode(), "Game Map", Style::Fullscreen);

	std::string filename = "map.csv";
	const int mapRows = 10;
	const int mapColumns = 20;
	const int size = mapRows * mapColumns;
	std::ifstream mapFile(filename, std::ios::binary);
	std::vector<int> mapNumbers;
	int number;

	TextureHolder th;
	Texture& texture = TextureHolder::GetTexture("graphics/background_sheet2.png");;
	int TILE_SIZE = 100;

	VertexArray rVA;
	const int worldHeight = mapRows * TILE_SIZE;
	const int worldWidth = mapColumns * TILE_SIZE;
	const int VERTS_IN_QUAD = 4;
	rVA.setPrimitiveType(Quads);
	rVA.resize(worldHeight * worldWidth * VERTS_IN_QUAD);
	int currentVertex = 0;
	int verticalOffset = 0;

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
	std::cout << mapNumbers.size() << std::endl;

	int i = 0;
	for (int h = 0; h < mapRows; h++)
	{
		for  (int w = 0; w < mapColumns; w++)
		{
			//for (int i = 0; i < mapNumbers.size(); i++)

			rVA[currentVertex + 0].position = Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 1].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			rVA[currentVertex + 2].position = Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			rVA[currentVertex + 3].position = Vector2f((w * TILE_SIZE), (h * TILE_SIZE) + TILE_SIZE);

			verticalOffset = mapNumbers[i] * TILE_SIZE;

			rVA[currentVertex + 0].texCoords = Vector2f(0, 0 + verticalOffset);
			rVA[currentVertex + 1].texCoords = Vector2f(TILE_SIZE, 0 + verticalOffset);
			rVA[currentVertex + 2].texCoords = Vector2f(TILE_SIZE, TILE_SIZE + verticalOffset);
			rVA[currentVertex + 3].texCoords = Vector2f(0, TILE_SIZE + verticalOffset);

			currentVertex = currentVertex + VERTS_IN_QUAD;

			i++;
		}
	}

	while (window.isOpen())
	{
		Event event;

		while(window.pollEvent(event))
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
			}
		}
		

		window.clear();
		window.draw(rVA, &texture);
		window.display();
	}

	return 0;
};