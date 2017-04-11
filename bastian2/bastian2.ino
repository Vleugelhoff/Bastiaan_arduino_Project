//the pins used in the program
const int buttonPin1 = 12;     // the number of the pushbutton1 pin -> moving manualy Up
const int buttonPin2 = 11;     // the number of the pushbutton2 pin -> moving manualy Down
const int buttonPin3 = 10;     // for starting test sequence
const int relayPin1 =  8;      // the number of the Realy1 pin Up
const int relayPin2 =  7;      // the number of the Relay2 pin Down
const int sensorPin = A1;      // select the input pin for the linear potentiometer
const int stopPotPin = A2;      // select the input pin for the end point setting potentiometer

// variables will change:
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status
float currentPosition = 350;  //sensor value

boolean Extending = false;
boolean Retracting = false;

//for the time
unsigned long startTime;               // to set the time from starting the measurements (millis)
unsigned long currentTime;             // the currenttime is the millis that the program is running - the start time

void setup() {
  // put your setup code here, to run once:
  //start serial connection
  Serial.begin(9600);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);

  // initialize the relay pin as an output:
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);

  //preset the relays to LOW
  digitalWrite(relayPin1, LOW);
  digitalWrite(relayPin2, LOW);
  
Serial.println("Hello there Dave");
}

void loop() {
  movemanual();
  if (digitalRead(buttonPin3)) {
    startTest();
  }
  idle();
}

void idle(){
  Serial.print("idle ");
  Serial.println(analogRead(sensorPin));
}

void movemanual() {
  //for moving it manually
  while (digitalRead(buttonPin1)) {
    // turn relay1 on:
    digitalWrite(relayPin1, HIGH);
  }
  // When we let go of the button, turn off relay 1the relay
  digitalWrite(relayPin1, LOW);

  while (digitalRead(buttonPin2)) {
    // turn relay2 on:
    digitalWrite(relayPin2, HIGH);
  }
  // When we let go of the button, turn off relay 2the relay
  digitalWrite(relayPin2, LOW);
}

void startTest() {
  //defineer begin
  float startPoint = analogRead(sensorPin);
  //defineer einde
  float stopPoint = analogRead(stopPotPin);

  test(startPoint, stopPoint);
}

void test(float begining, float ending) {

  currentPosition = begining;
  long startTime = millis();

  if (begining <= ending) {
    digitalWrite(relayPin1, HIGH);
    while (currentPosition <= ending || currentTime >= startTime+5000) {
      //define stuff
      currentTime = millis();
      currentPosition = analogRead(sensorPin);
      //say stuff
      Serial.print(currentTime);
      Serial.print(",");
      Serial.println(currentPosition);
    }
    digitalWrite(relayPin1, LOW);
    Serial.println(startTime);
    startTime = millis();
    digitalWrite(relayPin2, HIGH);

    while (currentPosition >= begining ||currentTime >= startTime+5000 ) {
      //define stuff
      currentTime = millis();
      /*currentPosition = analogRead(sensorPin);
      //say stuff
      Serial.print(currentTime);
      Serial.print(",");
      Serial.println(currentPostion);
      */
    }
    digitalWrite(relayPin2, LOW);
  }

  else if (begining >= ending) {
    digitalWrite(relayPin2, HIGH);
    while (ending <= currentPosition || currentTime >= startTime+5000) {
      //define stuff
      currentTime = millis();
      currentPosition = analogRead(sensorPin);
      //say stuff
      Serial.print(currentTime);
      Serial.print(",");
      Serial.println(currentPosition);
    }
    digitalWrite(relayPin2, LOW);
    Serial.println(startTime);
    startTime = millis();
    digitalWrite(relayPin1, HIGH);
    
    while (begining >= currentPosition || currentTime >= startTime+5000) {
      //define stuff
      currentTime = millis();
      /*currentPosition = analogRead(sensorPin);
      //say stuff
      Serial.print(currentTime);
      Serial.print(",");
      Serial.println(currentPostion);
      */
    }
    digitalWrite(relayPin1, LOW);
  }
}

