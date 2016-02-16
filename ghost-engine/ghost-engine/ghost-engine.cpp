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
	cout << 
};

