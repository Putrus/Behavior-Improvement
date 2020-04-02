#pragma once
#include <ctime>
#include <iostream>
class TimeManager {
private:
	//roznica czasow
	static double timeDifference;
	//stop
	static double stop;
	//animacja nastepna klatka
	static double startNF;
	//przyspieszenie
	static double startAA;


	TimeManager();
protected:
public:
	~TimeManager();
	static bool nextFrame();
	static bool addAcceleration();
};