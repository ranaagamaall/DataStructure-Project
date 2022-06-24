#pragma once
#include <iostream>
#include "LinkedQueue.h"
using namespace std;

class Rover
{
	int checkup, speed, ID, NMission, InCheck;
	char type;

public:
	Rover();
	Rover(int C, int S, int id, char T);
	void setNM(int N);
	int getNM();
	void incNM();
	int getCheckup();
	int getInCheck();
	void setIncheck(int In);
	void incIncheck();
	void incInCheckup(LinkedQueue<Rover>& R);
	int getID();
	char getType();
	int getSpeed();

	~Rover();
};
