// ghost-engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <cstdio>
#include <ctime>

using namespace std;

class Serial {
    private:
        //Connection status
        bool connected;
		char *port;

    public:
        Serial(char *portName);
        ~Serial();
        int ReadData(char *buffer, unsigned int nbChar);
        bool WriteData(char *buffer, unsigned int nbChar);
        bool IsConnected();
};

 Serial::Serial (char *portName) {
	 //dummy announcements
	 cout << "Connecting to port COM-" << portName << "\n";
	 port = portName;
	 connected = true;
	 cout << "Connection successful.\n";
	 return;
 }

 Serial::~Serial () {
	 connected = false;
	 cout << "Disconnected\n";
	 return;
 }

 int Serial::ReadData (char *buffer, unsigned int nbChar) {
	 return 1;
 }

 bool Serial::WriteData(char *buffer, unsigned int nbChar) {
	 cout << buffer << "\n";
	 return true;
 }

 class MCHardware {
  protected:
	 bool connected;
  public:
	bool connect (int);
	bool isConnected ();
 };

 bool MCHardware::connect (int port){
	 //initialize connection at COM-port
	 return connected;
 }

 bool MCHardware::isConnected (){
	return connected;
}

class Radio: public MCHardware {
	bool drawers[2];
	double station;
  public:
	Radio ();
	bool drawerStatus (int);
	double tuner ();
	void openDrawer (int);
};

Radio::Radio () {
	connected = 1;
	drawers[0] = drawers[1] = false;
	//These two values are arbitrary
	station = 96.3;
	Serial radioSerial("3");
}

bool Radio:: drawerStatus (int drawer){
	if (drawer > 2){
		//error
	}else {
		return drawers[drawer+1];
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
	if (drawer == 1 || drawer == 2){
		//open drawer
		drawers[drawer+1] = true;
		cout << "A drawer on the radio opens, revealing...\n";
		return;
	}else {
		//error
		return;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "Welcome to Seance\n\n";

	Radio radio;
	//Begin radio puzzle
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
	int wait;
	cin >> wait;
}

