#pragma once
#include <iostream>
#include<fstream>
#include "Rover.h"
#include "LinkedQueue.h"
#include "Event.h"
#include "Mission.h"
#include "UI.h"
#include<Windows.h>
#include "PriorityQueue.h"
using namespace std;

class MarsStation
{
private:
	LinkedQueue <Rover>* RoverEmergencyList;
	LinkedQueue <Rover>* RoverPolarList;
	LinkedQueue <Event>* EventList;
	PQueue <Mission>* WaitingEmergency;   //Priority Queue Depend on Significance
	LinkedQueue <Mission>* WaitingPolar;
	PQueue<Mission>* InExecution;  //Priority queue depend on least time
	LinkedQueue <Mission>* Completed;
	LinkedQueue <Rover>* CheckPolarList;
	LinkedQueue <Rover>* CheckEmergencyList;
	UI* Out;
	int Cday;
	int NumberOfMissions;
	
	

public:
	MarsStation();
	void ReadData();
	void Body();
	void PrintData();
	void DataOut();
	bool Ended();
	~MarsStation();

};
