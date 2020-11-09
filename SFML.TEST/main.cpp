#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"
#include "Shuriken.h"
#include "Item.h"
#include <Windows.h>
#include <math.h>

void playerCollisionItem(Player& vect, Item& Item, Collider col, sf::Vector2f direction);
void platformCollisionShuriken(std::vector<Platform>& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction);
void platformCollisionItem(std::vector<Platform>& vect, Item& Item, Collider col, sf::Vector2f direction);
void playerCollisionShuriken(Player& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction);
void upDateShuriken(std::vector<Shuriken>& vest, float deltaTime);
void upDateShurikenV2(std::vector<Shuriken>& vest, float deltaTime);
void upDateItem(std::vector<Item>& vest, float deltaTime);
void moveShuriken(std::vector<Shuriken>& vest, sf::Vector2f move, float deltaTime);
void moveShurikenV2(std::vector<Shuriken>& vest, sf::Vector2f move, float deltaTime);
void drawShuriken(std::vector<Shuriken>& vest, sf::RenderWindow& window);
void drawItem(std::vector<Item>& vest, sf::RenderWindow& window);
void printText(sf::Vector2f postiton, std::string message, float size, sf::RenderWindow& window);

sf::Vector2f Speed(float time);
int score = 0;

int shuriken = 0;
int numshuriken = 2;

int shurikenV2 = 0;
int numshurikenV2 = 0;

int Hp = 3;
int item = -1;
bool checkItme = false;
bool immortal = false;
bool checkTimeshurikenV2 = false;
//dead
float dead = 0;
//move Shuriken
sf::Vector2f move;

float TimeMoveV2 = 0;
sf::Clock clockMoveV2;

