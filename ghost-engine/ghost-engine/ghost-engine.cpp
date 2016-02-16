// ghost-engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

class Radio {
	bool online, drawer1Open, drawer2Open;
	double station;
  public:
	Radio ();
	bool isOnline ();
	bool drawerStatus (int);
	double tuner ();
	void openDrawer (int);
};

Radio::Radio () {
	online = 1;
	drawer1Open = drawer2Open = 0;
	station = 96.3;
}

bool Radio:: isOnline (){
	return online;
}

bool Radio:: drawerStatus (int drawer){
	if (drawer == 1){
		return drawer1Open;
	}else if (drawer == 2){
		return drawer2Open;
	}else {
		//error
		return 0;
	}
}

double Radio:: tuner (){
	cout << "--arduino.getStation\n";
	while(!(cin >> station)){
		cout << "Bad value!/n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return station;
}

void Radio:: openDrawer (int drawer){
	if (drawer == 1){
		//open drawer 1
		cout << "A drawer on the radio opens, revealing...\n";
		drawer1Open = 1;
		return;
	}else if (drawer == 2){
		//open drawer 2
		cout << "Another drawer on the radio opens, revealing...\n";
		drawer2Open = 1;
		return;
	}else {
		//error
		return;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	clock_t start;
    start = clock();

	Radio radio;

	cout << "Welcome to Seance\n\n";
	//wait
	cout << "The radio crackles to life and begins playing an odd tune...\n";
	bool puzzle1Solved = false;
	double station [3]  = {90.7, 101.7, 99.7};
	for (int i = 0; i < 3; i++){
		bool answer = false;
		while (!answer){
			cout << "waiting for answer...\n";
			double currStation = radio.tuner();
			if (currStation == station[i]){
				answer = true;
			}
		}
		cout << "A new song begins to play...\n";
	}
	radio.openDrawer(1);
	if (radio.drawerStatus(1) == true){
		cout << "...a note and a map.\n";
	} else {
		cout << "Something has gone wrong with Radio Drawer #1.\n";
	}
	bool answer = false;
	int combo = 5489;
	while (!answer){
		cout << "waiting for answer...\n";
		int attempt;
		while(!(cin >> attempt)){
			cout << "Bad value!\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (attempt == combo){
			answer = true;
		}
	}
	"The drawer opens up! It contains pages from the journal.\n";
	cin >> start;
}

