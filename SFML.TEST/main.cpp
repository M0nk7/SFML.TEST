#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <Windows.h>
#include <math.h>
#include "Player.h"
#include "Platform.h"
#include "Shuriken.h"
#include "Item.h"
#include "Textbox.h"
#include "BlockAnimation.h"

void playerCollisionItem(Player& vect, Item& Item, Collider col, sf::Vector2f direction);
void platformCollisionShuriken(std::vector<Platform>& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction);
void platformCollisionItem(std::vector<Platform>& vect, Item& Item, Collider col, sf::Vector2f direction);
void playerCollisionShuriken(Player& vect, Shuriken& Shuriken, Collider col, sf::Vector2f direction);
void upDateShuriken(std::vector<Shuriken>& vest, float deltaTime);
void upDateShurikenV2(std::vector<Shuriken>& vest, float deltaTime);
void upDateMagicBall(std::vector<Shuriken>& vest, float deltaTime);
void upDateItem(std::vector<Item>& vest, float deltaTime);
void moveShuriken(std::vector<Shuriken>& vest, sf::Vector2f move, float deltaTime);
void moveShurikenV2(std::vector<Shuriken>& vest, sf::Vector2f move, float deltaTime);
void drawShuriken(std::vector<Shuriken>& vest, sf::RenderWindow& window);
void drawItem(std::vector<Item>& vest, sf::RenderWindow& window);
void printText(sf::Vector2f postiton, std::string message, float size, sf::RenderWindow& window);
void moveMagicBall(std::vector<Shuriken>& vest, float deltaTime);

sf::Vector2f Speed(float time);
void SpeedV2(std::vector<Shuriken>& vest, Player& player);

int points = 0;

int stad = 0;

int shuriken = 0;
int numshuriken = 1;

int shurikenV2 = 0;
int numshurikenV2 = 0;

int magicBall = 0;
int numMagicBall = 0;

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

//sound
bool checkDamage = false;
bool checkDamageSh = false;
bool checkDamageB = false;

