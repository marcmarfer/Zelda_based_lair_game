#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace std;
using namespace sf;

int windowSizeX = 1280, windowSizeY = 960;
RenderWindow window(VideoMode(windowSizeX, windowSizeY), "The legend of zelda Boss Shelter");