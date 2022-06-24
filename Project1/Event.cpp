#include <iostream>
#include "Event.h"
using namespace std;

Event::Event(int D, int id, char T, int L, int Dur, int S)
	: M(T, D, L, Dur, S, id)
{
	day = D;
	ID = id;
}

Event::Event()
{}

Mission Event :: Excute()
{
	return M;
}

int Event::getDay()
{
	return day;
}