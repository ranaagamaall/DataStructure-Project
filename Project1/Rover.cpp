#include <iostream>
#include "Rover.h"
using namespace std;

Rover::Rover()
{}

Rover::Rover(int C, int S, int id, char T)
{
	checkup = C;
	speed = S;
	type = T;
	ID = id;
	NMission = 0;
	InCheck = 0;
}


void Rover::setNM(int N)
{
	NMission = N;
}

int Rover :: getNM()
{
	return NMission;
}


void Rover::incNM()
{
	NMission++;
}

int Rover::getCheckup()
{
	return checkup;
}

int Rover::getInCheck()
{
	return InCheck;
}
void Rover::incIncheck()
{
	InCheck++;
}

void Rover::incInCheckup(LinkedQueue<Rover>& R)
{
	LinkedQueue<Rover> Temp;
	while (!R.isEmpty())
	{
		Rover X;
		R.dequeue(X);
		X.incIncheck();
		Temp.enqueue(X);
	}

	while (!Temp.isEmpty())
	{
		Rover X;
		Temp.dequeue(X);
		R.enqueue(X);
	}
}

void Rover::setIncheck(int In)
{
	InCheck = In;
}

int Rover::getID()
{
	return ID;
}

char Rover::getType()
{
	return type;
}

int Rover::getSpeed()
{
	return speed;
}

Rover :: ~Rover()
{}