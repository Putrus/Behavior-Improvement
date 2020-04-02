#include "Platform.h"

Platform::Platform(std::string name){
	this->setTexture(*TextureManager::getTexture(name + ".png"));
}