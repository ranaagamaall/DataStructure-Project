#include <iostream>
#include "MarsStation.h"
using namespace std;


MarsStation::MarsStation()
{
	WaitingEmergency = new PQueue<Mission>;
	WaitingPolar = new LinkedQueue<Mission>;
	InExecution = new PQueue<Mission>;
	Completed = new LinkedQueue<Mission>;
	CheckPolarList = new LinkedQueue<Rover>;
	CheckEmergencyList = new LinkedQueue<Rover>;
	RoverPolarList = new LinkedQueue<Rover>;
	RoverEmergencyList = new LinkedQueue<Rover>;
	EventList = new LinkedQueue<Event>;
	Cday = 1;
	Out = new UI;
	int* NumberOfMissions = new int;
}

void MarsStation::ReadData()
{
	fstream file;
	file.open("file.txt");

	int NP, NE; //Number of polar and emergency missions
	file >> NP >> NE;

	Out->Printmsg("Choose normal or advanced rover (1/2)??");

	int RoverSpeed;
	cin >> RoverSpeed;
	int SP, SE; //Speeed of Polar and emergency missions

	if (RoverSpeed == 1)
	{
		file >> SP >> SE;
	}

	int N; //Number of missions till check up
	int CheckP, CheckE;
	file >> N >> CheckP >> CheckE;

	NumberOfMissions = N;
	int RID = 0;


	//making the rover lists
	for (int i = 0; i < NP; i++)
	{
		if (RoverSpeed == 2)
		{ 
			file >> SP;
		}
		Rover Polar(CheckP, SP, RID++,'P');
		RoverPolarList->enqueue(Polar);
	}


	for (int i = 0; i < NE; i++)
	{
		if (RoverSpeed == 2)
		{
			file >> SE;
		}
		Rover Emergency(CheckE, SE, RID++, 'E');
		RoverEmergencyList->enqueue(Emergency);
	}

		////////////////////////////////////////////////////////////////////////////////////////////////

	int EventSize;  //Number of events in the event list
	file >> EventSize;

	for (int i = 0; i < EventSize; i++)  //Forming the event list
	{
		char Type;
		int Day, Id, TLoc, Dur, Sig;
		file >> Type >> Day >> Id >> TLoc >> Dur >> Sig;

		Event E(Day, Id, Type, TLoc, Dur, Sig);
		EventList->enqueue(E);
	}

	file.close();
}


void MarsStation::Body()
{
	Event temp;
	EventList->peek(temp);
	Event E = temp;

	while (Ended())
	{
		/////////////////////////////  Waiting Missions Per Day /////////////////////////////////////
		while (E.getDay() == Cday)
		{
			Mission M = E.Excute();
			if (M.getType() == 'P')
			{
				WaitingPolar->enqueue(M);
			}
			else
			{
				WaitingEmergency->enqueue(M,M.getSig());
			}

			Event X;
			EventList->dequeue(X);
			EventList->peek(temp);
			E = temp;
			if (EventList->isEmpty())
				break;
		}

		//Waiting lists for Emergency and Polar Missions [For each day] + Rover Lists
		///////////////////////////////////// Missions/Rovers In Execution ///////////////////////////////
		while (!WaitingEmergency->IsEmpty())
		{
			if (!RoverEmergencyList->isEmpty())
			{
				Rover* r = new Rover;
				RoverEmergencyList->dequeue(*r);

				Mission ME;
				WaitingEmergency->dequeue(ME);
				ME.setRover(r);
				ME.setDuration();
				ME.setFD(Cday);
				ME.setWD(ME.getFD() - ME.getDay());
				InExecution->enqueue(ME,ME.getDuration());
			}
			else if (!RoverPolarList->isEmpty())
			{
				Rover* r = new Rover;
				RoverPolarList->dequeue(*r);

				Mission ME;
				WaitingEmergency->dequeue(ME);
				ME.setRover(r);
				ME.setDuration();
				ME.setFD(Cday);
				ME.setWD(ME.getFD() - ME.getDay());
				InExecution->enqueue(ME, ME.getDuration());
			}
			else
			{
				break;
			}
		}
		

		while (!WaitingPolar->isEmpty())
		{
			if (!RoverPolarList->isEmpty())
			{
				Rover* r = new Rover;
				RoverPolarList->dequeue(*r);

				Mission ME;
				WaitingPolar->dequeue(ME);
				ME.setRover(r);
				ME.setDuration();
				ME.setFD(Cday);
				ME.setWD(ME.getFD() - ME.getDay());
				InExecution->enqueue(ME, ME.getDuration());
			}
			else
			{
				break;
			}
		}

		/////////////////////////// In-Execution ////////////////////////////////////


		if (!InExecution->IsEmpty())
		{
			//Decrement the inexecution days function in mission list
			Mission D;
			D.DecExecutionDays(*InExecution);
		}

		while (!InExecution->IsEmpty())
		{
			Mission X;
			InExecution->peak(X);
			if (X.getDuration() == 0)
			{
				Mission X;
				InExecution->dequeue(X);
				Rover* R = X.getRover();
				R->incNM();
				if (NumberOfMissions == R->getNM())  //Number of mission done , Number of missions needed
				{
					if (R->getType() == 'P')
					{
						CheckPolarList->enqueue(*R);
					}
					else if (R->getType() == 'E')
					{
						CheckEmergencyList->enqueue(*R);
					}
				}
				else
				{
					if (R->getType() == 'P')
					{
						RoverPolarList->enqueue(*R);
					}
					else if (R->getType() == 'E')
					{
						RoverEmergencyList->enqueue(*R);
					}
				}
				X.setCD(Cday);
				X.setED(X.getCD() - X.getFD());
				Completed->enqueue(X);
			}
			else
			{
				break;
			}
		}


		//////////////////////// Rovers from Check up back to ready ///////////////////////////////
		if (!CheckEmergencyList->isEmpty())
		{
			Rover R;
			R.incInCheckup(*CheckEmergencyList);
		}
		if (!CheckPolarList->isEmpty())
		{
			Rover R;
			R.incInCheckup(*CheckPolarList);
		}
		///// Lists are incremented each day /////

		while (!CheckEmergencyList->isEmpty())
		{
			Rover X;
			CheckEmergencyList->peek(X);
			if (X.getCheckup() == X.getInCheck())
			{
				CheckEmergencyList->dequeue(X);
				X.setIncheck(0);
				RoverEmergencyList->enqueue(X);
			}
			else
			{
				break;
			}
		}

		while (!CheckPolarList->isEmpty())
		{
			Rover X;
			CheckPolarList->peek(X);
			if (X.getCheckup() == X.getInCheck())
			{
				CheckPolarList->dequeue(X);
				X.setIncheck(0);
				RoverPolarList->enqueue(X);
			}
			else
			{
				break;
			}
		}
		///////////////////////////////// Failed Mission ////////////////////////////////////////////////////
		Mission F;
		LinkedQueue<Mission> Failed;
		bool f = F.FailedMission(*InExecution,Failed);
		if (f)
		{
			Out->Printmsg("Failed Mission Detected:");
			Out->PrintMDetails(Failed);
			Out->NewLine();

			Failed.dequeue(F);
			Rover* RF = new Rover;
			RF = F.getRover();
			if (F.getType() == 'P')
				WaitingPolar->enqueue(F);
			else
				WaitingEmergency->enqueue(F,F.getSig());

			if (RF->getType() == 'P')
				CheckPolarList->enqueue(*RF);
			else
				CheckEmergencyList->enqueue(*RF);
		}
		
		if (Cday==200)
		{
			Out->Printmsg("Aborted as mission/s failed due to rover failures");
			return;
		}



		if (EventList->isEmpty() && InExecution->IsEmpty() && CheckPolarList->isEmpty() && CheckEmergencyList->isEmpty() && WaitingEmergency->IsEmpty() && WaitingPolar->isEmpty())
		{
			PrintData();
			return;
		}
		else
			PrintData();
	}
}


