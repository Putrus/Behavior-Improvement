#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureManager.h"
class Platform : public sf::Sprite{
private:
protected:
public:
	Platform(std::string name);
};