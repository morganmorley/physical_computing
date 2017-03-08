/*
  AnalogReadSerial
  Reads an analog input on pin 0, prints the result to the serial monitor.
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.
*/

int LEDPin = 13;
int pulsePin = 0;
int switchPin_1 = 3;
int switchPin_2 = 4;
int photoPin = 6;
float pulseHistory[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float pulse = 0;
int repeatCount = 19;
int switchValue_1 = 0;
int switchValue_2 = 0; 

// the setup routine runs once when you press reset:
void setup() 
{
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);
}

// the loop routine runs over and over again forever:
void loop() 
{
  // read the input on digital pins 3 and 4:
  switchValue_1 = digitalRead(switchPin_1);
  switchValue_2 = digitalRead(switchPin_2);
  sensePulse();
  int light = analogRead(photoPin);
  bool isOn = false;
  if (pulse > 0) {
    if (switchValue_1 > 0 && pulseHistory[repeatCount] > 0) {
      goto switches;
    } else {
      if (switchValue_2 > 0) {
        goto switches;
      } else {
        Serial.println("pulse");
        digitalWrite(LEDPin, HIGH);
        isOn = true;
      }
    }
  }
  switches:
  if (switchValue_2 > 0 && pulse == 0) {
    Serial.println("switch two");
    digitalWrite(LEDPin, LOW);
  } else {
    if (switchValue_1 > 0 && pulseHistory[repeatCount] > 0) {
      Serial.println("switch one");
      digitalWrite(LEDPin, HIGH);
      isOn = true;
      if (repeatCount == 0) {
        repeatCount = 19;
      } else {
        repeatCount = repeatCount - 1;
      }
    }
  }
  if (isOn == false) {
    Serial.println("off");
    digitalWrite(LEDPin, LOW);
  }
  Serial.println(light);
  delay(1);        // delay in between reads for stability
}

void sensePulse() 
{
  float pulseValue = analogRead(pulsePin);
  if (pulseValue > 250) {
    int i;
    float pulseSum = 0;
    for (i = 19; i > 0; i = i - 1) {
      pulseSum = pulseSum + pulseHistory[i];
      pulseHistory[i] = pulseHistory[i-1];
    }
    pulseHistory[0] = pulseValue;
    pulseSum = pulseSum + pulseHistory[0];
    float baseline = (pulseSum / 20) + 1;
    if (pulseValue > baseline) {
      pulse = pulseValue;
    } else {
      pulse = 0;
    }
  } else {
    pulse = 0;
  }
}

