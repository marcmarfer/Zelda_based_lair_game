#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "FunctionsForGUI.h"
#include "GameContext.h"
#include "Entity.h"
#include "Ocktopus.h"
#include "Character.h"

using namespace std;
using namespace sf;

int main()
{
	//Set a framerate cap
	window.setFramerateLimit(144);
	//window.setMouseCursorVisible(false);
	//window.setMouseCursorGrabbed(true);

	//Set a background
	Texture backgroundTexture;
	loadBackgroundTexture(backgroundTexture);

	Sprite backgroundSprite;
	Vector2u backgroundSize = backgroundTexture.getSize();
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(windowSizeX / 2, windowSizeY / 2);
	backgroundSprite.setOrigin(backgroundSize.x / 2, backgroundSize.y / 2);

	// Set background sprite scale to match the window size
	float backgroundScaleX = (float)windowSizeX / backgroundSize.x;
	float backgroundScaleY = (float)windowSizeY / backgroundSize.y;
	backgroundSprite.setScale(backgroundScaleX, backgroundScaleY);

	//Character settings
	Texture textureUp, textureDown, textureLeft, textureRight, textureStatic, textureAttackingUp, textureAttackingDown, textureAttackingLeft, textureAttackingRight;
	loadCharacterTextures(textureUp, textureDown, textureLeft, textureRight, textureStatic, textureAttackingUp, textureAttackingDown, textureAttackingLeft, textureAttackingRight);

	Sprite character;
	IntRect rectangleForCharacter(0, 0, 64, 64);
	character.setTextureRect(rectangleForCharacter);
	character.setPosition(windowSizeX / 2.f, windowSizeY / 2.f + 200);
	character.setOrigin(rectangleForCharacter.width / 2.f, rectangleForCharacter.height / 2.f);
	character.setScale(4.f, 4.f);
	float movementSpeed = 240.0f;

	FloatRect characterCollisionRect = character.getLocalBounds();
	RectangleShape characterCollisionShape(Vector2f(characterCollisionRect.width, characterCollisionRect.height)); //collision rectangle
	characterCollisionShape.setOrigin(character.getOrigin());
	characterCollisionShape.setPosition(character.getPosition());
	characterCollisionShape.setFillColor(sf::Color::Transparent);
	characterCollisionShape.setOutlineColor(sf::Color::Cyan);
	characterCollisionShape.setOutlineThickness(1);

	//When character is static
	IntRect rectangleForStaticCharacter(0, 0, 64, 64);

	//When character attacks
	IntRect rectangleForAttackingCharacter(0, 0, 64, 64);

	//Ocktopus settings
	Texture textureOcktopus, textureOcktopusRock, textureExplosion, textureNull;
	loadOcktopusTextures(textureOcktopus, textureOcktopusRock, textureExplosion, textureNull);

	Sprite ocktopus;
	IntRect rectangleForOcktopus(0, 0, 100, 100);

	ocktopus.setTextureRect(rectangleForOcktopus);
	ocktopus.setTexture(textureOcktopus);
	ocktopus.setPosition(windowSizeX / 2.f, windowSizeY / 2.f);
	ocktopus.setScale(3.f, 3.f);
	ocktopus.setOrigin(rectangleForOcktopus.width / 2.f, rectangleForOcktopus.height / 2.f);

	FloatRect ocktopusCollisionRect = ocktopus.getLocalBounds();
	float ocktopusRadius = max(ocktopusCollisionRect.width - 10, ocktopusCollisionRect.height - 10) / 2.f; //Adding -15 because when using "intersects" it uses the rectangle based on this radius

	CircleShape ocktopusCollisionShape(ocktopusRadius);
	ocktopusCollisionShape.setOrigin(ocktopusRadius, ocktopusRadius);
	ocktopusCollisionShape.setPosition(ocktopus.getPosition());
	ocktopusCollisionShape.setScale(2.f, 2.f);
	ocktopusCollisionShape.setFillColor(sf::Color::Transparent);
	ocktopusCollisionShape.setOutlineColor(sf::Color::Green);
	ocktopusCollisionShape.setOutlineThickness(1);

	//direction he s looking at
	Vector2f ocktopusDirection;

	//When ocktopus dies
	IntRect rectangleForExplosion(0, 0, 64, 64);

	//ocktopus rock
	Sprite ocktopusRock;
	IntRect rectangleForOcktopusRock(0, 0, 64, 64);

	ocktopusRock.setTextureRect(rectangleForOcktopusRock);
	ocktopusRock.setTexture(textureOcktopusRock);
	ocktopusRock.setPosition(windowSizeX / 2.f, windowSizeY / 2.f);
	ocktopusRock.setScale(1.6f, 1.6f);
	ocktopusRock.setOrigin(rectangleForOcktopusRock.width / 2.f, rectangleForOcktopusRock.height / 2.f);

	FloatRect ocktopusRockCollisionRect = ocktopusRock.getLocalBounds();
	float ocktopusRockRadius = max(ocktopusRockCollisionRect.width - 15, ocktopusRockCollisionRect.height - 15) / 2.f; //Adding -15 because when using "intersects" it uses the rectangle based on this radius

	CircleShape ocktopusRockCollisionShape(ocktopusRockRadius);
	ocktopusRockCollisionShape.setOrigin(ocktopusRockRadius, ocktopusRockRadius);
	ocktopusRockCollisionShape.setPosition(ocktopusRock.getPosition());
	ocktopusRockCollisionShape.setScale(0.7f, 0.7f);
	ocktopusRockCollisionShape.setFillColor(sf::Color::Transparent);
	ocktopusRockCollisionShape.setOutlineColor(sf::Color::Green);
	ocktopusRockCollisionShape.setOutlineThickness(1);

	float rockSpeed = 500.f;

	//Create a font
	Font arialFont;
	if (!arialFont.loadFromFile("arial.ttf"))
	{
		cout << "Error al cargar la fuente arial\n";
		return EXIT_FAILURE;
	}
	Font hyliaSerif;
	if (!hyliaSerif.loadFromFile("HyliaSerif.otf"))
	{
		cout << "Error al cargar la fuente arial\n";
		return EXIT_FAILURE;
	}

	//Create a text for showing the FPS
	Text framesText;
	framesText.setFont(arialFont);
	framesText.setCharacterSize(30);
	framesText.setFillColor(sf::Color::Green);
	framesText.setPosition(50.f, 50.f);

	//Character hp text
	Text characterHpText;
	characterHpText.setFont(arialFont);
	characterHpText.setCharacterSize(25);
	characterHpText.setFillColor(sf::Color::Green);

	//Ocktopus hp text
	Text ocktopusHpText;
	ocktopusHpText.setFont(arialFont);
	ocktopusHpText.setCharacterSize(40);
	ocktopusHpText.setFillColor(sf::Color::Red);
	ocktopusHpText.setPosition(windowSizeX / 2.f - 32, 20.f);

	//Character wins text
	Text characterWinsText;
	characterWinsText.setFont(hyliaSerif);
	characterWinsText.setCharacterSize(80);
	characterWinsText.setFillColor(Color(137, 252, 188));
	characterWinsText.setPosition(250.f, 200.f);

	//Character lost text
	Text characterLostText;
	characterLostText.setFont(hyliaSerif);
	characterLostText.setCharacterSize(80);
	characterLostText.setFillColor(Color(252, 109, 83));
	characterLostText.setPosition(240.f, 200.f);

	//different useful clocks and time objects over the code
	Clock clockForMovement;
	Clock clockForAttacks;
	Clock clockForRockFrames;
	Clock clockForExplosionFrames;
	Clock throwRockTimer;
	Clock clockForDeltaTime;
	Clock collisionBetweenRockAndCharacterTimer;
	Clock collisionBetweenSwordAndOcktopusTimer;
	Clock framesClock;
	Clock clicksClock;
	Time deltaTime;

	//Useful bools for movement control
	bool heroCanMove = true;
	bool characterLookingUp = false;
	bool characterLookingDown = false;
	bool characterLookingLeft = false;
	bool characterLookingRight = false;
	bool collisionRockCharacter = false;
	bool collisionBetweenRockAndCharacterDetected = false;
	bool collisionBetweenSwordAndOcktopusDetected = false;
	bool ocktopusAlive = true;
	bool characterAlive = true;

	//My objects
	Ocktopus ocktopusObject("Ocktopus", 600, 35);
	Character linkObject("Link", 100, 30);

	//Hp bar for the enemy
	RectangleShape hpBarBackground(Vector2f(300.f, 20.f));
	hpBarBackground.setFillColor(sf::Color::Black);
	hpBarBackground.setPosition(windowSizeX / 2 - 150.f, 70.f);

	RectangleShape hpBar(Vector2f(300.f, 20.f));
	hpBar.setFillColor(Color::Red);
	hpBar.setPosition(windowSizeX / 2 - 150.f, 70.f);

	float maxHp = ocktopusObject.getHp();

	while (window.isOpen())
	{
		deltaTime = clockForDeltaTime.restart();
		Event event;

		while (window.pollEvent(event))
		{
			//for closing the screen
			if (event.type == Event::Closed) window.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
		}
		if (ocktopusAlive && characterAlive) {
			ocktopusDirection = Vector2f(ocktopus.getPosition().x - character.getPosition().x, ocktopus.getPosition().y - character.getPosition().y); //distance difference --> Ax - Bx = distance
			handleCharacterMovement(character, textureUp, textureDown, textureLeft, textureRight, textureStatic, heroCanMove, clockForMovement, rectangleForCharacter, rectangleForStaticCharacter, movementSpeed, characterCollisionShape, deltaTime, event, characterLookingUp, characterLookingDown, characterLookingLeft, characterLookingRight);
			handleCharacterAttack(character, textureAttackingUp, textureAttackingDown, textureAttackingLeft, textureAttackingRight, heroCanMove, clicksClock, clockForAttacks, rectangleForAttackingCharacter, event, characterLookingUp, characterLookingDown, characterLookingLeft, characterLookingRight, characterCollisionShape);
			setRotationForOcktopus(ocktopus, ocktopusDirection);
			ocktopusThrowRock(character, ocktopus, ocktopusRock, ocktopusRockCollisionShape, rectangleForOcktopusRock, clockForRockFrames, rockSpeed, ocktopusDirection, throwRockTimer, deltaTime);
			checkCollisionBetweenRockAndCharacter(ocktopusRockCollisionShape, characterCollisionShape);
			ocktopusRockDamage(ocktopusRockCollisionShape, characterCollisionShape, linkObject, ocktopusObject, collisionBetweenRockAndCharacterTimer, collisionBetweenRockAndCharacterDetected);
			checkCollisionBetweenSwordAndOcktopus(ocktopusCollisionShape, characterCollisionShape, heroCanMove);
			characterSwordDamage(ocktopusCollisionShape, characterCollisionShape, linkObject, ocktopusObject, collisionBetweenSwordAndOcktopusTimer, collisionBetweenSwordAndOcktopusDetected, heroCanMove);
		}
		ocktopusDead(ocktopus, ocktopusRock, textureExplosion, textureNull, ocktopusObject, rectangleForExplosion, clockForExplosionFrames, ocktopusAlive);
		characterDead(character, textureExplosion, textureNull, linkObject, rectangleForExplosion, clockForExplosionFrames, characterAlive);

		//if ocktopus or character is -hp, set it to 0
		if (ocktopusObject.getHp() < 0) {
			ocktopusObject.setHp(0);
		}
		if (linkObject.getHp() < 0) {
			linkObject.setHp(0);
		}

		//calc for enemy hp bar
		float hpPercentage = ocktopusObject.getHp() / maxHp; //percentage of hp left
		float hpBarWidth = hpBarBackground.getSize().x * hpPercentage;
		hpBar.setSize(Vector2f(hpBarWidth, hpBar.getSize().y));

		//get frame rate
		int frameRate = 1.0f / framesClock.getElapsedTime().asSeconds();

		//get fps as string to draw them
		string framesToString = to_string(frameRate);
		framesText.setString(framesToString);

		//get character hp as string to draw it
		string characterHpToString = to_string(linkObject.getHp());
		characterHpText.setString(characterHpToString);
		characterHpText.setPosition(character.getPosition().x - 22.5f, character.getPosition().y - 80.f);

		//get ocktopus hp as string to draw it
		string ocktopusHpToString = to_string(ocktopusObject.getHp());
		ocktopusHpText.setString(ocktopusHpToString);

		//character wins message
		string characterWinsTextString = "YOU WON THE FIGHT";
		characterWinsText.setString(characterWinsTextString);

		//character lost message
		string characterLostTextString = "YOU LOST THE FIGHT";
		characterLostText.setString(characterLostTextString);

		framesClock.restart();
		window.clear();
		window.draw(backgroundSprite);
		window.draw(ocktopusRock);
		window.draw(character);
		window.draw(ocktopus);
		//window.draw(characterCollisionShape);
		//window.draw(ocktopusCollisionShape);
		//window.draw(ocktopusRockCollisionShape);
		window.draw(framesText);
		window.draw(characterHpText);
		window.draw(ocktopusHpText);
		window.draw(hpBarBackground);
		window.draw(hpBar);
		if (!characterAlive) {
			window.draw(characterLostText);
		}
		if (!ocktopusAlive) {
			window.draw(characterWinsText);
		}
		window.display();
	}
	return 0;
}