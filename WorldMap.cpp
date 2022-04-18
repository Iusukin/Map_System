#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "TextureHolder.h"
#include "Level.h"


using namespace sf;


int main()
{
	RenderWindow window(VideoMode::getDesktopMode(), "Game Map", Style::Fullscreen);

	//load texture for map and set tile size of texture
	TextureHolder th;
	Texture& bcgTexture = TextureHolder::GetTexture("graphics/background_sheet2.png");
	const int tileSize = 100;
	

	while (window.isOpen())
	{
		Event event;

		//load map file and construct level
		std::string filename = "maps/level1.txt";
		Level level1(filename, bcgTexture, tileSize);


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
		
		//Display and draw calls
		window.clear();
		level1.draw(window);
		window.display();
	}

	return 0;
};