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

void platformCollisionShuriken(std::vector<Platform>& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction);
void platformCollisionItem(std::vector<Platform>& vect, Item& Item, Collider col, sf::Vector2f direction);
void playerCollisionShuriken(Player& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction);
void playerCollisionItem(Player& vect, Item& Item, Collider col, sf::Vector2f direction);
void upDateShuriken(std::vector<Shuriken>& vest, float deltaTime);
void upDateItem(std::vector<Item>& vest, float deltaTime);
void moveShuriken(std::vector<Shuriken>& vest, sf::Vector2f move, float deltaTime);
void drawShuriken(std::vector<Shuriken>& vest, sf::RenderWindow& window);
void drawItem(std::vector<Item>& vest, sf::RenderWindow& window);
void printText(sf::Vector2f postiton, std::string message, sf::RenderWindow& window);

sf::Vector2f Speed(float time);

int shuriken = 0;
int item = -1;
int Hp = 4;
int numshuriken = 2;

//dead
float dead = 0;
//move Shuriken
sf::Vector2f move;

int main(){
	move.x = 500;
	move.y = 200;
	//Text
	
	//vector
	std::vector<Platform> platforms;
	std::vector<Shuriken> shurikens;
	std::vector<Item> items;

	//window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Shuriken Strike", sf::Style::Close | sf::Style::Resize);

	//shape
	sf::RectangleShape bg01(sf::Vector2f(1920, 1080));
	sf::RectangleShape hp(sf::Vector2f(30, 30));

	//Texture
	sf::Texture Hppng;
	sf::Texture shurikenpng;
	sf::Texture bg01png;
	sf::Texture platformpng;
	sf::Texture playepng;
	sf::Texture itempng;
	sf::Texture deadpng;

	Hppng.loadFromFile("png/heart.png");
	itempng.loadFromFile("png/item.png");
	shurikenpng.loadFromFile("png/shuriken.png");
	bg01png.loadFromFile("png/bg03.png");
	platformpng.loadFromFile("png/03.png");
	playepng.loadFromFile("png/player05.png");
	deadpng.loadFromFile("png/dead.png");

	//player
	Player player(&playepng, sf::Vector2u(4, 3), 0.2f, 400.0f);
	//animatiun player
	sf::RectangleShape shapeDead(sf::Vector2f(210, 170));
	Animation playerdead(&deadpng, sf::Vector2u(4, 1), 0.3f);
	shapeDead.setTexture(&deadpng);

	sf::Vector2f direction;
	bg01.setTexture(&bg01png);
	hp.setTexture(&Hppng);
	hp.setPosition(50, 50);
	platforms.push_back(Platform(&platformpng, sf::Vector2f(1400.0f, 150.0f), sf::Vector2f(960.0f, 840.0f)));
	Platform platformend(nullptr, sf::Vector2f(4000.0f, 1.0f), sf::Vector2f(960.0f, 1040.0f));
	
	//timeclock
	float deltaTime = 0.0f;
	float shurikenTime = 0.0f;
	float TimeMove = 0;
	float itemTime = 0;
	float immortalTime = 0;
	float flashingTime = 0;
	float deadTime = 0;

	sf::Clock clock;
	sf::Clock clockShuriken;
	sf::Clock clockMove;
	sf::Clock clockItem;
	sf::Clock clockImmortal;
	sf::Clock clockFlashing;
	sf::Clock clockDead;

	while (window.isOpen())
	{
		itemTime = clockItem.getElapsedTime().asMilliseconds();
		shurikenTime = clockShuriken.getElapsedTime().asMilliseconds();
		TimeMove = clockMove.getElapsedTime().asMilliseconds();
		immortalTime = clockImmortal.getElapsedTime().asMilliseconds();
		flashingTime = clockFlashing.getElapsedTime().asMilliseconds();
		deadTime = clockDead.getElapsedTime().asMilliseconds();

		//
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
		//ranItem
		item = rand() % 5;
		
		upDateItem(items, deltaTime);
		upDateShuriken(shurikens, deltaTime);
		moveShuriken(shurikens, Speed(TimeMove), deltaTime);
		int ran = rand() % 3;
		int ranm = 0;
		if (ran == 2) ranm = 150;
		else if (ran == 1) ranm = 0;
		else ranm = -150;

		int ranItem = rand() % 1920;

		if (shuriken < numshuriken)
		{
			if (shurikenTime > 800)
			{
				shurikens.push_back(Shuriken(&shurikenpng, sf::Vector2u(8, 1), 0.0001, sf::Vector2f(80, 80), player.GetPosition().x + ranm));
				shuriken++;
				clockShuriken.restart();
			}
		}
		for (int i = 0; i < shurikens.size(); i++)
		{
			Collider temp = shurikens[i].GetCollider();
			platformCollisionShuriken(platforms, shurikens[i], temp, direction);
			playerCollisionShuriken(player, shurikens[i], temp, direction);
		}
		//TimeRestart
		if (TimeMove > 1500) clockMove.restart();
		if (flashingTime > 300) clockFlashing.restart();
		if (Hp > 0) clockDead.restart();
		if (dead == 1)
		{
			if (immortalTime > 2000) {
				dead = 0;
				clockImmortal.restart();
			}
		}
		else clockImmortal.restart();
		
		//Item 
		if (itemTime > 9000)
		{
			items.push_back(Item(&itempng, sf::Vector2u(6, 1), 0.25, sf::Vector2f(40, 40), player.GetPosition().x + ranItem));
			clockItem.restart();
		}
		for (int i = 0; i < items.size(); i++)
		{
			Collider temp = items[i].GetCollider();
			platformCollisionItem(platforms, items[i], temp, direction);
			platformCollisionItem(platformend, items[i], temp, direction);
			playerCollisionItem(player, items[i], temp, direction);

		}

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
		printText(sf::Vector2f(100, 50),std::to_string(Hp), window);
		printText(sf::Vector2f(100, 140),std::to_string(shuriken), window);
		if (platformend.GetCollider().CheckCollision(playerCollision, direction,1))
		{

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		if (Hp <= 0)
		{ 
			dead = 3;
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
void platformCollisionShuriken(std::vector<Platform>& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction)
{
	for (Platform& platform : vect)
	{
		if (platform.GetCollider().CheckCollision(col, direction, 1.0f))
		{
			Shuriken.setDestroy(true);
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

	}
}
void playerCollisionShuriken(Player& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction)
{
	
	if (dead == 0) 
	{
		if (vect.GetCollider().CheckCollision(col, direction, 1.0f))
		{
			Shuriken.setDestroy(true);
			Hp--;
			dead = 1;
		}
	}
	else
	{
		
	}
}
void playerCollisionItem(Player& vect, Item& Item, Collider col, sf::Vector2f direction)
{
	if (vect.GetCollider().CheckCollision(col, direction, 1.0f))
	{
		Item.setDestroy(true);
		switch (item)
		{
		case(0):
			Hp + 1; break;
			
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
void printText(sf::Vector2f postiton,std::string message, sf::RenderWindow& window) {
	sf::Font fonttast;
	fonttast.loadFromFile("font/Deventer.ttf");
	sf::Text texttast;
	texttast.setFont(fonttast);
	//texttast.setStyle(sf::Text::Bold);
	texttast.setPosition(postiton);
	texttast.setCharacterSize(20);
	texttast.setString(message);
	texttast.setFillColor(sf::Color::White);
	window.draw(texttast);
}
