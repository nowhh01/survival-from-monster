#include "pch.h"
#include "Engine.h"
#include "Monster.h"

Monster* Engine::CreateMonsters(int numMonsters, const sf::IntRect& arena)
{
	Monster* monsters = new Monster[numMonsters];

	int maxY = arena.height - TILE_SIZE;
	int minY = arena.top + TILE_SIZE;
	int maxX = arena.width - TILE_SIZE;
	int minX = arena.left + TILE_SIZE;

	for (int i = 0; i < numMonsters; i++)
	{
		srand((int)time(0) * i);
		int side = (rand() % 4);
		float x, y;

		switch (side)
		{
		case 0:
			// left
			x = minX;
			y = (rand() % maxY) + minY;
			break;
		case 1:
			// right
			x = maxX;
			y = (rand() % maxY) + minY;
			break;
		case 2:
			// top
			x = (rand() % maxX) + minX;
			y = minY;
			break;
		case 3:
			// bottom
			x = (rand() % maxX) + minX;
			y = maxY;
			break;
		default:
			break;
		}

		srand((int)time(0) * i * 2);
		int type = (rand() % 3);

		monsters[i].Spawn(x, y, type, i);
	}
	
	return monsters;
}