#pragma once
#include <iostream>
#include "Mission.h"
using namespace std;

class Event
{
	int day, ID;
	Mission M;

public:
	Event();
	Event(int D, int id, char T, int L, int Dur, int S);
	Mission Excute();
	int getDay();
};