#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include "TextureManager.h"
#include "TimeManager.h"
#include "PhysicsManager.h"

//klasa character, która bêdzie podstaw¹ ka¿dej z postaci istniej¹cej na mapie
class Character
{
private:
	//sprite
	sf::Sprite* sprite;
	//imie potrzebne do wczytywania danych z pliku przez managery
	std::string name;
	//koordynaty do animacji, kazda postac ma inne poniewaz moze akurat stac itp, moze to zmienie
	int animation_x;
	int animation_y;
	//szybkosc x i y
	double speed_x;
	double speed_y;
	//zmienna przechowujaca informacje czy postac jest w powietrzu
	bool in_air;

	//odleglosc od srodka do punktow kolizji postaci
	float bound_x;
	float bound_y;

	//akutalne sciany postaci
	std::vector<float> walls;

protected:
public:
	//konstruktor
	Character(std::string name);
	//wyswietlanie postaci(dana jej klatke)
	void display(sf::RenderWindow& window);
	//animacja postaci w zaleznosci co teraz robi
	void animation();
	//ustawienie pozycji i zwracanie pozycji
	void setPosition(float x, float y);
	sf::Vector2f getPosition();

	//ruch w prawo, w lewo, zostanie w miejscu, skok oraz funckja grawitacji
	void moveRight();
	void moveLeft();
	void stayStill();
	void jump();
	//funkcja grawitacji na podstawie gdzie jest najblizsza podloga
	void gravity();
	//zwrot w prawo lub w lewo
	void turn(bool right);
	//wykonanie ruchu - dodanie speeda do biezacej pozycji
	void move(std::vector<Platform*> *platforms);
	//kontrola postacii przez gracza
	void control();

	//wyliczanie scian
	void calcWalls(std::vector<Platform*> *platforms);
	//sprawdzanie czy jest kolizja miedzy scianami
	void checkCollision();

	void setColor(float r, float g, float b, float a);
};