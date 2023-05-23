#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Entity.h"
#include "Ocktopus.h"
#include "Character.h"

using namespace std;
using namespace sf;

void loadBackgroundTexture(Texture& backgroundTexture);

void loadCharacterTextures(Texture& textureUp, Texture& textureDown, Texture& textureLeft, Texture& textureRight, Texture& textureStatic, Texture& textureAttackingUp, Texture& textureAttackingDown, Texture& textureAttackingLeft, Texture& textureAttackingRight);

void loadOcktopusTextures(Texture& textureOcktopus, Texture& textureOcktopusRock, Texture& textureExplosion, Texture& textureNull);

void handleCharacterMovement(Sprite& character, Texture& textureUp, Texture& textureDown, Texture& textureLeft, Texture& textureRight, Texture& textureStatic, bool heroCanMove, Clock& clock, IntRect& rectangleForCharacter, IntRect& rectangleForStaticCharacter, float movementSpeed, RectangleShape& characterCollisionShape, const Time& deltaTime, Event event, bool& characterLookingUp, bool& characterLookingDown, bool& characterLookingLeft, bool& characterLookingRight);

void handleCharacterAttack(Sprite& character, Texture& textureAttackingUp, Texture& textureAttackingDown, Texture& textureAttackingLeft, Texture& textureAttackingRight, bool& heroCanMove, Clock& clicksClock, Clock& clockForAttacks, IntRect& rectangleForAttackingCharacter, Event event, bool characterLookingUp, bool characterLookingDown, bool characterLookingLeft, bool characterLookingRight, RectangleShape& characterCollisionShape);

float getOcktopusRotation(Vector2f& ocktopusDirection);

void setRotationForOcktopus(Sprite& ocktopus, Vector2f& ocktopusDirection);

void ocktopusThrowRock(Sprite& character, Sprite& ocktopus, Sprite& ocktopusRock, CircleShape& ocktopusRockCollisionShape, IntRect& rectangleForOcktopusRock, Clock& clockForRockFrames, float rockSpeed, Vector2f& ocktopusDirection, Clock& throwRockTimer, const Time& deltaTime);

bool checkCollisionBetweenRockAndCharacter(CircleShape& ocktopusRockCollisionShape, RectangleShape& characterCollisionShape);

bool checkCollisionBetweenSwordAndOcktopus(CircleShape& ocktopusCollisionShape, RectangleShape& characterCollisionShape, bool heroCanMove);

void ocktopusRockDamage(CircleShape& ocktopusRockCollisionShape, RectangleShape& characterCollisionShape, Character& linkObject, Ocktopus& ocktopusObject, Clock& collisionBetweenRockAndCharacterTimer, bool& collisionBetweenRockAndCharacterDetected);

void characterSwordDamage(CircleShape& ocktopusCollisionShape, RectangleShape& characterCollisionShape, Character& linkObject, Ocktopus& ocktopusObject, Clock& collisionBetweenSwordAndOcktopusTimer, bool& collisionBetweenSwordAndOcktopusDetected, bool heroCanMove);

void ocktopusDead(Sprite& ocktopus, Sprite& ocktopusRock, Texture& textureExplosion, Texture& textureNull, Ocktopus& ocktopusObject, IntRect& rectangleForExplosion, Clock& clockForExplosionFrames, bool& ocktopusAlive);

void characterDead(Sprite& character, Texture& textureExplosion, Texture& textureNull, Character& characterObject, IntRect& rectangleForExplosion, Clock& clockForExplosionFrames, bool& characterAlive);