#include "FunctionsForGUI.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include "Entity.h"
#include "Ocktopus.h"
#include "Character.h"

using namespace std;
using namespace sf;

Vector2f velocity;
bool leftClickRegistered;
float timeBetweenMovingFrames = 0.05f;
float timeBetweenAttackFrames;
float timeBetweenRocks = 2.5f;
float timeBetweenRockFrames = 0.05f;
float timeBetweenExplosionFrames = 0.1f;
float cooldownTime = 0.3f;

void loadBackgroundTexture(Texture& backgroundTexture)
{
	if (!backgroundTexture.loadFromFile("background_texture.jpg")) {
		cout << "Error loading background texture." << endl;
	}
}

void loadCharacterTextures(Texture& textureUp, Texture& textureDown, Texture& textureLeft, Texture& textureRight, Texture& textureStatic, Texture& textureAttackingUp, Texture& textureAttackingDown, Texture& textureAttackingLeft, Texture& textureAttackingRight)
{
	if (!textureUp.loadFromFile("hero_moving_up.png") ||
		!textureDown.loadFromFile("hero_moving_down.png") ||
		!textureLeft.loadFromFile("hero_moving_left.png") ||
		!textureRight.loadFromFile("hero_moving_right.png") ||
		!textureStatic.loadFromFile("hero_static.png")) {
		cout << "Error loading character moving texture/s." << endl;
	}
	if (!textureAttackingUp.loadFromFile("hero_attacking_up.png") ||
		!textureAttackingDown.loadFromFile("hero_attacking_down.png") ||
		!textureAttackingLeft.loadFromFile("hero_attacking_left.png") ||
		!textureAttackingRight.loadFromFile("hero_attacking_right.png")) {
		cout << "Error loading character attacking texture/s." << endl;
	}
}

void loadOcktopusTextures(Texture& textureOcktopus, Texture& textureOcktopusRock, Texture& textureExplosion, Texture& textureNull) {
	if (!textureOcktopus.loadFromFile("Ocktopus.png") ||
		!textureOcktopusRock.loadFromFile("ocktopus_rock.png") ||
		!textureExplosion.loadFromFile("explosion.png") ||
		!textureNull.loadFromFile("null.png")) {
		cout << "Error loading character attacking, explosion or empty texture/s." << endl;
	}
}

