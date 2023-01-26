#pragma once
#include "SFML/Graphics.hpp"
#include <string>


const int basicX = 606;
const int basicY = 402;
const int stepY = 40;
const size_t hardStep = 4;
const size_t easyMaxSequence = 10;
const size_t mediumMaxSequence = 20;
const size_t hardMaxSequence = 40;

const size_t gamesButtonsNumMax = 6;
const size_t gamesButtonsNumMin = 4;
const sf::Vector2f circlePos(396, 90);
const sf::Vector2f pausePos(82, 65);
const std::string pausePath = "images/field/pause.png";

const int width = 1728;
const int height = 1117;
const std::string selectedButtonsMainMenuPath = "images/buttons/pressed/Frame ";
const std::string notSelectedButtonsMainMenuPath = "images/buttons/unpressed/Frame ";
const sf::Vector2f start(basicX,basicY);
const std::string photoFormat = ".png";
const std::string background = "images/MainMenu" + photoFormat; 

const std::string difficultsBackground = "images/Difficulties/background" + photoFormat;
const std::string difficultsSelectedButtonsPath = "images/Difficulties/buttons/pressed/Frame ";
const std::string difficultsNotSelectedButtonsPath = "images/Difficulties/buttons/unpressed/Frame ";


const std::string gamesBackground = "images/field/field" + photoFormat;
const std::string gamesSelectedButtonsPath = "images/field/buttons/pressed/Frame ";
const std::string gamesNotSelectedButtonsPath = "images/field/buttons/unpressed/Frame ";
const std::string circlePath = "images/field/circle" + photoFormat;

const std::string soundFormat = ".ogg";
const std::string soundGamesButton = "sound/GameButtons/sound ";

const std::string winerSound = "sound/win" + soundFormat;

const std::string goodSign = "images/field/good" + photoFormat;
const std::string badSign = "images/field/bad" + photoFormat;


const sf::Vector2f pausesButtonsStart(basicX,141);
const std::string pauseBackground = "images/pause/background" + photoFormat;
const std::string pauseSelectedButtonsPath = "images/pause/buttons/pressed/Frame ";
const std::string pauseNotSelectedButtonsPath = "images/pause/buttons/unpressed/Frame ";