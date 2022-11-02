const int buttonPin = 2;
const int carRedPin = 8;
const int carYellowPin = 12;
const int carGreenPin = 13;
const int peopleRedPin = 4;
const int peopleGreenPin = 7;
const int buzzerPin = 3;

byte reading = LOW;
byte lastReading = LOW;
byte buttonState = LOW;
byte buttonLock = 0;
byte state2Active = 0, state3Active = 0, state4Active = 0;
byte state4LedState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;

int buzzerTone = 1000, blinkingInterval = 500, buzzerInterval, stateDuration;

unsigned long stateTimer = 0, buzzerTimer = 0, blinkingLightTimer = 0, currentTimer;
 
void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(carRedPin, OUTPUT);
  pinMode(carYellowPin, OUTPUT);
  pinMode(carGreenPin, OUTPUT);
  pinMode(peopleRedPin, OUTPUT);
  pinMode(peopleGreenPin, OUTPUT);

}
 
void loop() {
  
  if (state2Active == 0 && state3Active == 0 && state4Active == 0){
    digitalWrite(peopleRedPin, HIGH);
    digitalWrite(carGreenPin, HIGH);
    stateDuration = 8000;
    buzzerInterval = 500;
  }

  if (buttonLock==0) {
    reading = digitalRead(buttonPin);
    stateTimer = millis();
  }
 
  if(reading != lastReading) {
      lastDebounceTime = millis();
  }

  if(millis() - lastDebounceTime > debounceDelay) {
    if(reading != buttonState) {
      buttonState = reading;
      if(buttonState == LOW) {
        buttonLock = 1;
        state2Active = 1;
      }
    }
 
  }
 
  lastReading = reading;
  currentTimer = millis();

  if((currentTimer - stateTimer >= stateDuration) && (state2Active == 1)) {
      if(buttonState == LOW) {
        digitalWrite(carGreenPin, LOW);
        digitalWrite(carYellowPin, HIGH);
        if (currentTimer - stateTimer >= stateDuration + 3000){
          stateTimer = millis();
          state3Active = 1;
          state2Active = 0;
          stateDuration = 8000;
        }

      }
  }

  if(state3Active == 1){
    digitalWrite(peopleRedPin, LOW);
    digitalWrite(carYellowPin, LOW);
    digitalWrite(carRedPin, HIGH);
    digitalWrite(peopleGreenPin, HIGH);
  
    if (currentTimer - buzzerTimer >= buzzerInterval){
      buzzerTimer = millis();
      tone(buzzerPin, buzzerTone, 300);
    }
    if (currentTimer - stateTimer >= stateDuration){
      stateTimer = millis();
      state4Active = 1;
      state3Active = 0;
      stateDuration = 4000;
      buzzerInterval = 200;
    }
  }
  if(state4Active == 1){
  
    if (currentTimer - blinkingLightTimer >= blinkingInterval){
      blinkingLightTimer = millis();
      digitalWrite(peopleGreenPin, state4LedState);
      state4LedState = !state4LedState;
    }
    if (currentTimer - buzzerTimer >= buzzerInterval){
      buzzerTimer = millis();
      tone(buzzerPin, buzzerTone,100);
    }
    if (currentTimer - stateTimer >= stateDuration){
      state4Active = 0;
      buttonLock = 0;
      digitalWrite(carRedPin, LOW);
      digitalWrite(peopleGreenPin, LOW);
    }
  }
  
}
