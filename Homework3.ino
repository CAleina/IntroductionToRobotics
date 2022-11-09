// declare all the segments pins
const int pinA = 4;
byte pinAState = LOW;

const int pinB = 5;
byte pinBState = LOW;

const int pinC = 6;
byte pinCState = LOW;

const int pinD = 7;
byte pinDState = LOW;

const int pinE = 8;
byte pinEState = LOW;

const int pinF = 9;
byte pinFState = LOW;

const int pinG = 10;
byte pinGState = LOW;

const int pinDP = 11;
byte pinDPState = LOW;

bool ledState = LOW;
int currentPin = 7;

const int segSize = 8;
int segments[segSize] = { 
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
int segmentsState[segSize] = { 
  pinAState, pinBState, pinCState, pinDState, pinEState, pinFState, pinGState, pinDPState
};
 
// joystick pins
const int joyXPin = A0;
const int joyYPin = A1;
const int joySWPin = 12;
 
const int joyMinThreshold = 400;
const int joyMaxThreshold = 600;
 
bool joyIsNeutral = true;
byte joySWState = HIGH;

byte joySWReading = HIGH;
byte joySWLastReading = HIGH;


// time variables
unsigned long blinkTime = 0;
unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;
unsigned long buttonPressTime;
unsigned long stateChangeTime = 0;
unsigned int stateChangeDelay = 400;
unsigned int blinkInterval = 200;
unsigned int continuousButtonPress = 3000;

byte state2Active=0;

void setup() {
  Serial.begin(9600);
  // initialize all the pins
  pinMode(joySWPin, INPUT_PULLUP);
  for (int i = 0; i < segSize; i++) {
    pinMode(segments[i], OUTPUT);
  }
}
 
void loop() {
  int joyY = analogRead(joyYPin);   //reading the joystick movements on the X and Y axes
  int joyX = analogRead(joyXPin);

  if(joyX > joyMaxThreshold && joyIsNeutral && millis() - stateChangeTime > stateChangeDelay) {   //checking if the joystick moved upwards on the X ax and checking not to take a double movement
    if(state2Active) {    //change the state of the current led if state 2 is active
      segmentsState[currentPin] = !segmentsState[currentPin];
    }
    digitalWrite(segments[currentPin], segmentsState[currentPin]);    //makes sure the last state of the previous pin remains it's current state after blinking
    if (!state2Active){   //move the led upwards if state 1 is active
      if(currentPin == 1 || currentPin == 5 || currentPin == 6) {
          currentPin = 0;
        }
        else if (currentPin == 2 || currentPin == 3 || currentPin == 4) {
          currentPin = 6;
        }
      ledState = LOW;   //sets blinking led state
    }
  
    joyIsNeutral = false;   //records the fact that the joystick moved
    stateChangeTime = millis();   //resets the timer for when the joystick last moved
  }

  if(joyX < joyMinThreshold && joyIsNeutral && millis() - stateChangeTime > stateChangeDelay) {   //checking if the joystick moved downwards on the X ax and checking not to take a double movement
    if(state2Active) {
      segmentsState[currentPin] = !segmentsState[currentPin];
    }
    digitalWrite(segments[currentPin], segmentsState[currentPin]);
    if (!state2Active){   //move the led downwards if state 1 is active
      if(currentPin == 2 || currentPin == 4 || currentPin == 6) {
          currentPin = 3;
        }
        else if (currentPin == 0 || currentPin == 1 || currentPin == 5) {
          currentPin = 6;
        }    
      ledState = LOW;
    }
    joyIsNeutral = false;
    stateChangeTime = millis();
  }

  if (!state2Active){   //makes sure there is no recorded movement on the Y ax during state 2
    if(joyY < joyMinThreshold && joyIsNeutral && millis() - stateChangeTime > stateChangeDelay) {   //checking if the joystick moved left on the Y ax and checking not to take a double movement
      digitalWrite(segments[currentPin], segmentsState[currentPin]);
      if(currentPin == 0 || currentPin == 1) {    //move the led left if state 1 is active
          currentPin = 5;
        }
        else if (currentPin == 2 || currentPin == 3) {
          currentPin = 4;
        }
        else if (currentPin == 7){
          currentPin = 2;
        }    
      joyIsNeutral = false;
      ledState = LOW;
      stateChangeTime = millis();
    }

    if(joyY > joyMaxThreshold && joyIsNeutral && millis() - stateChangeTime > stateChangeDelay) {   //checking if the joystick moved right on the Y ax and checking not to take a double movement
      digitalWrite(segments[currentPin], segmentsState[currentPin]);
      if(currentPin == 0 || currentPin == 5) {    //move the led right if state 1 is active
          currentPin = 1;
        }
        else if (currentPin == 3 || currentPin == 4) {
          currentPin = 2;
        }
        else if (currentPin == 2){
          currentPin = 7;
        }    
      joyIsNeutral = false;
      ledState = LOW;
      stateChangeTime = millis();
    }
  }

  if (joyY <= joyMaxThreshold && joyY >= joyMinThreshold && joyX <= joyMaxThreshold && joyX >= joyMinThreshold) {   //setting the joystick move back to neutral waiting for the next move
    joyIsNeutral = true;
  }
  
  joySWReading = digitalRead(joySWPin);   //reading the button press of the joystick
  if (joySWReading != joySWLastReading) {   //checking if the button state changed
    lastDebounceTime = millis();    //starting the timer for the debounce
    if (joySWReading == LOW){
      buttonPressTime = millis();   //starting the timer for how long the button press is
    }
  }
  
  if(millis() - lastDebounceTime > debounceDelay){  //checking the state of the button again after debounce time passed
    if(joySWReading != joySWState) {    //if the previous button state is different than current button state, button state is changed to current
      joySWState = joySWReading;

      if(joySWState == HIGH) {    //state 2 is activated once button is back to original state
        digitalWrite(segments[currentPin], segmentsState[currentPin]);
        state2Active = !state2Active;
      }
    }
  }

  if(millis() - buttonPressTime > continuousButtonPress && joySWState==LOW && !state2Active){    //the state of all the leds are reset to original state and current led is the dp led if the button is pressed for 3 seconds straight
    for (int i = 0; i < segSize; i++) {
      digitalWrite(segments[i], LOW);
      segmentsState[i] = LOW;
      }
    currentPin = 7;
    digitalWrite(segments[7], HIGH);
    state2Active = 1;
  }

  if (millis() - blinkTime > blinkInterval && !state2Active && joySWState==HIGH){   //the state of the blinking led in state 1 is changed and timer for it is reset
      blinkTime = millis();
      digitalWrite(segments[currentPin], ledState);
      ledState = !ledState;
  }

  joySWLastReading = joySWReading;
 
}