//DS= [D]ata [S]torage - data
//STCP= [ST]orage [C]lock [P]in latch
//SHCP= [SH]ift register [C]lock [P]in clock

const int latchPin = 11;  // STCP to 12 on Shift Register
const int clockPin = 10;  // SHCP to 11 on Shift Register
const int dataPin = 12;   // DS to 14 on Shift Register

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const byte regSize = 8;  // 1 byte aka 8 bits

int displaySegment[] = {  //vector of segment pins
  segD1, segD2, segD3, segD4
};

int displayDigit[] = {  //vector of the digit for each segment individually
  0, 0, 0, 0
};

const int displayCount = 4;

byte registers[regSize];

const int encodingsNumber = 16;


int encodingArray[encodingsNumber][regSize] = {
  //matrix of encoding for each digit
  { 1, 1, 1, 1, 1, 1, 0, 0 },  // 0 B11111100
  { 0, 1, 1, 0, 0, 0, 0, 0 },  // 1
  { 1, 1, 0, 1, 1, 0, 1, 0 },  // 2
  { 1, 1, 1, 1, 0, 0, 1, 0 },  // 3
  { 0, 1, 1, 0, 0, 1, 1, 0 },  // 4
  { 1, 0, 1, 1, 0, 1, 1, 0 },  // 5
  { 1, 0, 1, 1, 1, 1, 1, 0 },  // 6
  { 1, 1, 1, 0, 0, 0, 0, 0 },  // 7
  { 1, 1, 1, 1, 1, 1, 1, 0 },  // 8
  { 1, 1, 1, 1, 0, 1, 1, 0 },  // 9
  { 1, 1, 1, 0, 1, 1, 1, 0 },  // A
  { 0, 0, 1, 1, 1, 1, 1, 0 },  // b
  { 1, 0, 0, 1, 1, 1, 0, 0 },  // C
  { 0, 1, 1, 1, 1, 0, 1, 0 },  // d
  { 1, 0, 0, 1, 1, 1, 1, 0 },  // E
  { 1, 0, 0, 0, 1, 1, 1, 0 },  // F
};

// joystick pins
const int joyXPin = A0;
const int joyYPin = A1;
const int joySWPin = 2;

const int joyMinThreshold = 400;
const int joyMaxThreshold = 600;

bool joyIsNeutral = true;
byte joySWState = HIGH;

byte joySWReading = HIGH;
byte joySWLastReading = HIGH;

int selectedSegment = 0;  //segment that is being changed
int currentSegment = 0;   //current segment used for multiplexing
int dpState = 0;          //the dp state for main segment

int state2Active = 0;

//button variables

unsigned long blinkTime = 0;
unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;
unsigned long buttonPressTime;
unsigned long stateChangeTime = 0;
unsigned int stateChangeDelay = 400;
unsigned int blinkInterval = 500;
unsigned int continuousButtonPress = 3000;

void setup() {

  // put your setup code here, to run once:
  pinMode(joySWPin, INPUT_PULLUP);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displaySegment[i], OUTPUT);
    digitalWrite(displaySegment[i], LOW);
  }

  Serial.begin(9600);
}