void handleCharacterMovement(Sprite& character, Texture& textureUp, Texture& textureDown, Texture& textureLeft, Texture& textureRight, Texture& textureStatic, bool heroCanMove, Clock& clockForMovement, IntRect& rectangleForCharacter, IntRect& rectangleForStaticCharacter, float movementSpeed, RectangleShape& characterCollisionShape, const Time& deltaTime, Event event, bool& characterLookingUp, bool& characterLookingDown, bool& characterLookingLeft, bool& characterLookingRight)
{
	if (heroCanMove) {
		if (Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W))
		{
			characterLookingUp = true;
			characterLookingDown = false;
			characterLookingLeft = false;
			characterLookingRight = false;
			if (character.getPosition().y >= 120) { //32 bc the collision origin is in the center of the character sprite (64x64, so its half)
				character.setTexture(textureUp);
				character.move(0, -movementSpeed * deltaTime.asSeconds());
				characterCollisionShape.move(0, -movementSpeed * deltaTime.asSeconds());
				rectangleForStaticCharacter.left = 0;
				if (clockForMovement.getElapsedTime().asSeconds() > timeBetweenMovingFrames) {
					if (rectangleForCharacter.left == 576) {
						rectangleForCharacter.left = 0;
					}
					else {
						rectangleForCharacter.left += 64;
						character.setTextureRect(rectangleForCharacter);
						clockForMovement.restart();
					}
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S))
		{
			characterLookingDown = true;
			characterLookingUp = false;
			characterLookingLeft = false;
			characterLookingRight = false;
			if (character.getPosition().y <= 790) {
				character.setTexture(textureDown);
				character.move(0, movementSpeed * deltaTime.asSeconds());
				characterCollisionShape.move(0, movementSpeed * deltaTime.asSeconds());
				rectangleForStaticCharacter.left = 64;
				if (clockForMovement.getElapsedTime().asSeconds() > timeBetweenMovingFrames) {
					if (rectangleForCharacter.left == 576) {
						rectangleForCharacter.left = 0;
					}
					else {
						rectangleForCharacter.left += 64;
						character.setTextureRect(rectangleForCharacter);
						clockForMovement.restart();
					}
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A))
		{
			characterLookingLeft = true;
			characterLookingUp = false;
			characterLookingDown = false;
			characterLookingRight = false;
			if (character.getPosition().x >= 150) {
				character.setTexture(textureLeft);
				character.move(-movementSpeed * deltaTime.asSeconds(), 0);
				characterCollisionShape.move(-movementSpeed * deltaTime.asSeconds(), 0);
				rectangleForStaticCharacter.left = 64 * 2;
				if (clockForMovement.getElapsedTime().asSeconds() > timeBetweenMovingFrames) {
					if (rectangleForCharacter.left == 576) {
						rectangleForCharacter.left = 0;
					}
					else {
						rectangleForCharacter.left += 64;
						character.setTextureRect(rectangleForCharacter);
						clockForMovement.restart();
					}
				}
			}
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D))
		{
			characterLookingRight = true;
			characterLookingUp = false;
			characterLookingDown = false;
			characterLookingLeft = false;
			if (character.getPosition().x <= 1130) {
				character.setTexture(textureRight);
				character.move(movementSpeed * deltaTime.asSeconds(), 0);
				characterCollisionShape.move(movementSpeed * deltaTime.asSeconds(), 0);
				rectangleForStaticCharacter.left = 64 * 3; //static position sprite sheet change sprite
				if (clockForMovement.getElapsedTime().asSeconds() > timeBetweenMovingFrames) {
					if (rectangleForCharacter.left == 576) {
						rectangleForCharacter.left = 0;
					}
					else {
						rectangleForCharacter.left += 64;
						character.setTextureRect(rectangleForCharacter);
						clockForMovement.restart();
					}
				}
			}
		}
		else {
			character.setTextureRect(rectangleForStaticCharacter); //putting our sprite on "static mode"
			character.setTexture(textureStatic);
		}
	}
	//cout << (int)character.getPosition().x << " " << (int)character.getPosition().y << endl;
}

void handleCharacterAttack(Sprite& character, Texture& textureAttackingUp, Texture& textureAttackingDown, Texture& textureAttackingLeft, Texture& textureAttackingRight, bool& heroCanMove, Clock& clicksClock, Clock& clockForAttacks, IntRect& rectangleForAttackingCharacter, Event event, bool characterLookingUp, bool characterLookingDown, bool characterLookingLeft, bool characterLookingRight, RectangleShape& characterCollisionShape) {
	timeBetweenAttackFrames = cooldownTime / 3.f;
	if (heroCanMove) {
		if (event.type == Event::MouseButtonPressed) {
			if (event.mouseButton.button == Mouse::Left && !leftClickRegistered) {
				clicksClock.restart();
				clockForAttacks.restart();
				heroCanMove = false;
				leftClickRegistered = true;
			}
		}
		else if (event.type == Event::MouseButtonReleased) {
			if (event.mouseButton.button == Mouse::Left) {
				leftClickRegistered = false;
			}
		}
	}
	if (!heroCanMove) {
		Time elapsedSecondsAfterClick = clicksClock.getElapsedTime();
		Time elapsedSecondsForEachAttackFrame = clockForAttacks.getElapsedTime();
		if (characterLookingUp) {
			character.setTexture(textureAttackingUp);
			characterCollisionShape.setPosition(character.getPosition().x - 10, character.getPosition().y - 45);
			characterCollisionShape.setSize(Vector2f(character.getLocalBounds().width - 20, character.getLocalBounds().height));
		}
		else if (characterLookingDown) {
			character.setTexture(textureAttackingDown);
			characterCollisionShape.setPosition(character.getPosition().x + 30, character.getPosition().y + 45);
			characterCollisionShape.setSize(Vector2f(character.getLocalBounds().width - 20, character.getLocalBounds().height));
		}
		else if (characterLookingLeft) {
			character.setTexture(textureAttackingLeft);
			characterCollisionShape.setPosition(character.getPosition().x - 60, character.getPosition().y + 20);
			characterCollisionShape.setSize(Vector2f(character.getLocalBounds().width, character.getLocalBounds().height - 20));
		}
		else if (characterLookingRight) {
			character.setTexture(textureAttackingRight);
			characterCollisionShape.setPosition(character.getPosition().x + 60, character.getPosition().y + 20);
			characterCollisionShape.setSize(Vector2f(character.getLocalBounds().width, character.getLocalBounds().height - 20));
		}
		else { //if he didnt even moved from spawn --- attack up cause hero is looking up when he spawns
			character.setTexture(textureAttackingUp);
		}
		character.setTextureRect(rectangleForAttackingCharacter);

		if (rectangleForAttackingCharacter.left == 128) {
			rectangleForAttackingCharacter.left = 0;
			clockForAttacks.restart();
		}
		else {
				if (elapsedSecondsForEachAttackFrame.asSeconds() > timeBetweenAttackFrames) {
					rectangleForAttackingCharacter.left += 64;
					clockForAttacks.restart();
					elapsedSecondsForEachAttackFrame = clockForAttacks.getElapsedTime();
				}
		}

		if (elapsedSecondsAfterClick.asSeconds() > cooldownTime) {
			heroCanMove = true;
			characterCollisionShape.setPosition(character.getPosition());
			characterCollisionShape.setSize(Vector2f(character.getLocalBounds().width, character.getLocalBounds().height));
		}
	}
}

