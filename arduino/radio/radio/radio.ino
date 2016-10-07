const int potPin = 2;
const int ledPin = 13;
const int solPin = 12;

void setup() {
  while (!Serial) ;
  // put your setup code here, to run once:
  // Initialize serial communication with computer
  // Rate = 9600 baud
  Serial.begin(9600);
  // LED pin
  pinMode(ledPin, OUTPUT);
  // Solenoid pin
  pinMode(solPin, OUTPUT);
}

void loop() {
  // PARSER
  // Checks if there is a new line to parse
   if (Serial.available() > 0) {
    // Pulls out the function name (everything before the open parenthesis)
    String function = Serial.readStringUntil('(');
    // Pulls out the function value (everything between the parenthesis)
    int val = Serial.readStringUntil(')').toInt();//String valS = Serial.readStringUntil(')');
    // Converts the string into an integer
    //int val = valConverter(valS);
    String newline = Serial.readString();

    // Performs function
    if (function == "double") {
      Serial.println(val * 2);
    } else if (function == "square"){
      Serial.println(val * val);
    } else if (function == "rfid"){
      Serial.println(random(1000,9999));
    } else if (function == "open"){
      digitalWrite(solPin, HIGH);
      delay(300);
      digitalWrite(solPin, LOW);
    } else if (function == "on"){
      //Serial.println("Turning LED on!");
      digitalWrite(ledPin, HIGH);
    } else if (function == "off"){
      //Serial.println("Turning LED off!");
      digitalWrite(ledPin, LOW);
    } else if (function == "blink"){
      //Serial.println("Blinking " + String(val) + " times...");
      for (int i = 0; i < val; i++){
        digitalWrite(ledPin, HIGH);
        delay(500);
        digitalWrite(ledPin, LOW);
        delay(500);
      }
    } else if (function == "radio"){
      unsigned long station = analogRead(potPin);
      // f(x) = a + ((b-a)*(x-min))/(max-min)
      // where min/max are pot reads
      // and a/b are radio stations
      station = 878 + ((1080 - 878)*(station-6))/(647-6);
      Serial.println(String(station));
    }else if (function == "pot"){
      Serial.println(analogRead(potPin));
    } else {
      Serial.println("Error! Command not recognized.");
    }

   }
}

//int valConverter(String valS){
//  int len = valS.length();
//  int newVal = 0;
//  for (int i = 0; i < len; i++){
//    //Serial.print((valS.charAt(i) - '0') * pow(10,(len-i-1)));
//    //Serial.print(" + ");
//    newVal += ((valS.charAt(i) - '0') * pow(10,(len-i-1)));
//  }
//  //Serial.print("= ");
//  //Serial.print(newVal);
//  return newVal;
//}

