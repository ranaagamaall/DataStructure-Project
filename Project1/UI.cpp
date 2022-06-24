#pragma once
#include <iostream>
#include<fstream>
#include "UI.h"
using namespace std;

void UI::PrintMDetails(LinkedQueue<Mission> Q)
{
	Mission x;
	Q.dequeue(x);

	//Fist bracket
	if (x.getType() == 'E')
	{
		cout << "[" << x.getID();
	}
	else if (x.getType() == 'P')
	{
		cout << "(" << x.getID();
	}
	
	//Middle numbers
	while (!Q.isEmpty())
	{
		Mission x;
		Q.dequeue(x);
		cout <<  "," << x.getID();
	}

	//Last bracket 
	if (x.getType() == 'E')
	{
		cout << "]" << " ";
	}
	else if (x.getType() == 'P')
	{
		cout << ")";
	}
}

void UI::PrintMDetails(PQueue<Mission> Q)
{
	Mission x;
	Q.dequeue(x);

	//Fist bracket
	if (x.getType() == 'E')
	{
		cout << "[" << x.getID();
	}
	else if (x.getType() == 'P')
	{
		cout << "(" << x.getID();
	}

	//Middle numbers
	while (!Q.IsEmpty())
	{
		Mission x;
		Q.dequeue(x);
		cout << "," << x.getID();
	}

	//Last bracket 
	if (x.getType() == 'E')
	{
		cout << "]" << " ";
	}
	else if (x.getType() == 'P')
	{
		cout << ")";
	}
}

void UI::Printint(PQueue<Mission> X, LinkedQueue<Mission> Y)
{
	int c1 = 0;
	while (!X.IsEmpty())
	{
		Mission x;
		X.dequeue(x);
		c1++;
	}
	int c2 = 0;
	while (!Y.isEmpty())
	{
		Mission x;
		Y.dequeue(x);
		c2++;
	}

	cout << c1 + c2 << " ";
}

void UI::PrintExecutionDetails(PQueue<Mission> Q)
{
	
	LinkedQueue<Mission> E;
	LinkedQueue<Mission> P;

	while (!Q.IsEmpty())
	{
		Mission x;
		Q.dequeue(x);

		if (x.getType() == 'E')
		{
			E.enqueue(x);
		}	
		else if (x.getType() == 'P')
		{
			P.enqueue(x);
		}
	}


	
	while (!E.isEmpty())
	{
		Mission x;
		E.dequeue(x);
		cout << "[" << x.getID() << "/" << x.getRover()->getID();

		while (!E.isEmpty())
		{
			Mission x;
			E.dequeue(x);
			cout << "," << x.getID() << "/" << x.getRover()->getID();
		}
			
		if (E.isEmpty())
			cout << "]";
	}

	while (!P.isEmpty())
	{
		Mission x;
		P.dequeue(x);
		cout << "(" << x.getID() << "/" << x.getRover()->getID();

		while (!P.isEmpty())
		{
			Mission x;
			P.dequeue(x);
			cout << "," << x.getID() << "/" << x.getRover()->getID();
		}

		if (P.isEmpty())
			cout << ")";
	}
}

void UI::PrintRDetails(LinkedQueue<Rover> R)
{
	Rover x;
	R.dequeue(x);

	//Fist bracket
	if (x.getType() == 'E')
	{
		cout << "[" << x.getID();
	}
	else if (x.getType() == 'P')
	{
		cout << "(" << x.getID();
	}

	//Middle numbers
	while (!R.isEmpty())
	{
		Rover x;
		R.dequeue(x);
		cout << "," << x.getID();
	}

	//Last bracket 
	if (x.getType() == 'E')
	{
		cout << "]" << " ";
	}
	else if (x.getType() == 'P')
	{
		cout << ")";
	}
}


void UI::Printmsg(string A)
{
	cout << A;
}

void UI::Printint(LinkedQueue<Mission> X, LinkedQueue<Mission> Y)
{
	int c1 = 0;
	while (!X.isEmpty())
	{
		Mission x;
		X.dequeue(x);
		c1++;
	}
	int c2 = 0;
	while (!Y.isEmpty())
	{
		Mission x;
		Y.dequeue(x);
		c2++;
	}

	cout << c1+c2 << " ";
}

void UI::Printint(LinkedQueue<Rover> X, LinkedQueue<Rover> Y)
{
	int c1 = 0;
	while (!X.isEmpty())
	{
		Rover x;
		X.dequeue(x);
		c1++;
	}
	int c2 = 0;
	while (!Y.isEmpty())
	{
		Rover x;
		Y.dequeue(x);
		c2++;
	}

	cout << c1 + c2 << " ";
}

