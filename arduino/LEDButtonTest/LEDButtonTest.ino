// Pin setup
const int potPin = 2;    // select the input pin for the potentiometer
const int LEDPin = 13;

// Set initial station and goal station
unsigned long station = 0;
const unsigned long stationGoal[3] = {977, 1017, 997};
int stationIter = 0;


void setup() {
  // Pin setup:
  pinMode(LEDPin, OUTPUT);
  // Open serial connection
  Serial.begin(9600);
  Serial.println("Connected :)");  
}

void loop() {
  // Reads pins, first up, then down
//  if(digitalRead(buttonUpPin) == HIGH){
//    station += 1;
//    Serial.println(stationIntToString(station));
//    while(digitalRead(buttonUpPin) == HIGH){}
//  }else if (digitalRead(buttonDownPin) == HIGH){
//    station -= 1;
//    Serial.println(stationIntToString(station));
//    while(digitalRead(buttonDownPin) == HIGH){}
//  }
  station = analogRead(potPin);
  station = ((station * 173)/1023) + 850;
  Serial.println(stationIntToString(station));
  // Check currently tuned station to that of the goal
  if(station == stationGoal[stationIter]){
    Serial.println("Tuned!");
    //Quick blink when target signal reached
    for (int i = 0; i < 3; i ++){
      digitalWrite(LEDPin, HIGH);
      delay(50);
      digitalWrite(LEDPin, LOW);
      delay(10);
    }
    stationIter++;
  }
 
}

String stationIntToString (unsigned long stationInt){
  String stationString = "";
  stationString += (stationInt/10);
  stationString += ('.');
  stationString += (stationInt%10);
  return stationString;
}