float getOcktopusRotation(Vector2f& ocktopusDirection) {
	float rotationAngle = atan2(ocktopusDirection.y, ocktopusDirection.x) * 180 / 3.14159265 + 90.f;
	return rotationAngle;
}

void setRotationForOcktopus(Sprite& ocktopus, Vector2f& ocktopusDirection) {
	ocktopus.setRotation(getOcktopusRotation(ocktopusDirection));
}

void ocktopusThrowRock(Sprite& character, Sprite& ocktopus, Sprite& ocktopusRock, CircleShape& ocktopusRockCollisionShape, IntRect& rectangleForOcktopusRock, Clock& clockForRockFrames, float rockSpeed, Vector2f& ocktopusDirection, Clock& throwRockTimer, const Time& deltaTime) {
	Time throwRockTimerValue = throwRockTimer.getElapsedTime();
	Time elapsedSecondsAfterEachRockFrame = clockForRockFrames.getElapsedTime();
	if (throwRockTimerValue.asSeconds() > timeBetweenRocks) {
		ocktopusRock.setPosition(ocktopus.getPosition());
		ocktopusRockCollisionShape.setPosition(ocktopus.getPosition());
		float distanceBetweenRockAndCharacter = sqrt(pow(ocktopusRock.getPosition().x - character.getPosition().x, 2) + pow(ocktopusRock.getPosition().y - character.getPosition().y, 2)); //Pythagorean theorem (square root of the sum of x^2 + y^2). Using this for getting the distance between both.
		velocity = (ocktopusDirection / distanceBetweenRockAndCharacter) * - rockSpeed;
		throwRockTimer.restart();
	}
	ocktopusRock.move(velocity * deltaTime.asSeconds());
	ocktopusRockCollisionShape.move(velocity * deltaTime.asSeconds());
	
	if (elapsedSecondsAfterEachRockFrame.asSeconds() > timeBetweenRockFrames) {
		if (rectangleForOcktopusRock.left == 192) {
			rectangleForOcktopusRock.left = 0;
		}
		else {
			rectangleForOcktopusRock.left += 64;
			ocktopusRock.setTextureRect(rectangleForOcktopusRock);
			clockForRockFrames.restart();
		}
	}
}

bool checkCollisionBetweenRockAndCharacter(CircleShape& ocktopusRockCollisionShape, RectangleShape& characterCollisionShape) {
	if (ocktopusRockCollisionShape.getGlobalBounds().intersects(characterCollisionShape.getGlobalBounds())) {
		return true;
	}
	return false;
}

bool checkCollisionBetweenSwordAndOcktopus(CircleShape& ocktopusCollisionShape, RectangleShape& characterCollisionShape, bool heroCanMove) {
	if (!heroCanMove && characterCollisionShape.getGlobalBounds().intersects(ocktopusCollisionShape.getGlobalBounds())) {
		return true;
	}
	return false;
}

