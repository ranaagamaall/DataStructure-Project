#include <iostream>
#include "Mission.h"
using namespace std;


Mission::Mission()
{
	type = 'X';
	day = 0;
	Location = 0;
	Duration = 0;
	Sig = 0;
	ID = 0;
	CD = 0;
	WD = 0;
	ED = 0;
	FD = 0;
}

Mission::Mission(char T, int d, int L, int Dur, int S, int id)
{
	type=T;
	day = d;
	Location = L;
	Duration = Dur;
	Sig=S*(L/Dur);
	ID = id;
	CD = 0;
	WD = 0;
	ED = 0;
	FD = 0;
	
	R = new Rover; //As not in excution
}

char Mission :: getType()
{
	return type;
}

void Mission::setRover(Rover* r)
{
	R = r;
}

int Mission::getDuration()
{
	return Duration;
}

void Mission :: DecExecutionDays(PQueue<Mission> &M)
{
	PQueue<Mission> Temp;
	while (!M.IsEmpty())
	{
		Mission X;
		M.dequeue(X);

		if (X.getDuration()>0)
			X.Decd();
		Temp.enqueue(X,X.getDuration());
	}

	while (!Temp.IsEmpty())
	{
		Mission X;
		Temp.dequeue(X);
		M.enqueue(X,X.getDuration());
	}
}

void Mission::Decd()
{
	Duration--;
}

Rover* Mission::getRover()
{
	return R;
}

int Mission::getID()
{
	return ID;
}

void Mission::setDuration()
{
	int time;
	time = (25 * Duration) + 2*(Location / R->getSpeed());
	Duration = ceil(time/25);
}

void Mission::setCD(int cd)
{
	CD = cd;
}

void Mission::setWD(int wd)
{
	WD = wd;
}

void Mission::setED(int ed)
{
	ED = ed;
}

void Mission::setFD(int fd)
{
	FD = fd;
}

int Mission::getCD()
{
	return CD;
}

int Mission::getWD()
{
	return WD;
}

int Mission::getED()
{
	return ED;
}

int Mission::getFD()
{
	return FD;
}

int Mission::getDay()
{
	return day;
}

int Mission::getSig()
{
	return Sig;
}

int Mission::getLoc()
{
	return Location;
}

bool Mission::FailedMission(PQueue<Mission>& InE, LinkedQueue<Mission>& FM)
{
	PQueue<Mission> Temp;

	while (!InE.IsEmpty())
	{
		Mission X;
		InE.dequeue(X);

		if (X.getDuration() > 60 || X.getLoc() > 200 * (X.getRover()->getSpeed()))
			FM.enqueue(X);
		else
			Temp.enqueue(X,X.getDuration());
	}

	while (!Temp.IsEmpty())
	{
		Mission X;
		Temp.dequeue(X);
		InE.enqueue(X, X.getDuration());
	}

	if (FM.isEmpty())
		return false;
	else
		return true;
}