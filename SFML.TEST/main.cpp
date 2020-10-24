#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "Player.h"
#include "Platform.h"
#include "Shuriken.h"
#include <Windows.h>
#include <math.h>
static const float View_HEIGHT = 720.0f;

void platformCollisionShuriken(std::vector<Platform>& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction);
void playerCollisionShuriken(Player& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction);
void upDateShuriken(std::vector<Shuriken>& vest, float deltaTime);
void moveShuriken(std::vector<Shuriken>& vest, sf::Vector2f move, float deltaTime);
void drawShuriken(std::vector<Shuriken>& vest, sf::RenderWindow& window);
sf::Vector2f Speed(float time);


void ResizeView(const sf::RenderWindow& window, sf::View& view)
{
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
	view.setSize((View_HEIGHT)*aspectRatio, View_HEIGHT);
}

int shuriken = 0;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920,1080), "Shuriken Strike",sf::Style::Close | sf::Style::Resize);
	
	sf::RectangleShape bg01(sf::Vector2f(1920, 1080));
	//test
	sf::Texture testRocket;
	testRocket.loadFromFile("png/shuriken.png");	

	sf::Texture bg01png;
	bg01png.loadFromFile("png/bg03.png");
	sf::Texture platformsgreed;
	platformsgreed.loadFromFile("png/03.png");
 
	sf::Texture mon_texture;
	mon_texture.loadFromFile("png/player05.png");
	Player monster(&mon_texture, sf::Vector2u(4, 3), 0.2f, 400.0f, 250.0f);
	std::vector<Platform> platforms;
	std::vector<Platform> platformend;
	std::vector<Shuriken> shurikens;

	sf::Vector2f direction;
	bg01.setTexture(&bg01png);
	platforms.push_back(Platform(&platformsgreed, sf::Vector2f(1400.0f, 150.0f), sf::Vector2f(960.0f, 840.0f)));
	
	platformend.push_back(Platform(nullptr, sf::Vector2f(4000.0f, 1.0f), sf::Vector2f(960.0f, 1040.0f)));
	sf::Vector2f move;
	float r = 350;
	double arctan = 0;
	double a = 0;
	double b = 0;
	float deltaTime = 0.0f;
	float rocketTime = 0.0f,rocketTimere = 0;
	float TimeMove = 0;
	double sa;
	sf::Clock clock,clockRocket,clockMove;
	while (window.isOpen())
	{
		window.draw(bg01);
		rocketTime = clockRocket.getElapsedTime().asMilliseconds();
		TimeMove = clockMove.getElapsedTime().asMilliseconds();
		deltaTime = clock.restart().asSeconds();
		if (deltaTime > 1.0f / 20.0f)
			deltaTime = 1.0f / 20.0f;
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
		
		if (TimeMove > 1500) clockMove.restart();
		
		upDateShuriken(shurikens, deltaTime);
		moveShuriken(shurikens,Speed(TimeMove), deltaTime);
		int ran = rand() % 3;
		int ranm = 0;
		if (ran == 2) ranm = 150;
		else if (ran == 1) ranm = 0;
		else ranm = -150;
		if (shuriken < 2)
		{
			if (rocketTime > 800)
			{
				shurikens.push_back(Shuriken(&testRocket, sf::Vector2u(8, 1), 0.0001, sf::Vector2f(80, 80), monster.GetPosition().x+ranm));
				shuriken++;
				clockRocket.restart();
			}
			
		}
			for (int i = 0; i < shurikens.size(); i++)
			{
				Collider temp = shurikens[i].GetCollider();
				platformCollisionShuriken(platforms, shurikens[i], temp, direction);
				platformCollisionShuriken(platformend, shurikens[i], temp, direction);
				playerCollisionShuriken(monster, shurikens[i], temp, direction);
			}
			//		arctan = (arctan + atan((monster.GetPosition().y + Rockets.GetPosition().y) / (monster.GetPosition().x + Rockets.GetPosition().x)))/2;
			drawShuriken(shurikens, window);
			Collider monsterCollision = monster.GetCollider();
		monster.Update(deltaTime);
		
		for (Platform& platform : platforms)
			if (platform.GetCollider().CheckCollision(monsterCollision, direction, 1.0f))
				monster.OnCollision(direction);
		
		monster.Draw(window);
		for (Platform& platform : platforms)
		platform.Draw(window);
		
		window.display();
		
		for (Platform& platformen : platformend)
		if (platformen.GetCollider().CheckCollision(monsterCollision, direction, 0.0f))
		{
			monster.SetPosition(sf::Vector2f(960.0f,0.0f));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
	}
	return 0;
}
sf::Vector2f Speed(float time)
{
	sf::Vector2f move;
	if (time > 750) move.x = 750;
	else move.x = -750;
	move.y = 300;
	return move;
}
void platformCollisionShuriken(std::vector<Platform>& vect, Shuriken& Shuriken,Collider col,sf::Vector2f direction)
{
	for (Platform& platform : vect)
	{
		if(platform.GetCollider().CheckCollision(col, direction, 1.0f))
		{
			Shuriken.setDestroy(true);
		}
			
	}
}
void playerCollisionShuriken(Player& vect, Shuriken& Shuriken,Collider col,sf::Vector2f direction)
{
	if (vect.GetCollider().CheckCollision(col, direction, 1.0f))
	{
		vect.SetPosition(sf::Vector2f(960.0f, 500.0f));
		Shuriken.setDestroy(true);
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
void moveShuriken(std::vector<Shuriken>& vest,sf::Vector2f move, float deltaTime)
{
	
	for (Shuriken& Rocket : vest)
	{
		Rocket.Move(move,deltaTime);
	}
}
void drawShuriken(std::vector<Shuriken>& vest,sf::RenderWindow& window)
{
	for (Shuriken& Rocket : vest)
		Rocket.Draw(window);
}