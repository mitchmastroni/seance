const int potPin = 2;

void setup() {
  // put your setup code here, to run once:
  // Initialize serial communication with computer
  // Rate = 9600 baud
  Serial.begin(9600);
  // Confirm good connection
  Serial.println("Connected!");
  // LED pin
  pinMode(13, OUTPUT);
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
    } else if (function == "on"){
      Serial.println("Turning LED on!");
      digitalWrite(13, HIGH);
    } else if (function == "off"){
      Serial.println("Turning LED off!");
      digitalWrite(13, LOW);
    } else if (function == "blink"){
      //Serial.println("Blinking " + String(val) + " times...");
      for (int i = 0; i < val; i++){
        digitalWrite(13, HIGH);
        delay(500);
        digitalWrite(13, LOW);
        delay(500);
      }
    } else if (function == "radio"){
      unsigned long station = analogRead(potPin);
      // f(x) = a + ((b-a)*(x-min))/(max-min)
      // where min/max are pot reads
      // and a/b are radio stations
      station = 878 + ((1080 - 878)*(station-6))/(956-6);
      Serial.println(String(station));
    }else{
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

