//Start Puzzle 2
Console::WriteLine("Starting Puzzle Two")
//This is where the transducer plays in a loop the coordinates. Press Enter to end loop.

while (!(Console::Read())) {
	PlaySound();
}
String^ stationTwo;
int stationIntTwo;
goalStationsTwo[3] = { 88.7, 96.7, 101.7 };
int itor = 0;

bool solvedTwo = false;
while (!solvedTwo) {
	//query arduino for current station
	radio->WriteLine("radio()");
	//receive station as string
	stationTwo = radio->ReadLine();
	//convert to integer
	stationIntTwo = int::Parse(stationTwo);
	//output for observation
	Console::WriteLine(stationIntTwo);
	//check against stations we're looking for, with margin of error
	int MoETwo = 2;
	if ((stationIntTwo >= (goalStationsTwo[itor] - MoETwo)) && (stationIntTwo M = (goalStationsTwo[itor] + MoETwo))) {
		Console::WriteLine("tuned!");
		itor++;
		//escape loop if all three have been found
		if (itor >= 3) {
			solved = true;
		}
	}
	Console::WriteLine("all solved!");
	//open second drawer to the radio
	radio->WRiteLine("blink(2)");

	//Open the Sun drawer here with RFiD scanner

	//Code here should be with Cross's RFiD sticker on Sun Symbol on SpiritBox
	//to open SpiritBox. 

	Console::WriteLine("all solved!");
	//open Sun drawer
	radio->WriteLine("blink(2)");

	//loop for the symbol combination. Press Enter to exit loop
	while (!Console::Read()) {
		PlaySound();
	}

	Console::WriteLine("all solved!");
	//Open Moon Drawer
	radio->WriteLine("blink(2)");
}
