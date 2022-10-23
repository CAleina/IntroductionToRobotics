const int redPin=9, greenPin=10, bluePin=11;
const int sourceRedPin=A0, sourceGreenPin=A1, sourceBluePin=A2;
int sourceRedValue, sourceGreenValue, sourceBlueValue, minPotVoltage, maxPotVoltage, minLedVoltage, maxLedVoltage;

void setup() {
  pinMode(sourceRedPin, INPUT);
  pinMode(sourceGreenPin, INPUT);
  pinMode(sourceBluePin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  maxPotVoltage = 1023;
  minPotVoltage = 0;
  maxLedVoltage = 255;
  minLedVoltage = 0;
}

void loop() {
  // reading the values from the potentiometer for each of the RGB lights
  sourceRedValue = analogRead(sourceRedPin);
  sourceGreenValue = analogRead(sourceGreenPin);
  sourceBlueValue = analogRead(sourceBluePin);

  // turning the values of the voltage read by the potentiometers (0-1023) to the voltage read by the LEDs (0,255)
  sourceRedValue = map(sourceRedValue, minPotVoltage, maxPotVoltage, minLedVoltage, maxLedVoltage);
  sourceGreenValue = map(sourceGreenValue, minPotVoltage, maxPotVoltage, minLedVoltage, maxLedVoltage);
  sourceBlueValue = map(sourceBlueValue, minPotVoltage, maxPotVoltage, minLedVoltage, maxLedVoltage);
  
  // writing the values converted from the potentiometers to the LEDs, controlling their intensity
  analogWrite(redPin, sourceRedValue);
  analogWrite(greenPin, sourceGreenValue);
  analogWrite(bluePin, sourceBlueValue);


}