void UI::Printint(LinkedQueue<Mission> X)
{
	int c = 0;
	while (!X.isEmpty())
	{
		Mission x;
		X.dequeue(x);
		c++;
	}

	cout << c << " ";
}

void UI::Printint(PQueue<Mission> X)
{
	int c = 0;
	while (!X.IsEmpty())
	{
		Mission x;
		X.dequeue(x);
		c++;
	}

	cout << c << " ";
}

void UI::Printint(int x)
{
	cout << x << " ";
}

void UI::NewLine()
{
	cout << endl;
}

void UI::PrintLine()
{
	cout << endl;
	cout << "-----------------------------------------------------" << endl;
}

void UI::SelectMode()
{
	cout << "Please select your mode:- " << endl;
	cout << "1-Interactive Mode:" << endl;
	cout << "2-Step-By-Step Mode:" << endl;
	cout << "3-Silent Mode:" << endl;
	int x;
	cin >> x;
	while (x > 3 || x < 1)
	{
		cout << "Please chose again (Unavailable choice) : ";
		cin >> x;
		cout << endl;
	}
	Mode = x;
}

UI::UI()
{
	Mode = 0;
}

int UI::SMode()
{
	return Mode;
}

void UI::Input()
{
	cin.ignore();
}

void UI::PrintCDetails(LinkedQueue<Mission> Q)
{
	LinkedQueue<Mission> E;
	LinkedQueue<Mission> P;

	while (!Q.isEmpty())
	{
		Mission x;
		Q.dequeue(x);

		if (x.getType() == 'E')
		{
			E.enqueue(x);
		}
		else if (x.getType() == 'P')
		{
			P.enqueue(x);
		}
	}



	while (!E.isEmpty())
	{
		Mission x;
		E.dequeue(x);
		cout << "[" << x.getID();

		while (!E.isEmpty())
		{
			Mission x;
			E.dequeue(x);
			cout << "," << x.getID();
		}

		if (E.isEmpty())
			cout << "]";
	}

	while (!P.isEmpty())
	{
		Mission x;
		P.dequeue(x);
		cout << "(" << x.getID();

		while (!P.isEmpty())
		{
			Mission x;
			P.dequeue(x);
			cout << "," << x.getID();
		}

		if (P.isEmpty())
			cout << ")";
	}
}

void UI::OutputDetails(LinkedQueue<Mission> C, LinkedQueue<Rover> Polar, LinkedQueue<Rover> Emergency)
{
	ofstream file("../MarsStation.txt", ios::out);

	if (!file)
	{
		cout << "Failed to open file..\n";
		return;
	}

	file << "CD\tID\tFD\tWD\tED\n";
	PQueue<Mission>* Q = new PQueue<Mission>;
	LinkedQueue<Mission>* stat = new LinkedQueue<Mission>;
	while (!C.isEmpty())
	{
		Mission x;
		C.dequeue(x);
		Q->enqueue(x,x.getCD());
	}


	while (!Q->IsEmpty())
	{
		Mission x;
		Q->dequeue(x);
		stat->enqueue(x);

		file << x.getCD() << "      "
			<< x.getID() << "       "
			<< x.getFD() << "       "
			<< x.getWD() << "       " 
			<< x.getED() << "      " << endl;
	}

	file << "-------------------------------------------------" << endl;
	file << "-------------------------------------------------" << endl;
	int P = 0, E = 0;
	float  SumWait = 0, SumExec = 0;

	while (!stat->isEmpty())
	{
		Mission x;
		stat->dequeue(x);

		SumWait += x.getWD();
		SumExec += x.getED();

		if (x.getType() == 'E')
			E++;
		else if (x.getType() == 'P')
			P++;
	}

	int RP = 0, RE = 0;
	while (!Polar.isEmpty())
	{
		Rover r;
		Polar.dequeue(r);
		RP++;
	}
	while (!Emergency.isEmpty())
	{
		Rover r;
		Emergency.dequeue(r);
		RE++;
	}


	file << "Missions: " << P + E << "[P:" << P << ", E:" << E << "]" << endl;
	file << "Rovers: " << RP + RE << "[P:" << RP << ", E:" << RE << "]" << endl;
	file << "Avg Wait =" << SumWait / (P + E) << ", Avg Exec =" << SumExec / (P + E) << endl;
	file.close();
}