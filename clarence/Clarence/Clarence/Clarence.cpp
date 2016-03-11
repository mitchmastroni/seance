// Clarence.cpp : main project file.

#include "stdafx.h"
#include "Hardware.h"
#include "Radio.h"
#include "fmod_studio.hpp"
#include "fmod_errors.h"
#include <iostream>
#include <Windows.h>
#include <MMSystem.h>

using namespace System;
using namespace System::IO::Ports;
	

int main(array<System::String ^> ^args)
{
    String^ response;

	//====================================
	//Setup all Arduino serial connections
	//====================================

	String^ radioPortName;
	String^ rfidPortName;
	//Fixed baud rates
	int radioBaudRate = 9600;
	int rfidBaudRate = 115200;

	//Ask for port names, then create new port instance
	Console::WriteLine("Type in a port name for the RFID and hit ENTER");
	rfidPortName=Console::ReadLine();
	SerialPort^ rfid;
	rfid =  gcnew SerialPort(rfidPortName, rfidBaudRate);
	//Again
	Console::WriteLine("Type in a port name for the Radio and hit ENTER");
	radioPortName = Console::ReadLine();
	SerialPort^ radio;
	radio = gcnew SerialPort(radioPortName, radioBaudRate);


	//Open port for RFID board
	//Continue once correct tag has been read
	try { rfid->Open();
		do {
			//Print confirmation message once established
			Console::WriteLine("Connected to RFID. Continue?");
			//Wait for user to prompt continue;
			Console::ReadLine();
			//query the arduino to see if a mifare card
			//has been detected
			rfid->WriteLine("mifare()");
			Console::WriteLine("mifare()");
			response = rfid->ReadLine();
			// print arduino's response to console
			Console::WriteLine("Clarence detected!");
		}while(false);
		// close port to arduino
		rfid->Close();
	} 
	//Exception handling
	catch (IO::IOException^ e  ) { 
		Console::WriteLine(e->GetType()->Name+": Port is not ready");
	} catch (ArgumentException^ e) {
		Console::WriteLine(e->GetType()->Name+": incorrect port name syntax, must start with COM/com");
	}

	//RFID triggered, Seance has begun

	try { radio->Open();
	}
	catch (IO::IOException^ e) {
		Console::WriteLine(e->GetType()->Name + ": Port is not ready");
	}
	catch (ArgumentException^ e) {
		Console::WriteLine(e->GetType()->Name + ": incorrect port name syntax, must start with COM/com");
	}

	//Turn on radio music
	PlaySound(L"C:\\Users\\Mitch\\Documents\\Seance-git\\clarence\\Clarence\\Debug\\music.wav", NULL, SND_LOOP | SND_ASYNC);
	//Puzzle 1
	Console::WriteLine("Starting Puzzle One:");
	//variables to hold onto the current station
	String^ station;
	int stationInt;
	//stations that we're looking for, in order
	int goalStations[3] = { 850, 1017, 899 };
	int iter = 0;
	//keep looking for the current station until they're all found
	bool solved = false;
	while (!solved) {
		//query arduino for current station
		radio->WriteLine("radio()");
		//receieve station as string
		station = radio->ReadLine();
		//convert to integer
		stationInt = int::Parse(station);
		//output for observation
		Console::WriteLine(stationInt);
		//check against stations we're looking for, with margin of error
		int MoE = 2;
		if ((stationInt >= (goalStations[iter] - MoE)) && (stationInt <= (goalStations[iter] + MoE))) {
			Console::WriteLine("tuned!");
			iter++;
			//escape loop if all three have been found
			if (iter >= 3) { solved = true; }
		}
	}
	Console::WriteLine("all solved!");
	//open drawer
	radio->WriteLine("blink(2)");

	// end program
	Console::Write("Press enter to close the program");
	Console::Read();
    return 0;
}
