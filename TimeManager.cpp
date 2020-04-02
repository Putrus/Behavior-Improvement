#include "TimeManager.h"
TimeManager::TimeManager()
{
}
double TimeManager::timeDifference;
double TimeManager::stop;




double TimeManager::startNF = clock();
double TimeManager::startAA = clock();






bool TimeManager::nextFrame()
{
	stop = clock();
	timeDifference = (double)(stop - startNF) / CLOCKS_PER_SEC;
	if (timeDifference > 0.08)
	{
		startNF = clock();
		return true;
	}
	return false;
}
bool TimeManager::addAcceleration()
{
	stop = clock();
	timeDifference = (double)(stop - startAA) / CLOCKS_PER_SEC;
	if (timeDifference > 0.01)
	{
		startAA = clock();
		return true;
	}
	return false;
}

TimeManager::~TimeManager() {

}