int main(){
	int level = 1;

	move.x = 400;
	move.y = 200;

	sf::Vector2f playerP;
	//Text
	
	//vector
	std::vector<Platform> platforms;
	std::vector<Shuriken> shurikens;
	std::vector<Shuriken> shurikenV2s;
	std::vector<Item> items;

	sf::Vector2f direction;
	//window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Shuriken Strike", sf::Style::Close | sf::Style::Resize);

	//shape
	sf::RectangleShape bg01(sf::Vector2f(1920, 1080));
	sf::RectangleShape hp(sf::Vector2f(30, 30));
	sf::RectangleShape immAS(sf::Vector2f(220, 220));

	//Texture
	sf::Texture immortalpng;
	sf::Texture Hppng;
	sf::Texture shurikenpng;
	sf::Texture bg01png;
	sf::Texture platformpng;
	sf::Texture playepng;
	sf::Texture itempng;
	sf::Texture deadpng;
	sf::Texture protectpng;

	protectpng.loadFromFile("png/protect01.png");
	immortalpng.loadFromFile("png/immortal.png");
	Hppng.loadFromFile("png/heart.png");
	itempng.loadFromFile("png/item.png");
	shurikenpng.loadFromFile("png/shuriken.png");
	bg01png.loadFromFile("png/bg04.png");
	platformpng.loadFromFile("png/03.png");
	playepng.loadFromFile("png/player06.png");
	deadpng.loadFromFile("png/dead.png");

	//player
	Player player(&playepng, sf::Vector2u(4, 4), 0.2f, 400.0f);
	sf::RectangleShape shapeDead(sf::Vector2f(210, 170));
	Animation playerdead(&deadpng, sf::Vector2u(4, 1), 0.3f);
	shapeDead.setTexture(&deadpng);

	Animation immAnima(&protectpng, sf::Vector2u(3, 1), 0.2f);

	immAS.setTexture(&protectpng);
	bg01.setTexture(&bg01png);
	hp.setTexture(&Hppng);
	
	hp.setPosition(50, 50);
	platforms.push_back(Platform(&platformpng, sf::Vector2f(1400.0f, 150.0f), sf::Vector2f(960.0f, 840.0f)));
	
	//timeclock

	float deltaTime = 0.0f;
	float shurikenTime = 0.0f;
	float shurikenTimeV2 = 0.0f;
	float TimeMove = 0;
	float immortalTime = 0;
	float flashingTime = 0;
	float deadTime = 0;
	float deadImmortalTime = 0;
	float timeGame = 0;
	float timeLevel = 0;

	sf::Clock clock;
	sf::Clock clockShuriken;
	sf::Clock clockShurikenV2;
	sf::Clock clockMove;
	sf::Clock clockImmortal;
	sf::Clock clockDeadImmortal;
	sf::Clock clockFlashing;
	sf::Clock clockDead;
	sf::Clock clockGame;
	sf::Clock clockLevel;

	while (window.isOpen())
	{
		TimeMoveV2 = clockMoveV2.getElapsedTime().asMilliseconds();

		timeLevel = clockLevel.getElapsedTime().asSeconds();
		shurikenTime = clockShuriken.getElapsedTime().asMilliseconds();
		shurikenTimeV2 = clockShurikenV2.getElapsedTime().asMilliseconds();
		TimeMove = clockMove.getElapsedTime().asMilliseconds();
		deadImmortalTime = clockDeadImmortal.getElapsedTime().asMilliseconds();
		immortalTime = clockImmortal.getElapsedTime().asMilliseconds();
		flashingTime = clockFlashing.getElapsedTime().asMilliseconds();
		deadTime = clockDead.getElapsedTime().asMilliseconds();

		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;

		//bg
		window.draw(bg01);
		
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			}
		}
		//level
		if (timeLevel > 10)
		{
			move.x += 25;
			move.x += 25;
			level++;
			clockLevel.restart();
			if (level % 3 == 0)
			{
				numshurikenV2++;
			}
			if (level % 5 == 0)
			{
				numshuriken++;
			}
			
		}
		
		upDateItem(items, deltaTime);
		upDateShuriken(shurikens, deltaTime);
		upDateShurikenV2(shurikenV2s, deltaTime);
		moveShuriken(shurikens,Speed(TimeMove), deltaTime);
		moveShurikenV2(shurikenV2s, sf::Vector2f(0,1500), deltaTime);
		int ran = rand() % 3;
		int ranm = 0;
		if (ran == 2) ranm = 150;
		else if (ran == 1) ranm = 0;
		else ranm = -150;
		std::cout << TimeMoveV2 << std::endl;
		int ranItem = rand() % 1920;

		if (shuriken < numshuriken)
		{
			if (shurikenTime > 800)
			{
				shurikens.push_back(Shuriken(&shurikenpng, sf::Vector2u(8, 1), 0.0001, sf::Vector2f(80, 80), player.GetPosition().x + ranm,sf::Color::Green));
				shuriken++;
				score++;
				clockShuriken.restart();
			}
		}
		if (shurikenTimeV2 > 2000)
		{
			for (int i = 0; i < numshurikenV2; i++)
			{
				shurikenV2s.push_back(Shuriken(&shurikenpng, sf::Vector2u(8, 1), 0.0001, sf::Vector2f(80, 80),rand() % 1400 + 260,sf::Color::Yellow));
				shurikenV2++;
				score++;
			}
			clockMoveV2.restart();
			clockShurikenV2.restart();	
		}
		
		for (int i = 0; i < shurikens.size(); i++)
		{ 
			Collider temp = shurikens[i].GetCollider();
			platformCollisionShuriken(platforms, shurikens[i], temp, direction);
			playerCollisionShuriken(player, shurikens[i], temp, direction);
		}
		for (int i = 0; i < shurikenV2s.size(); i++)
		{
			Collider temp = shurikenV2s[i].GetCollider();
			platformCollisionShuriken(platforms, shurikenV2s[i], temp, direction);
			playerCollisionShuriken(player, shurikenV2s[i], temp, direction);
		}
		//TimeRestart
		if (TimeMove > 1500) clockMove.restart();
		if (flashingTime > 300) clockFlashing.restart();
		if (Hp > 0) clockDead.restart();
		if (dead == 1)
		{
			if (deadImmortalTime > 1500) {
				dead = 0;
				clockDeadImmortal.restart();
			}
		}
		else clockDeadImmortal.restart();
		
		//Item 
		if (checkItme)
		{
			items.push_back(Item(&itempng, sf::Vector2u(6, 1), 0.25, sf::Vector2f(40, 40), player.GetPosition().x + ranItem));
			checkItme = false;
		}
		for (int i = 0; i < items.size(); i++)
		{
			Collider temp = items[i].GetCollider();
			platformCollisionItem(platforms, items[i], temp, direction);
			playerCollisionItem(player, items[i], temp, direction);	
		}
		//2
		if (immortal)
		{
			if (immortalTime < 4000)
			{
				Platform immortalShape(nullptr, sf::Vector2f(190, 190), sf::Vector2f(player.GetPosition()));
				for (Shuriken& S : shurikens)
				{
					Collider temp = S.GetCollider();
					if (immortalShape.GetCollider().CheckCollision(temp, direction, 1.0f))
					S.setDestroy(true);
				}
				for (Shuriken& S : shurikenV2s)
				{
					Collider temp = S.GetCollider();
					if (immortalShape.GetCollider().CheckCollision(temp, direction, 1.0f))
						S.setDestroy(true);

				}
				immAnima.Update(0, deltaTime, 1);
				immAS.setPosition(player.GetPosition());
				immAS.setOrigin(110, 110);
				immAS.setTextureRect(immAnima.uvRect);
				window.draw(immAS);

			}
			else immortal = false;
		}
		else clockImmortal.restart();
		Collider playerCollision = player.GetCollider();
		for (Platform& platform : platforms)
		{
			if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
			{
				player.OnCollision(direction);
			}
			platform.Draw(window);
		}
			
		drawItem(items, window);
		drawShuriken(shurikens, window);
		drawShuriken(shurikenV2s, window);
		player.Update(deltaTime);

		if (dead == 1) 
		{
			if (flashingTime > 150) player.Draw(window);
		}
		else if (dead == 0)
		{
			player.Draw(window);
			shapeDead.setPosition(sf::Vector2f(player.GetPosition().x,player.GetPosition().y-100));
		}
		else
		{
			if (deadTime > 1200) window.close();
			
			playerdead.Update(0, deltaTime, player.faceRight);
			shapeDead.setTextureRect(playerdead.uvRect);
			window.draw(shapeDead);
		}
		window.draw(hp);
		//Text
		printText(sf::Vector2f(1600, 20),"SCORE",40, window);
		printText(sf::Vector2f(1775, 20),std::to_string(score),40, window);
		printText(sf::Vector2f(100, 50),std::to_string(Hp),24, window);
		printText(sf::Vector2f(1645, 80), "LEVEL",28, window);
		printText(sf::Vector2f(1780, 80), std::to_string(level),28, window);
		printText(sf::Vector2f(100, 140),std::to_string(shuriken),24, window);
		if (player.GetPosition().y > 1500)
		{
			window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		if (Hp <= 0)
		{ 
			dead = 3;
			immortal = false;
		}

		window.display();
	}
	return 0;
} 
sf::Vector2f Speed(float time)
{
	sf::Vector2f speed;
	if (time > 750) speed.x = move.x;
	else  speed.x = -move.x;
	speed.y = move.y;
	return speed;
}
void playerCollisionItem(Player& vect, Item& Item, Collider col, sf::Vector2f direction)
{
	int randItem = rand() % 2;
	if (vect.GetCollider().CheckCollision(col, direction, 1.0f))
	{
		Item.setDestroy(true);
		switch (randItem)
		{
			case(0)://Hp
			{
				Hp += 1; break;
			}
			case(1)://Immortal
			{
				immortal = false;
				immortal = true; break;
			}
		}
	}
}
void platformCollisionShuriken(std::vector<Platform>& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction)
{
	int randItem = rand() % 30;
	for (Platform& platform : vect)
	{
		if (platform.GetCollider().CheckCollision(col, direction, 1.0f))
		{
			
			Shuriken.setDestroy(true);
			if(randItem == 1|| randItem == 11|| randItem == 12|| randItem == 2|| randItem == 5)
			{
				checkItme = true;
			}
			
		}

	}
}
void platformCollisionItem(std::vector<Platform>& vect, Item& Item, Collider col, sf::Vector2f direction)
{
	for (Platform& platform : vect)
	{
		if (platform.GetCollider().CheckCollision(col, direction, 1.0f))
		{
			Item.setDestroy(true);
		}
		if (Item.GetPosition().y > 2000)
		{
			Item.setDestroy(true);
		}

	}
}
void playerCollisionShuriken(Player& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction)
{
	
	if (dead == 0 && immortal == false)
	{
		if (vect.GetCollider().CheckCollision(col, direction, 1.0f))
		{
			Shuriken.setDestroy(true);
			Hp--;
			dead = 1;
		}
	}
}
void upDateShuriken(std::vector<Shuriken>& vest, float deltaTime)
{
	for (Shuriken& Rocket : vest)
	{
		Rocket.Update(deltaTime);
	}
	for (int i = 0; i < vest.size(); i++)
	{
		if (vest[i].isDestroy())
		{
			vest.erase(vest.begin() + i);
			shuriken--;
		}
	}
}
void upDateShurikenV2(std::vector<Shuriken>& vest, float deltaTime)
{
	for (Shuriken& Rocket : vest)
	{
		Rocket.Update(deltaTime);
	}
	for (int i = 0; i < vest.size(); i++)
	{
		if (vest[i].isDestroy())
		{
			vest.erase(vest.begin() + i);
			shurikenV2--;
		}
	}
}
void upDateItem(std::vector<Item>& vest, float deltaTime)
{
	for (Item& Item : vest)
	{
		Item.Update(deltaTime);
	}
	for (int i = 0; i < vest.size(); i++)
	{
		if (vest[i].isDestroy())
		{
			vest.erase(vest.begin() + i);
		}
	}
}
void moveShuriken(std::vector<Shuriken>& vest, sf::Vector2f move, float deltaTime)
{

	for (Shuriken& Rocket : vest)
	{
		Rocket.Move(move, deltaTime);
		if (Rocket.GetPosition().y > 1100)
			Rocket.setDestroy(true);
	}
}
void moveShurikenV2(std::vector<Shuriken>& vest, sf::Vector2f move, float deltaTime)
{
	
	if (TimeMoveV2 > 500)
	{
		for (Shuriken& Rocket : vest)
		{
			Rocket.Move(move, deltaTime);
			if (Rocket.GetPosition().y > 1100)
				Rocket.setDestroy(true);
		}
	}
	
}
void drawShuriken(std::vector<Shuriken>& vest, sf::RenderWindow& window)
{
	for (Shuriken& Rocket : vest)
		Rocket.Draw(window);
}
void drawItem(std::vector<Item>& vest, sf::RenderWindow& window)
{
	for (Item& Item : vest)
		Item.Draw(window);
}
void printText(sf::Vector2f postiton,std::string message,float size, sf::RenderWindow& window) {
	sf::Font fonttast;
	fonttast.loadFromFile("font/Neuterous.otf");
	sf::Text texttast;
	texttast.setFont(fonttast);
	//texttast.setStyle(sf::Text::Bold);
	texttast.setPosition(postiton);
	texttast.setCharacterSize(size);
	texttast.setString(message);
	texttast.setFillColor(sf::Color::White);
	window.draw(texttast);
}