void MarsStation::PrintData()
{
	//////////////////////////// Output ////////////////////////////////////	
	if (Cday==1)
		Out->SelectMode();

	if (Out->SMode() == 1 || Out->SMode() == 2)
	{
		Out->Printmsg("Current Day:");
		Out->Printint(Cday);
		Out->NewLine();

		Out->Printint(*WaitingEmergency, *WaitingPolar);
		Out->Printmsg("Waiting Missions:");
		Out->PrintMDetails(*WaitingEmergency);
		Out->PrintMDetails(*WaitingPolar);
		Out->PrintLine();

		Out->Printint(*InExecution);
		Out->Printmsg("In-Execution Missions/Rovers:");
		Out->PrintExecutionDetails(*InExecution);
		Out->PrintLine();

		Out->Printint(*RoverEmergencyList, *RoverPolarList);
		Out->Printmsg("Available Rovers:");
		Out->PrintRDetails(*RoverEmergencyList);
		Out->PrintRDetails(*RoverPolarList);
		Out->PrintLine();

		Out->Printint(*CheckEmergencyList, *CheckPolarList);
		Out->Printmsg("In-Checkup Rovers:");
		Out->PrintRDetails(*CheckEmergencyList);
		Out->PrintRDetails(*CheckPolarList);
		Out->PrintLine();

		Out->Printint(*Completed);
		Out->Printmsg("Completed Missions:");
		Out->PrintCDetails(*Completed);
		Out->PrintLine();

		if (Out->SMode() == 1)
		{
			Out->Printmsg("Please press any char to continue:");
			Out->Input();
			if (Cday == 1)
				cin.ignore();
		}
		else if (Out->SMode() == 2)
		{
			Sleep(1000);
		}

		Out->NewLine();
		Out->NewLine();
	}
	else
	{
		if (!(Cday>1))
			Out->Printmsg("Simulation Starts... Simulation ends, Output file created");
	}
	Cday++;
}

void MarsStation::DataOut()
{
	Out->OutputDetails(*Completed, *RoverPolarList, *RoverEmergencyList);
}

bool MarsStation::Ended()
{
	if (!EventList->isEmpty() || !InExecution->IsEmpty() || !CheckPolarList->isEmpty() || !CheckEmergencyList->isEmpty() || !WaitingEmergency->IsEmpty() || !WaitingPolar->isEmpty())
		return true;

	return false;
}

MarsStation::~MarsStation()
{
	delete WaitingEmergency;
	delete WaitingPolar;
	delete InExecution;
	delete Completed;
	delete CheckPolarList;
	delete CheckEmergencyList;
	delete RoverPolarList;
	delete RoverEmergencyList;
	delete EventList;
	delete Out;
}