void loop() {

  int joyX = analogRead(joyXPin);  //reading the joystick movements on the X and Y axes
  int joyY = analogRead(joyYPin);

  if (!state2Active) {
    if (joyY > joyMaxThreshold && joyIsNeutral && millis() - stateChangeTime > stateChangeDelay) {  //checking if the joystick moved right on the Y ax
      selectedSegment++;                                                                            //moving the selected segment to the right                              //and checking not to take a double movement
      if (selectedSegment == displayCount) {                                                        //if selected segment is outside of range, moving back to first segment
        selectedSegment = 0;
      }
      joyIsNeutral = false;        //records the fact that the joystick moved
      stateChangeTime = millis();  //resets the timer for when the joystick last moved
    }

    if (joyY < joyMinThreshold && joyIsNeutral && millis() - stateChangeTime > stateChangeDelay) {  //checking if the joystick moved left on the Y ax
      selectedSegment--;                                                                            //moving the selected segment to the left                               //and checking not to take a double movement
      if (selectedSegment == -1) {                                                                  //if selected segment outside of range, moving to the last segment
        selectedSegment = 3;
      }
      joyIsNeutral = false;
      stateChangeTime = millis();
    }
  }

  if (state2Active) {                                                                               //makes sure there is no recorded movement on the X ax during state 2
    if (joyX < joyMinThreshold && joyIsNeutral && millis() - stateChangeTime > stateChangeDelay) {  //checking if the joystick moved downwards on the X ax
      int tempDigit = displayDigit[displayCount - selectedSegment - 1];                             //and checking not to take a double movement
      tempDigit--;                                                                                  //decreasing the digit recorded in the digit vector
      if (tempDigit < 0) {                                                                          //if digit is out of range, moving back to biggest digit
        tempDigit = 15;
      }
      displayDigit[displayCount - selectedSegment - 1] = tempDigit;
      joyIsNeutral = false;
      stateChangeTime = millis();
    }

    if (joyX > joyMaxThreshold && joyIsNeutral && millis() - stateChangeTime > stateChangeDelay) {  //checking if the joystick moved right on the X ax
      int tempDigit = displayDigit[displayCount - selectedSegment - 1];                             //and checking not to take a double movement
      tempDigit++;                                                                                  //increasing the digit recorded in the digit vector
      if (tempDigit > 15) {                                                                         //if digit is out of range, moving back to smallest digit
        tempDigit = 0;
      }
      displayDigit[displayCount - selectedSegment - 1] = tempDigit;
      joyIsNeutral = false;
      stateChangeTime = millis();
    }
  }

  if (joyY <= joyMaxThreshold && joyY >= joyMinThreshold && joyX <= joyMaxThreshold && joyX >= joyMinThreshold) {  //setting the joystick move back to neutral
    joyIsNeutral = true;                                                                                           //waiting for the next move
  }

  joySWReading = digitalRead(joySWPin);    //reading the button press of the joystick
  if (joySWReading != joySWLastReading) {  //checking if the button state changed
    lastDebounceTime = millis();           //starting the timer for the debounce
    if (joySWReading == LOW) {
      buttonPressTime = millis();  //starting the timer for how long the button press is
    }
  }

  if (millis() - lastDebounceTime > debounceDelay) {  //checking the state of the button again after debounce time passed
    if (joySWReading != joySWState) {                 //if the previous button state is different than current button state, button state is changed to current
      joySWState = joySWReading;

      if (joySWState == HIGH) {  //state 2 is activated once button is back to original state
        state2Active = !state2Active;
      }
    }
  }

  if (millis() - buttonPressTime > continuousButtonPress && joySWState == LOW && !state2Active) {  //checking if the button is pressed more than 3 seconds
    for (int i = 0; i < displayCount; i++) {                                                       //
      displayDigit[i] = 0;                                                                         //we are reseting the vector of digits
    }
    selectedSegment = 0;  //setting the selected segment back to the first one
    state2Active = 1;
  }

  if (millis() - blinkTime > blinkInterval && !state2Active && joySWState == HIGH) {  //the state of the blinking dp in state 1 is changed and timer for it is reset
    blinkTime = millis();
    dpState = !dpState;
  }

  if (currentSegment == selectedSegment) {  //checking if the current segment is also the selected segment
    if (!state2Active) {
      writeReg(displayDigit[displayCount - currentSegment - 1], dpState);  //blinking the dp led of the selected segment and writing the digit of the segment if state 2 is not active
    } else {
      writeReg(displayDigit[displayCount - currentSegment - 1], 1);  //keeping the dp led on of the selected segment and writing the digit of the segment if state 2 is active
    }
  } else {
    writeReg(displayDigit[displayCount - currentSegment - 1], 0);  //keeping the dp led inactive when current segment is not the selected segment
  }                                                                //writing the current digit of the segment


  for (int i = 0; i < displayCount; i++) {
    digitalWrite(displaySegment[i], HIGH);  //turning off all the segments
  }

  digitalWrite(displaySegment[displayCount - currentSegment - 1], LOW);  //turning on the current segment

  currentSegment++;                      //moving the current segment to the left
  if (currentSegment >= displayCount) {  //if current segment is outside of range, moving back to the first segment
    currentSegment = 0;
  }
  joySWLastReading = joySWReading;
  delay(5);  //delay for multiplexing
}

void writeReg(int i, int tempDPState) {
  encodingArray[i][7] = tempDPState;  //setting the dp led with the given state
  digitalWrite(latchPin, LOW);

  for (int j = 0; j < regSize; j++) {  // writing the given digit with most significant bit first
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, encodingArray[i][j]);
    digitalWrite(clockPin, HIGH);
  }

  digitalWrite(latchPin, HIGH);
}