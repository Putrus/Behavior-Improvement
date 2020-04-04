#include "TextureManager.h"

//niepotrzebny konstruktor
TextureManager::TextureManager()
{
}

//mapa z teksturami
std::map<std::string, sf::Texture*> TextureManager::textures;
//vector kolejnosc tekstur
std::vector<std::string> TextureManager::texture_order;


//zwraca dlugosc mapy textur
int TextureManager::getLength()
{
	return textures.size();
}
//zwraca texture po indeksie
sf::Texture* TextureManager::getTexture(int index)
{
	return getTexture(texture_order.at(index));
}
//zwraca texture po nazwie
sf::Texture* TextureManager::getTexture(std::string name)
{
	if (textures.find(name) != textures.end())
	{
		//std::cout << name << "\n";
		return textures[name];
	}
	else
	{
		return NULL
			;
	}
}

//wczytuje texture i wyrzuca na podstawie nazwy i sciezki(folder w ktorym jest obraz)
sf::Texture* TextureManager::loadTexture(std::string name, std::string pathname)
{
	sf::Texture* texture = new sf::Texture();
	if (texture->loadFromFile(pathname + "/" + name))
	{
		textures[name] = texture;
		texture_order.push_back(name);
		return textures[name];
	}
	else
	{
		delete texture;
		return NULL;
	}
	

}

void TextureManager::loadAllTextures()
{
	std::fstream file("Data/Textures.txt", std::ios::in);
	std::string path, name;
	while (!file.eof())
	{
		file >> path;
		file >> name;
		loadTexture(name + ".png", path);
	}
	file.close();
}


//destruktor
TextureManager::~TextureManager()
{
	sf::Texture* texture;
	std::map<std::string, sf::Texture*>::iterator iterinho = textures.begin();
	while (iterinho != textures.end())
	{
		texture = iterinho->second;
		delete texture;
		iterinho++;
	}
}
