#pragma once
#include <iostream>
#include "Rover.h"
#include "LinkedQueue.h"
#include "PriorityQueue.h"
using namespace std;


class Mission
{
	
	int day, Location, Duration, Sig, ID;
	char type;
	Rover* R;

	int CD, WD, ED, FD;

	public:
		Mission();
		Mission(char T, int d, int L, int Dur, int S, int id);
		char getType();
		void setRover(Rover* r);
		int getDay();
		int getDuration();
		Rover* getRover();
		void Decd();
		void DecExecutionDays(PQueue<Mission> &M);
		int getID();
		void setDuration();
		int getSig();
		int getLoc();

		void setCD(int cd);
		void setWD(int wd);
		void setED(int ed);
		void setFD(int fd);

		int getCD();
		int getWD();
		int getED();
		int getFD();

		bool FailedMission(PQueue<Mission>& InE, LinkedQueue<Mission>& FM);


};