void ocktopusRockDamage(CircleShape& ocktopusRockCollisionShape, RectangleShape& characterCollisionShape, Character& linkObject, Ocktopus& ocktopusObject, Clock& collisionBetweenRockAndCharacterTimer, bool& collisionBetweenRockAndCharacterDetected) {
	//this time check handles with the multiple collision detections so it only detects it once
	Time elapsedTimeBetweenRockAndCharacterCollision = collisionBetweenRockAndCharacterTimer.getElapsedTime();
	if (checkCollisionBetweenRockAndCharacter(ocktopusRockCollisionShape, characterCollisionShape) && elapsedTimeBetweenRockAndCharacterCollision.asSeconds() >= timeBetweenRocks) {
		linkObject.setHp(linkObject.getHp() - ocktopusObject.getThrowRock());
		collisionBetweenRockAndCharacterDetected = true; 
		collisionBetweenRockAndCharacterTimer.restart();
	}
	else {
		collisionBetweenRockAndCharacterDetected = false;
	}
}

void characterSwordDamage(CircleShape& ocktopusCollisionShape, RectangleShape& characterCollisionShape, Character& linkObject, Ocktopus& ocktopusObject, Clock& collisionBetweenSwordAndOcktopusTimer, bool& collisionBetweenSwordAndOcktopusDetected, bool heroCanMove) {
	//this time check handles with the multiple collision detections so it only detects it once
	Time elapsedTimeBetweenSwordBlowAndOcktopusCollision = collisionBetweenSwordAndOcktopusTimer.getElapsedTime();
	if (checkCollisionBetweenSwordAndOcktopus(ocktopusCollisionShape, characterCollisionShape, heroCanMove) && elapsedTimeBetweenSwordBlowAndOcktopusCollision.asSeconds() >= cooldownTime) {
		ocktopusObject.setHp(ocktopusObject.getHp() - linkObject.getSwordBlow());
		collisionBetweenSwordAndOcktopusDetected = true;
		collisionBetweenSwordAndOcktopusTimer.restart();
	}
	else {
		collisionBetweenSwordAndOcktopusDetected = false;
	}
}

void ocktopusDead(Sprite& ocktopus, Sprite& ocktopusRock, Texture& textureExplosion, Texture& textureNull, Ocktopus& ocktopusObject, IntRect& rectangleForExplosion, Clock& clockForExplosionFrames, bool& ocktopusAlive) {
	Time elapsedSecondsAfterEachExplosionFrame = clockForExplosionFrames.getElapsedTime();
	if (ocktopusObject.getHp() <= 0) {
		ocktopus.setTexture(textureExplosion);
		ocktopus.setRotation(0.0);
		ocktopus.setPosition(690, 480);
		ocktopusRock.setTexture(textureNull);
		ocktopusAlive = false;
		if (elapsedSecondsAfterEachExplosionFrame.asSeconds() > timeBetweenExplosionFrames) {
			if (rectangleForExplosion.left != 576) {
				rectangleForExplosion.left += 64;
				ocktopus.setTextureRect(rectangleForExplosion);
				clockForExplosionFrames.restart();
			}
			else {
				ocktopus.setTexture(textureNull);
			}
		}
	}
}

void characterDead(Sprite& character, Texture& textureExplosion, Texture& textureNull, Character& characterObject, IntRect& rectangleForExplosion, Clock& clockForExplosionFrames, bool& characterAlive) {
	Time elapsedSecondsAfterEachExplosionFrame = clockForExplosionFrames.getElapsedTime();
	if (characterObject.getHp() <= 0) {
		character.setTexture(textureExplosion);
		characterAlive = false;
		if (elapsedSecondsAfterEachExplosionFrame.asSeconds() > timeBetweenExplosionFrames) {
			if (rectangleForExplosion.left != 576) {
				rectangleForExplosion.left += 64;
				character.setTextureRect(rectangleForExplosion);
				clockForExplosionFrames.restart();
			}
			else {
				character.setTexture(textureNull);
			}
		}
	}
}
//Circle shape intersection is not correct at all cause "intersects" uses the global bounds, which gets the properties as if it was a rectangle. To change this 
//I should use a library for pixel perfect collisions or program an intersection for circle-rect collisions