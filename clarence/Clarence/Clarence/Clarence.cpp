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

	Console::WriteLine("Demo version?");
	String^ demo;
	demo = Console::ReadLine();

	try {
		pi->Open();
		do {
			//Print confirmation message once established
			Console::WriteLine("Pi connection established.");
			//login
			//pi->WriteLine("pi");
			//pi->WriteLine("raspberry");
			//navigate to directory
			//pi->WriteLine("cd ./scripts");
			//turn off screen
			pi->WriteLine("/opt/vc/bin/tvservice -o");
		} while (false);
		// close port to arduino
		pi->Close();
	}
	//Exception handling
	catch (IO::IOException^ e) {
		Console::WriteLine(e->GetType()->Name + ": Pi port is not ready");
	}
	catch (ArgumentException^ e) {
		Console::WriteLine(e->GetType()->Name + ": incorrect pi port name syntax, must start with COM/com");
	}

	try {
		lights->Open();
		do {
			lights->WriteLine("towersOn()");
			Console::ReadLine();
			lights->WriteLine("flickerOn()");
			Console::ReadLine();
			lights->WriteLine("towersYellow()");
			Console::ReadLine();
		} while (false);
	}
	//Exception handling
	catch (IO::IOException^ e) {
		Console::WriteLine(e->GetType()->Name + ": Light port is not ready");
	}
	catch (ArgumentException^ e) {
		Console::WriteLine(e->GetType()->Name + ": incorrect light port name syntax, must start with COM/com");
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
	PlaySound(L"initiation.wav", NULL, SND_LOOP | SND_ASYNC);

	Console::WriteLine("Hold");
	Console::ReadLine();

	bool solved = false;


	if (demo != "yes") {

		//Console::WriteLine("Jump to music?");
		////variables to hold onto the current station

		////stations that we're looking for, in order
		//int goalStations[2] = { 666, 960 };
		//LPCWSTR stationFiles[2] = { L"song1.wav", L"song2.wav" };
		//int iter = 0;
		////keep looking for the current station until they're all found
		PlaySound(L"song1mute.wav", NULL, SND_LOOP | SND_ASYNC);

		Console::WriteLine("GO when first door opened");
		Console::ReadLine();

		lights->WriteLine("towersYellow()");

		Console::WriteLine("GO when second door opened");
		Console::ReadLine();
	}
		String^ currStation;
		int currStationInt = 0;
		radio->WriteLine("radio()");
		String^ stationOne = radio->ReadLine();
		int stationOneInt = int::Parse(stationOne);

	

	while (!solved) {
		int oldStationInt = currStationInt;
		//query arduino for current station
		//receieve station as string
		radio->WriteLine("radio()");
		currStation = radio->ReadLine();
		//convert to integer
		currStationInt = int::Parse(currStation);
		//if changing, make static
		int MoE = 3;
		//tuning through static
		if ((currStationInt <= (oldStationInt - MoE)) || (currStationInt >= (oldStationInt + MoE))) {
			PlaySound(L"staticVoice.wav", NULL, SND_LOOP | SND_ASYNC);
		}
		if ((oldStationInt != currStationInt) && (currStationInt >= (stationOneInt - MoE)) && (currStationInt <= (stationOneInt + MoE))) {
			Console::WriteLine("retuned!");
			PlaySound(L"song1.wav", NULL, SND_LOOP | SND_ASYNC);
		}

		//output for observation
		Console::WriteLine(currStationInt);
		////check against stations we're looking for, with margin of error
		if ((currStationInt >= (960 - MoE)) && (currStationInt <= (960 + MoE))) {
			Console::WriteLine("tuned!");
			solved = true;
			radio->WriteLine("open()");
			PlaySound(L"song2.wav", NULL, SND_LOOP | SND_ASYNC);
		}
	}


	//RADIO TUNED TO 96.0
	Console::WriteLine("Radio correctly tuned! Going blue!");
	radio->WriteLine("open()");
	lights->WriteLine("towersBlue()");

	//Console::WriteLine("Give order one cross drawer is open!");
	//Console::ReadLine();

	lights->WriteLine("flickerOff()");

	Console::WriteLine("Perfect! Give order once the tarot puzzle is solved!");
	Console::ReadLine();

	lights->WriteLine("drop()");
	lights->WriteLine("flickerOn()");

	Console::WriteLine("Go when final card place");
	Console::ReadLine();
	radio->WriteLine("off()");
	lights->WriteLine("towersOff()");


	try {
		pi->Open();
		do {
			//Print confirmation message once established
			Console::WriteLine("Going for pi video!");
			//query the arduino to see if a mifare card
			//has been detected
			pi->WriteLine("bash video");
			Console::WriteLine("Enter when done!");
			Console::ReadLine();
			pi->WriteLine("/opt/vc/bin/tvservice -o");
		} while (false);
		// close port to arduino
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


