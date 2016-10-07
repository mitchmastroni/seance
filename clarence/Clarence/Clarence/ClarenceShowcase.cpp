// Clarence.cpp : main project file.

#include "stdafx.h"
#include "Hardware.h"
#include "Radio.h"
#include "fmod_studio.hpp"
#include "fmod_errors.h"
#include <iostream>
#include <Windows.h>
#include <MMSystem.h>

#include <time.h>//for sleep

using namespace System;
using namespace System::IO::Ports;


int main(array<System::String ^> ^args)
{

	String^ response;

	//====================================
	//Setup all Arduino serial connections
	//====================================

	String^ radioPortName;
	String^ piPortName;
	String^ rfidPortName;
	String^ lightsPortName;
	//Fixed baud rates
	int radioBaudRate = 9600;
	int piBaudRate = 115200;
	int rfidBaudRate = 115200;
	int lightsBaudRate = 9600;

	//Ask for port names, then create new port instance
	Console::WriteLine("Type in a port name for the RFID and hit ENTER");
	rfidPortName = Console::ReadLine();
	SerialPort^ rfid;
	rfid = gcnew SerialPort(rfidPortName, rfidBaudRate);
	//Pi time
	Console::WriteLine("Type in a port name for the pi and hit ENTER");
	piPortName = Console::ReadLine();
	SerialPort^ pi;
	pi = gcnew SerialPort(piPortName, piBaudRate);
	//Again
	Console::WriteLine("Type in a port name for the Radio and hit ENTER");
	radioPortName = Console::ReadLine();
	SerialPort^ radio;
	radio = gcnew SerialPort(radioPortName, radioBaudRate);
	//Once More
	Console::WriteLine("Type in a port name for the Lights and hit ENTER");
	lightsPortName = Console::ReadLine();
	SerialPort^ lights;
	lights = gcnew SerialPort(lightsPortName, lightsBaudRate);


	try {
		pi->Open();
		do {
			//Print confirmation message once established
			Console::WriteLine("Pi connection established.");
			//login
			pi->WriteLine("pi");
			pi->WriteLine("raspberry");
			//navigate to directory
			pi->WriteLine("cd ./scripts");
			//turn off screen
			pi->WriteLine("/opt/vc/bin/tvservice -o");
		} while (false);
		// close port to arduino
		pi->Close();
	}
	//Exception handling
	catch (IO::IOException^ e) {
		Console::WriteLine(e->GetType()->Name + ": Port is not ready");
	}
	catch (ArgumentException^ e) {
		Console::WriteLine(e->GetType()->Name + ": incorrect port name syntax, must start with COM/com");
	}

	try {
		lights->Open();
		do {
			lights->WriteLine("towersOn()");
			lights->WriteLine("flickerOn()");
			lights->WriteLine("towersYellow()");
		} while (false);
	}
	//Exception handling
	catch (IO::IOException^ e) {
		Console::WriteLine(e->GetType()->Name + ": Port is not ready");
	}
	catch (ArgumentException^ e) {
		Console::WriteLine(e->GetType()->Name + ": incorrect port name syntax, must start with COM/com");
	}

	//Open port for RFID board
	//Continue once correct tag has been read
	try {
		rfid->Open();
		do {
			//Print confirmation message once established
			Console::WriteLine("Connected to RFiD");
			Console::WriteLine("Game setup ready! Continue?");
			//Wait for user to prompt continue;
			Console::ReadLine();
			//query the arduino to see if a mifare card
			//has been detected
			rfid->WriteLine("mifare()");
			Console::WriteLine("Waiting for blackboard...");
			response = rfid->ReadLine();
		} while (false);
		// close port to arduino
		rfid->Close();
	}
	//Exception handling
	catch (IO::IOException^ e) {
		Console::WriteLine(e->GetType()->Name + ": Port is not ready");
	}
	catch (ArgumentException^ e) {
		Console::WriteLine(e->GetType()->Name + ": incorrect port name syntax, must start with COM/com");
	}

	Console::WriteLine("Clarence detected! Going creepy!");

	lights->WriteLine("towersRed()");


	try {
		radio->Open();
	}
	catch (IO::IOException^ e) {
		Console::WriteLine(e->GetType()->Name + ": Port is not ready");
	}
	catch (ArgumentException^ e) {
		Console::WriteLine(e->GetType()->Name + ": incorrect port name syntax, must start with COM/com");
	}

	radio->WriteLine("on()");


	//Turn on radio music
	//LPWSTR baseFolder = L"C:\\Users\\Mitch\\Documents\\Seance-git\\clarence\\Clarence\\Debug\\";
	PlaySound(L"initiation.wav", NULL, SND_LOOP | SND_ASYNC);
	//variables to hold onto the current station
	String^ station;
	int stationInt = 0;
	//stations that we're looking for, in order
	int goalStations[2] = { 1000, 960 };
	//------------------------||            PUZZLE ONE                ||     PUZZLE TWO A    ||  
	LPCWSTR stationFiles[2] = { L"song1.wav", L"song2.wav" };
	int iter = 0;
	//keep looking for the current station until they're all found
	bool solved = false;
	Console::WriteLine("Hold");
	Console::ReadLine();
	PlaySound(L"song1.wav", NULL, SND_LOOP | SND_ASYNC);
	while (!solved) {
		//store last read station
		int oldStation = stationInt;
		//query arduino for current station
		radio->WriteLine("radio()");
		//receieve station as string
		station = radio->ReadLine();
		//convert to integer
		stationInt = int::Parse(station);
		//if changing, make static
		int MoE = 2;
		if ((stationInt <= (oldStation - MoE)) || (stationInt >= (oldStation + MoE))) {
			PlaySound(L"static.wav", NULL, SND_LOOP | SND_ASYNC);
		}
		if (iter > 0) {
			if ((oldStation != stationInt) && (stationInt >= (goalStations[iter - 1] - MoE)) && (stationInt <= (goalStations[iter - 1] + MoE))) {
				Console::WriteLine("retuned!");
				PlaySound(stationFiles[iter - 1], NULL, SND_LOOP | SND_ASYNC);
			}
		}
		//output for observation
		Console::WriteLine(stationInt);
		//check against stations we're looking for, with margin of error
		if ((stationInt >= (goalStations[iter] - MoE)) && (stationInt <= (goalStations[iter] + MoE))) {
			Console::WriteLine("tuned!");
			PlaySound(stationFiles[iter], NULL, SND_LOOP | SND_ASYNC);
			iter++;
			//escape loop if all three have been found
			if (iter == 2) {
				//open drawer
				radio->WriteLine("open()");
				solved = true;
				station = Console::ReadLine();
				PlaySound(stationFiles[iter], NULL, SND_LOOP | SND_ASYNC);
			}
		}
	}
	Console::WriteLine("all solved!");
	//Open light ports
	try {
		lights->Open();
		do {
			lights->WriteLine("towersYellow()");
		} while (false);
		lights->Close();
	}
	//Exception handling
	catch (IO::IOException^ e) {
		Console::WriteLine(e->GetType()->Name + ": Light port is not ready");
	}
	catch (ArgumentException^ e) {
		Console::WriteLine(e->GetType()->Name + ": incorrect port name syntax for lights, must start with COM/com");
	}

	//RADIO TUNED TO 96.0
	Console::WriteLine("Radio correctly tuned! Going blue!");
	radio->WriteLine("open()");
	lights->WriteLine("towersBlue()");
	lights->WriteLine("flickerOff()");

	Console::WriteLine("Give order one cross drawer is open!");
	Console::Read();

	Console::WriteLine("Perfect! Give order once the tarot puzzle is solved!");
	lights->WriteLine("drop()");
	lights->WriteLine("flickerOn()");

	try {
		rfid->Open();
		do {
			//Print confirmation message once established
			Console::WriteLine("Connected to RFiD");
			Console::WriteLine("Ready for last card, yeah?");
			//Wait for user to prompt continue;
			Console::ReadLine();
			//query the arduino to see if a mifare card
			//has been detected
			rfid->WriteLine("mifare()");
			Console::WriteLine("Waiting for blackboard/card...");
			response = rfid->ReadLine();
		} while (false);
		// close port to arduino
		rfid->Close();
	}
	//Exception handling
	catch (IO::IOException^ e) {
		Console::WriteLine(e->GetType()->Name + ": Port is not ready");
	}
	catch (ArgumentException^ e) {
		Console::WriteLine(e->GetType()->Name + ": incorrect port name syntax, must start with COM/com");
	}



	try {
		pi->Open();
		do {
			//Print confirmation message once established
			Console::WriteLine("Going for pi video!");
			//query the arduino to see if a mifare card
			//has been detected
			pi->WriteLine("bash video");
			Console::WriteLine("fingers crossed");
		} while (false);
		// close port to arduino
		pi->Close();
	}
	//Exception handling
	catch (IO::IOException^ e) {
		Console::WriteLine(e->GetType()->Name + ": Port is not ready");
	}
	catch (ArgumentException^ e) {
		Console::WriteLine(e->GetType()->Name + ": incorrect port name syntax, must start with COM/com");
	}

	// end program
	Console::Write("Press enter to close the program");
	Console::Read();
	return 0;
}
