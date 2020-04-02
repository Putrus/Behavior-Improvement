#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
//zarz¹dza teksturami, trzyma je w map textures
class TextureManager {

private:
	//zaladowane tekstury
	static std::map<std::string, sf::Texture*> textures;
	//kolejnosc do sledzenia tekstur(ich indeksow)
	static std::vector<std::string> texture_order;
	//konstruktor niepotrzebny
	TextureManager();
public:
	//destruktor
	~TextureManager();
	//zwraca ilosc tekstur w textures
	static int getLength();
	//zwraca texture po indeksie
	static sf::Texture * getTexture(int index);
	//zwraca texture po nazwie
	static sf::Texture * getTexture(std::string name);
	//zwraca wskaznik do zaladowanej tekstury
	//jesli nie znajdzie pliku zwraca NULL
	static sf::Texture * loadTexture(std::string name, std::string pathname);
	//wczytanie wszystkich tekstur
	static void loadAllTextures();



};