#pragma once
#include <iostream>
#include<fstream>
#include "Rover.h"
#include "LinkedQueue.h"
#include "Event.h"
#include "Mission.h"
#include "PriorityQueue.h"
using namespace std;


class UI
{
	int Mode;
public:
	UI();
	void SelectMode();
	int SMode();
	void Printmsg(string A);
	void Printint(LinkedQueue<Mission> X, LinkedQueue<Mission> Y);
	void Printint(PQueue<Mission> X, LinkedQueue<Mission> Y);
	void Printint(LinkedQueue<Mission> X);
	void Printint(PQueue<Mission> X);
	void Printint(LinkedQueue<Rover> X, LinkedQueue<Rover> Y);
	void Printint(int x);
	void NewLine();
	void PrintLine();
	void Input();
	void PrintMDetails(LinkedQueue<Mission> Q);
	void PrintMDetails(PQueue<Mission> Q);
	void PrintCDetails(LinkedQueue<Mission> Q);
	void PrintExecutionDetails(PQueue<Mission> Q);//Printing Mission details
	void PrintRDetails(LinkedQueue<Rover> R); // Printing Q details
	void OutputDetails(LinkedQueue<Mission> C, LinkedQueue<Rover> Polar, LinkedQueue<Rover> Emergency);
};