int main(){
	bool checkGame = false;
	bool checkMouse = true;
	bool checkEsc = true;
	bool checkPause = false;
	int level = 1;
	int PauseLevel = 0;
	int Pauseimmortal = 0;
	move.x = 400;
	move.y = 200;

	sf::Vector2f playerP;
	//sound
	
	std::vector<BlockAnimation> booms;
	std::vector<BlockAnimation> boomsV2;
	
	sf::Texture boompng;
	sf::Texture boomV2png;
	boompng.loadFromFile("png/effectshuriken.png");
	boomV2png.loadFromFile("png/boom.png");

	sf::SoundBuffer sbDamage;
	sf::Sound sDamage;
	sbDamage.loadFromFile("sound/damage.wav");
	sDamage.setBuffer(sbDamage);
	sDamage.setVolume(5);

	sf::SoundBuffer sbDamageB;
	sf::Sound sDamageB;
	sbDamageB.loadFromFile("sound/damageB.wav");
	sDamageB.setBuffer(sbDamageB);
	sDamageB.setVolume(5);

	sf::SoundBuffer sbDamageSh;
	sf::Sound sDamageSh;
	sbDamageSh.loadFromFile("sound/damageSh.wav");
	sDamageSh.setBuffer(sbDamageSh);
	sDamageSh.setVolume(5);

	sf::SoundBuffer sound1;
	sound1.loadFromFile("sound/sound1.wav");

	sf::Sound sound;
	sound.setBuffer(sound1);
	sound.setVolume(5);
	

	sf::Music musicMenu;
	musicMenu.openFromFile("sound/background.wav");
	musicMenu.setVolume(5);
	musicMenu.setLoop(true);
	musicMenu.play();
	//highscore
	FILE* fp;
	char ch[255];
	int score[6];
	std::string name[6];
	std::vector<std::pair<int, std::string>> userScore;
	name[5] = "-";
	score[5] = 0;
	bool checkHighscore = false;
	fp = fopen("./hi.txt", "r");
	for (int i = 0; i < 5; i++)
	{
		fscanf(fp, "%s", &ch);
		name[i] = ch;
		fscanf(fp, "%d", &score[i]);
		userScore.push_back(std::make_pair(score[i], name[i]));
	}
	userScore.push_back(std::make_pair(score[5], name[5]));
	std::sort(userScore.begin(), userScore.end());
	fclose(fp);

	fp = fopen("./hi.txt", "w");
	for (int i = 5; i >= 0; i--)
	{
		std::strcpy(ch, userScore[i].second.c_str());
		fprintf_s(fp, "%s %d\n", ch, userScore[i].first);
	}
	fclose(fp);
	//manu
	sf::Font fonttast;
	fonttast.loadFromFile("font/Neuterous.otf");

	Textbox ID(70, sf::Color::White, true);
	ID.setFont(fonttast);
	ID.setLimit(true,8);
	
	sf::Texture dz;
	sf::Texture play0png;
	sf::Texture play1png;
	sf::Texture hi0png;
	sf::Texture hi1png;
	sf::Texture tu0png;
	sf::Texture tu1png;
	sf::Texture exit0png;
	sf::Texture exit1png;

	sf::Texture stad5png;
	sf::Texture ok0png;
	sf::Texture ok1png;

	sf::Texture gametupng;
	sf::Texture back0png;
	sf::Texture back1png;

	sf::Texture pausepng;
	sf::Texture restert0png;
	sf::Texture restert1png;
	sf::Texture exm0png;
	sf::Texture exm1png;

	sf::Texture highscorespng;

	sf::Texture gameoverpng;
	sf::Texture reo0png;
	sf::Texture reo1png;
	sf::Texture overtm0png;
	sf::Texture overtm1png;

	gameoverpng.loadFromFile("png/gameover.png");
	reo0png.loadFromFile("png/reo0.png");
	reo1png.loadFromFile("png/reo1.png");
	overtm0png.loadFromFile("png/overtm0.png");
	overtm1png.loadFromFile("png/overtm1.png");

	highscorespng.loadFromFile("png/highscores.png");

	pausepng.loadFromFile("png/pause.png");
	restert0png.loadFromFile("png/restart0.png");
	restert1png.loadFromFile("png/restart1.png");
	exm0png.loadFromFile("png/exm0.png");
	exm1png.loadFromFile("png/exm1.png");

	gametupng.loadFromFile("png/game tu.png");
	back0png.loadFromFile("png/back0.png");
	back1png.loadFromFile("png/back1.png");

	exit0png.loadFromFile("png/exit0.png");
	exit1png.loadFromFile("png/exit1.png");

	tu0png.loadFromFile("png/tu0.png");
	tu1png.loadFromFile("png/tu1.png");

	hi0png.loadFromFile("png/hi0.png");
	hi1png.loadFromFile("png/hi1.png");

	play0png.loadFromFile("png/play0.png");
	play1png.loadFromFile("png/play1.png");

	stad5png.loadFromFile("png/stad5.png");
	ok0png.loadFromFile("png/ok0.png");
	ok1png.loadFromFile("png/ok1.png");

	dz.loadFromFile("png/dz1.png");

	Platform dz1(&dz,sf::Vector2f(1920, 1080.0f), sf::Vector2f(960.0f, 540.0f));

	Platform play0(&play0png, sf::Vector2f(420, 175.0f), sf::Vector2f(960.0f, 435.0f));
	Platform play1(&play1png, sf::Vector2f(420, 175.0f), sf::Vector2f(960.0f, 435.0f));

	Platform hi0(&hi0png, sf::Vector2f(660, 140.0f), sf::Vector2f(960.0f, 585.0f));
	Platform hi1(&hi1png, sf::Vector2f(660, 140.0f), sf::Vector2f(960.0f, 585.0f));

	Platform tu0(&tu0png, sf::Vector2f(700, 140.0f), sf::Vector2f(960.0f, 725.0f));
	Platform tu1(&tu1png, sf::Vector2f(700, 140.0f), sf::Vector2f(960.0f, 725.0f));

	Platform exit0(&exit0png, sf::Vector2f(300, 140.0f), sf::Vector2f(960.0f, 865.0f));
	Platform exit1(&exit1png, sf::Vector2f(300, 140.0f), sf::Vector2f(960.0f, 865.0f));

	Platform gametu(&gametupng, sf::Vector2f(1920, 1080), sf::Vector2f(960,540));
	Platform back0(&back0png, sf::Vector2f(300, 140.0f), sf::Vector2f(1700.0f, 940.0f));
	Platform back1(&back1png, sf::Vector2f(300, 140.0f), sf::Vector2f(1700.0f, 940.0f));

	Platform stad5(&stad5png, sf::Vector2f(1920, 1080.0f), sf::Vector2f(960.0f, 540.0f));
	Platform ok0(&ok0png, sf::Vector2f(250, 184.0f), sf::Vector2f(960.0f, 750.0f));
	Platform ok1(&ok1png, sf::Vector2f(250, 184.0f), sf::Vector2f(960.0f, 750.0f));

	Platform pause(&pausepng, sf::Vector2f(960.0f, 540.0f), sf::Vector2f(960.0f, 540.0f));
	Platform restert0(&restert0png, sf::Vector2f(370.0f, 100.0f), sf::Vector2f(960.0f, 540.0f));
	Platform restert1(&restert1png, sf::Vector2f(370.0f, 100.0f), sf::Vector2f(960.0f, 540.0f));
	Platform exm0(&exm0png, sf::Vector2f(550.0f, 100.0f), sf::Vector2f(960.0f, 660.0f));
	Platform exm1(&exm1png, sf::Vector2f(550.0f, 100.0f), sf::Vector2f(960.0f, 660.0f));
	
	Platform highscores(&highscorespng, sf::Vector2f(960.0f, 800.0f), sf::Vector2f(960.0f, 540.0f));

	Platform gameover(&gameoverpng, sf::Vector2f(960.0f, 740.0f), sf::Vector2f(960.0f, 540.0f));
	Platform reo0(&reo0png, sf::Vector2f(370.0f, 100.0f), sf::Vector2f(960.0f, 640.0f));
	Platform reo1(&reo1png, sf::Vector2f(370.0f, 100.0f), sf::Vector2f(960.0f, 640.0f));
	Platform overtm0(&overtm0png, sf::Vector2f(550.0f, 100.0f), sf::Vector2f(960.0f, 740.0f));
	Platform overtm1(&overtm1png, sf::Vector2f(550.0f, 100.0f), sf::Vector2f(960.0f, 740.0f));

	//vector
	std::vector<Platform> platforms;
	std::vector<Shuriken> shurikens;
	std::vector<Shuriken> shurikenV2s;
	std::vector<Shuriken> magicBalls;
	std::vector<Item> items;

	sf::Vector2f direction;
	//window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Danger Zone", sf::Style::Close | sf::Style::Fullscreen);
	window.setFramerateLimit(144);
	//shape
	sf::RectangleShape bg01(sf::Vector2f(1920, 1080));
	sf::RectangleShape hp(sf::Vector2f(70, 70));
	sf::RectangleShape immAS(sf::Vector2f(220, 220));

	sf::RectangleShape pngPlatforms(sf::Vector2f(1410, 150));
	pngPlatforms.setOrigin(pngPlatforms.getSize() / 2.0f);
	pngPlatforms.setPosition(960, 880);;

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
	sf::Texture rocketpng;

	rocketpng.loadFromFile("png/rocket.png");
	protectpng.loadFromFile("png/protect2.png");
	immortalpng.loadFromFile("png/immortal.png");
	Hppng.loadFromFile("png/heart.png");
	itempng.loadFromFile("png/item.png");
	shurikenpng.loadFromFile("png/shuriken.png");
	bg01png.loadFromFile("png/bg12.jpg");
	platformpng.loadFromFile("png/07.png");
	playepng.loadFromFile("png/player07.png");
	deadpng.loadFromFile("png/dead.png");

	//player
	Player player(&playepng, sf::Vector2u(4, 5), 0.2f, 400.0f);
	sf::RectangleShape shapeDead(sf::Vector2f(210, 170));
	Animation playerdead(&deadpng, sf::Vector2u(4, 1), 0.2f);
	shapeDead.setTexture(&deadpng);

	Animation immAnima(&protectpng, sf::Vector2u(1, 1), 0.2f);

	immAS.setTexture(&protectpng);
	bg01.setTexture(&bg01png);
	hp.setTexture(&Hppng);
	pngPlatforms.setTexture(&platformpng);
	
	hp.setPosition(50, 50);
	platforms.push_back(Platform(&platformpng, sf::Vector2f(1400.0f, 150.0f), sf::Vector2f(960.0f, 880.0f)));
	
	//timeclock

	float deltaTime = 0.0f;
	float shurikenTime = 0.0f;
	float shurikenTimeV2 = 0.0f;
	float timeMagicBall = 0;
	float TimeMove = 0;
	float immortalTime = 0;
	float flashingTime = 0;
	float deadTime = 0;
	float deadImmortalTime = 0;
	float timeGame = 0;
	float timeLevel = 0;
	float timePause = 0;

	sf::Clock clock;
	sf::Clock clockShuriken;
	sf::Clock clockShurikenV2;
	sf::Clock clockMagicBall;
	sf::Clock clockMove;
	sf::Clock clockImmortal;
	sf::Clock clockDeadImmortal;
	sf::Clock clockFlashing;
	sf::Clock clockDead;
	sf::Clock clockGame;
	sf::Clock clockLevel;
	sf::Clock clockPause;


	while (window.isOpen())
	{
		if (checkMouse == false && !(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
		{
			checkMouse = true;
		}
		if (checkEsc == false && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)))
		{
			checkEsc = true;
		}
		//sound
		if (checkDamage)
		{
			sDamage.play();
			checkDamage = false;
		}
		if (checkDamageSh)
		{
			sDamageSh.play();
			checkDamageSh = false;
		}
		if (checkDamageB)
		{
			sDamageB.play();
			checkDamageB = false;
		}
			TimeMoveV2 = clockMoveV2.getElapsedTime().asMilliseconds();

			shurikenTime = clockShuriken.getElapsedTime().asMilliseconds();
			shurikenTimeV2 = clockShurikenV2.getElapsedTime().asMilliseconds();
			timeMagicBall = clockMagicBall.getElapsedTime().asMilliseconds();
			TimeMove = clockMove.getElapsedTime().asMilliseconds();
			deadImmortalTime = clockDeadImmortal.getElapsedTime().asMilliseconds();
			immortalTime = clockImmortal.getElapsedTime().asMilliseconds() + Pauseimmortal;
			flashingTime = clockFlashing.getElapsedTime().asMilliseconds();
			deadTime = clockDead.getElapsedTime().asMilliseconds();
			timeLevel = clockLevel.getElapsedTime().asMilliseconds() + PauseLevel;
			deltaTime = clock.restart().asSeconds();
			if (deltaTime > 1.0f / 20.0f)
				deltaTime = 1.0f / 20.0f;
		
		
			//bg
			
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
				window.close();
				break;

				case sf::Event::TextEntered:
					if (stad == 5)
					{
						ID.typedOn(event);
					}
				
				break;
			}
		}

		if (checkGame)
		{
			sound.setLoop(true);
			sound.play();
			ID.setSelected(true);
			shurikens.erase(shurikens.begin(), shurikens.end());
			shurikenV2s.erase(shurikenV2s.begin(), shurikenV2s.end());
			magicBalls.erase(magicBalls.begin(), magicBalls.end());
			items.erase(items.begin(), items.end());
			level = 0;
			
			points = 0;
			shuriken = 0;
			numshuriken = 1;

			shurikenV2 = 0;
			numshurikenV2 = 0;

			magicBall = 0;
			numMagicBall = 0;

			move.x = 400;
			move.y = 200;

			Hp = 3;
			item = -1;
			checkItme = false;
			immortal = false;
			checkTimeshurikenV2 = false;
			//dead
			dead = 0;
			player.SetPosition(sf::Vector2f(960.0f, 510.0f));

			clockShuriken.restart();
			clockShurikenV2.restart();
			clockMagicBall.restart();
			clockMove.restart();
			clockMoveV2.restart();
			clockImmortal.restart();
			clockDeadImmortal.restart();
			clockDead.restart();
			clockFlashing.restart();
			clockGame.restart();
			clockLevel.restart();

			checkPause = false;
			stad = 1;
			checkGame = false;

		}
		if (stad == 6)
		{
			window.clear(sf::Color::Black);
			gameover.Draw(window);
			reo0.Draw(window);
			if (reo0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				reo1.Draw(window);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
				{
					checkMouse = false;
					checkGame = true;
				}
			}
			overtm0.Draw(window);
			if (overtm0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{

				overtm1.Draw(window);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
				{
					sound.play();
					sound.stop();
					ID.textReSet();
					musicMenu.setLoop(true);
					musicMenu.play();
					checkMouse = false;
					stad = 0;
				}
			}
			
			if(points >= 1000) printText(sf::Vector2f(900, 485), std::to_string(points), 54, window);
			else if (points >= 100) printText(sf::Vector2f(915, 485), std::to_string(points), 54, window);
			else if (points >= 10) printText(sf::Vector2f(930, 485), std::to_string(points), 54, window);
			else printText(sf::Vector2f(945, 485), std::to_string(points), 54, window);
		}
		
		if (stad == 5)
		{
			stad5.Draw(window);
			ok0.Draw(window);
			if (ok0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				ok1.Draw(window);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
				{						
					musicMenu.stop();
					checkMouse = false;
					checkGame = true;
				}
			}
			if (back0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				back1.Draw(window);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
				{
					checkMouse = false;
					stad = 0;
				}
			}
			else
			{
				back0.Draw(window);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				musicMenu.stop();
				checkGame = true;
			}
			ID.setPosition(sf::Vector2f(720, 470));
			ID.drawTo(window);
		}
		
		if (stad == 0)
		{
			window.clear(sf::Color(0, 0, 0));
			dz1.Draw(window);
			if (play0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				play1.Draw(window);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
				{
					checkMouse = false;
					stad = 5;
					//checkHighscore = false;
				}
			}
			else play0.Draw(window);

			if (hi0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				hi1.Draw(window);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
				{
					checkMouse = false;
					stad = 3;
				}
				
			}
			else
			{
				hi0.Draw(window);
			}

			if (tu0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				tu1.Draw(window);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
				{
					checkMouse = false;
					stad = 2;
				}
			}
			else
			{
				tu0.Draw(window);

			}
			if (exit0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				exit1.Draw(window);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
				{
					checkMouse = false;
					window.close();
				}
			}
			else
			{
				exit0.Draw(window);

			}
		}
		if (stad == 2)
		{
			gametu.Draw(window);
			if (back0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				back1.Draw(window);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
				{
					checkMouse = false;
					stad = 0;
				}
			}
			else
			{
				back0.Draw(window);

			}
		}
		if (stad == 3)
		{
			window.clear(sf::Color(0, 0, 0));
			highscores.Draw(window);
			back0.Draw(window);
			if (back0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
			{
				back1.Draw(window);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
				{
					checkMouse = false;
					stad = 0;
				}
			}
		
			printText(sf::Vector2f(710, 330), userScore[5].second, 50, window);
			printText(sf::Vector2f(1110, 330), std::to_string(userScore[5].first), 50, window);
		    printText(sf::Vector2f(710, 445), userScore[4].second, 50, window);
			printText(sf::Vector2f(1110, 445), std::to_string(userScore[4].first), 50, window);
			printText(sf::Vector2f(710, 565), userScore[3].second, 50, window);
			printText(sf::Vector2f(1110, 565), std::to_string(userScore[3].first), 50, window);
			printText(sf::Vector2f(710, 675), userScore[2].second, 50, window);
			printText(sf::Vector2f(1110, 675), std::to_string(userScore[2].first), 50, window);
			printText(sf::Vector2f(710, 790), userScore[1].second, 50, window);
			printText(sf::Vector2f(1110, 790), std::to_string(userScore[1].first), 50, window);

		}
		if (stad == 1)
		{
			
			//bg
			window.draw(bg01);
			//level
			if (checkPause == false)
			{
				if (timeLevel > 8000)
				{
					
					level++;
					clockLevel.restart();
					if (level % 3 == 0)
					{
						numshurikenV2++;
						move.x += 25;
						move.y += 25;
					}
					if (level % 4 == 0)
					{
						numMagicBall++;
					}
					if (level % 5 == 0)
					{
						numshuriken++;
					}
					if (numshurikenV2 >= 6) numshurikenV2 = 6;
					if (numshuriken >= 6) numshuriken = 6;
					PauseLevel = 0;
					clockLevel.restart();
				}
			}
			
			if (checkPause == false)
			{
				upDateItem(items, deltaTime);
				upDateShuriken(shurikens, deltaTime);
				upDateShurikenV2(shurikenV2s, deltaTime);
				upDateMagicBall(magicBalls, deltaTime);
				player.Update(deltaTime);

				SpeedV2(magicBalls, player);
				moveShuriken(shurikens, Speed(TimeMove), deltaTime);
				moveMagicBall(magicBalls,deltaTime);
				moveShurikenV2(shurikenV2s, sf::Vector2f(0, 1500), deltaTime);
			}
			else
			{
				clockShuriken.restart();
				clockShurikenV2.restart();
				clockMagicBall.restart();
				clockMove.restart();
				clockMoveV2.restart();
				clockImmortal.restart();
				clockDeadImmortal.restart();
				clockDead.restart();
				clockFlashing.restart();
				clockGame.restart();
				clockLevel.restart();
			}
			playerdead.Update(0, deltaTime, player.faceRight);
			
			
			int ran = rand() % 3;
			int ranm = 0;
			if (ran == 2) ranm = 150;
			else if (ran == 1) ranm = 0;
			else ranm = -150;
			
			int ranItem = rand() % 1920;

			
			//1
			if (shuriken < numshuriken)
			{
				if (shurikenTime > 750)
				{
					shurikens.push_back(Shuriken(&shurikenpng, sf::Vector2u(8, 1), 0.0001, sf::Vector2f(80, 80), player.GetPosition().x + ranm, sf::Color::Yellow));
					shuriken++;
					points++;
					clockShuriken.restart();
				}
			}
			//2
			if (shurikenTimeV2 > 2000)
			{
				for (int i = 0; i < numshurikenV2; i++)
				{
					shurikenV2s.push_back(Shuriken(&rocketpng, sf::Vector2u(6, 2), 0.01, sf::Vector2f(20, 120), rand() % 1400 + 260, sf::Color::White));
					shurikenV2++;
					points++;
				}
				clockMoveV2.restart();
				clockShurikenV2.restart();
			}
			//3
			if (magicBall < numMagicBall)
			{
				if (timeMagicBall > 500)
				{
					magicBalls.push_back(Shuriken(&shurikenpng, sf::Vector2u(8, 1), 0.0001, sf::Vector2f(80, 80), rand() % 1400 + 260, sf::Color::White));
					magicBall++;
					points++;
					clockMagicBall.restart();
				}
			}
			for (int i = 0; i < shurikens.size(); i++)
			{
				Collider temp = shurikens[i].GetCollider();
				platformCollisionShuriken(platforms, shurikens[i], temp, direction);
				playerCollisionShuriken(player, shurikens[i], temp, direction);
				if(shurikens[i].isDestroy() == true) booms.push_back(BlockAnimation(&boompng, sf::Vector2u(5, 1), 0.1, sf::Vector2f(100, 100), sf::Vector2f(shurikens[i].GetPosition().x, shurikens[i].GetPosition().y+25)));
			}
			for (int i = 0; i < shurikenV2s.size(); i++)
			{
				Collider temp = shurikenV2s[i].GetCollider();
				platformCollisionShuriken(platforms, shurikenV2s[i], temp, direction);
				playerCollisionShuriken(player, shurikenV2s[i], temp, direction);
				if (shurikenV2s[i].isDestroy() == true) boomsV2.push_back(BlockAnimation(&boomV2png, sf::Vector2u(5, 1), 0.1, sf::Vector2f(100, 100), sf::Vector2f(shurikenV2s[i].GetPosition().x, shurikenV2s[i].GetPosition().y+60)));
			}
			
			for (int i = 0; i < magicBalls.size(); i++)
			{
				Collider temp = magicBalls[i].GetCollider();
				platformCollisionShuriken(platforms, magicBalls[i], temp, direction);
				playerCollisionShuriken(player, magicBalls[i], temp, direction);
				if (magicBalls[i].isDestroy() == true) booms.push_back(BlockAnimation(&boompng, sf::Vector2u(5, 1), 0.1, sf::Vector2f(100, 100), sf::Vector2f(magicBalls[i].GetPosition())));
			}
			//TimeRestart
			if (TimeMove > 1500) clockMove.restart();
			if (flashingTime > 300) clockFlashing.restart();
			
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
						if (S.isDestroy() == true) booms.push_back(BlockAnimation(&boompng, sf::Vector2u(5, 1), 0.1, sf::Vector2f(100, 100), sf::Vector2f(S.GetPosition())));
					}
					for (Shuriken& S : shurikenV2s)
					{
						Collider temp = S.GetCollider();
						if (immortalShape.GetCollider().CheckCollision(temp, direction, 1.0f))
							S.setDestroy(true);
						if (S.isDestroy() == true) boomsV2.push_back(BlockAnimation(&boomV2png, sf::Vector2u(5, 1), 0.1, sf::Vector2f(100, 100), sf::Vector2f(S.GetPosition().x, S.GetPosition().y + 60)));
					}
					for (Shuriken& S : magicBalls)
					{
						Collider temp = S.GetCollider();
						if (immortalShape.GetCollider().CheckCollision(temp, direction, 1.0f))
							S.setDestroy(true);
						if (S.isDestroy() == true) booms.push_back(BlockAnimation(&boompng, sf::Vector2u(5, 1), 0.1, sf::Vector2f(100, 100), sf::Vector2f(S.GetPosition())));
					}
					immAnima.Update(0, deltaTime, 1);
					immAS.setPosition(player.GetPosition());
					immAS.setOrigin(110, 110);
					immAS.setTextureRect(immAnima.uvRect);
					if (immortalTime > 3000)
					{
						if (flashingTime > 150) window.draw(immAS);
					}
					else window.draw(immAS);
				}
				else
				{
					Pauseimmortal = 0;
					immortal = false;
				}
			}
			else clockImmortal.restart();
			Collider playerCollision = player.GetCollider();
			Collider playerCollisionBox = player.GetColliderBox();
			for (Platform& platform : platforms)
			{
				if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
				{
					player.OnCollision(direction);
				}
				if (platform.GetCollider().CheckCollision(playerCollisionBox, direction, 1.0f))
				{
					player.OnCollision(direction);
				}
				//platform.Draw(window);
			}

			drawItem(items, window);
			drawShuriken(shurikens, window);
			drawShuriken(shurikenV2s, window);
			drawShuriken(magicBalls, window);
			window.draw(pngPlatforms);
			

			if (dead == 1)
			{
				if (flashingTime > 150) player.Draw(window);
			}
			else if (dead == 0)
			{
				player.Draw(window);
				shapeDead.setPosition(sf::Vector2f(player.GetPosition().x, player.GetPosition().y - 100));
				clockDead.restart();
			}
			else
			{
				if (deadTime > 0)
				{
					 score[5] = points;
					 userScore[0].first = score[5];
					 userScore[0].second = ID.getText();
					 std::sort(userScore.begin(), userScore.end());
					
					 fp = fopen("./hi.txt", "w");
					 for (int i = 5; i >= 0; i--)
					 {
						 std::strcpy(ch, userScore[i].second.c_str());
						 fprintf_s(fp, "%s %d\n", ch, userScore[i].first);
					 }
					 fclose(fp);
					 sound.pause();
					 stad = 6;
					 checkHighscore = false;
				}
				
				shapeDead.setTextureRect(playerdead.uvRect);
				window.draw(shapeDead);
			}
			window.draw(hp);
			//Text
			printText(sf::Vector2f(1600, 20), "SCORE", 40, window);
			printText(sf::Vector2f(1775, 20), std::to_string(points), 40, window);
			printText(sf::Vector2f(150, 50), std::to_string(Hp), 50, window);
			printText(sf::Vector2f(1645, 80), "LEVEL", 28, window);
			printText(sf::Vector2f(1780, 80), std::to_string(level), 28, window);
			if (player.GetPosition().y > 1500)
			{
				score[5] = points;
				userScore[0].first = score[5];
				userScore[0].second = ID.getText();
				std::sort(userScore.begin(), userScore.end());

				fp = fopen("./hi.txt", "w");
				for (int i = 5; i >= 0; i--)
				{
					std::strcpy(ch, userScore[i].second.c_str());
					fprintf_s(fp, "%s %d\n", ch, userScore[i].first);
				}
				fclose(fp);
				sound.pause();
				stad = 6;
			}
			
			if (Hp <= 0)
			{
				checkHighscore = true;
				immortal = false;
				dead = 3;
				
			}
				
			if (checkPause)
			{
				pause.Draw(window);
				restert0.Draw(window);
				if (restert0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{
					restert1.Draw(window);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
					{
						checkMouse = false;
						checkGame = true;
						checkPause = false;
					}
				}
				exm0.Draw(window);
				if (exm0.body.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
				{

					exm1.Draw(window);
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && checkMouse)
					{
						score[5] = points;
						userScore[0].first = score[5];
						userScore[0].second = ID.getText();
						std::sort(userScore.begin(), userScore.end());

						fp = fopen("./hi.txt", "w");
						for (int i = 5; i >= 0; i--)
						{
							std::strcpy(ch, userScore[i].second.c_str());
							fprintf_s(fp, "%s %d\n", ch, userScore[i].first);
						}
						fclose(fp);
						musicMenu.setLoop(true);
						musicMenu.play();
						ID.textReSet();
						sound.play();
						sound.stop();
						checkMouse = false;
						stad = 0;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && checkEsc)
				{
					sound.play();
					checkEsc = false;
					checkPause = false;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) && checkEsc)
			{
				sound.pause();
				PauseLevel = timeLevel;
				Pauseimmortal = immortalTime;
				checkEsc = false;
				checkPause = true;
			}
			for (int i = 0; i < booms.size(); i++)
			{
				booms[i].Updata(deltaTime, window);
				if (booms[i].dead == true) booms.erase(booms.begin() + i);
			}
			for (int i = 0; i < boomsV2.size(); i++)
			{
				boomsV2[i].Updata(deltaTime, window);
				if (boomsV2[i].dead == true) boomsV2.erase(boomsV2.begin() + i);
			}
		}
		if (checkHighscore == false) clockDead.restart();
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}*/
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
void SpeedV2(std::vector<Shuriken>& vest,Player& player)
{
	for (int i = 0; i < vest.size(); i++)
	{
		if (vest[i].GetPosition().x > player.GetPosition().x) vest[i].move.x = -200;
		else if (vest[i].GetPosition().x == player.GetPosition().x) vest[i].move.x = 0;
		else vest[i].move.x = 200;
		vest[i].move.y = 300;
	}
}
void playerCollisionItem(Player& vect, Item& Item, Collider col, sf::Vector2f direction)
{
	int randItem = rand() % 2;
	if (vect.checkS)
	{
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
	else
	{
		if (vect.GetColliderBox().CheckCollision(col, direction, 1.0f))
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
		if (vect.checkS) {
			if (vect.GetCollider().CheckCollision(col, direction, 1.0f))
			{
				checkDamage = true;
				Shuriken.setDestroy(true);
				Hp--;
				dead = 1;
			}
		}
		else
		{
			if (vect.GetColliderBox().CheckCollision(col, direction, 1.0f))
			{
				checkDamage = true;
				Shuriken.setDestroy(true);
				Hp--;
				dead = 1;
			}
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
			checkDamageSh = true;
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
			checkDamageB = true;
			vest.erase(vest.begin() + i);
			shurikenV2--;
		}
	}
}
void upDateMagicBall(std::vector<Shuriken>& vest, float deltaTime)
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
			magicBall--;
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
void moveMagicBall(std::vector<Shuriken>& vest, float deltaTime)
{
	for (int i = 0; i < vest.size();i++)
	{
		vest[i].magicMove(deltaTime);
		if (vest[i].GetPosition().y > 1100)
			vest[i].setDestroy(true);
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
	else
	{
		for (Shuriken& Rocket : vest)
		{
			Rocket.Move(sf::Vector2f(0,90), deltaTime);
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