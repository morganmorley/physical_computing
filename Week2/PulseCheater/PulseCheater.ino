/*
  PulseCheater
  Reads two analog inputs (pins 0 and 6) and two digital inputs (pins 3 and 4), prints the result 
  of the photocell to the serial monitor. Powers one digital output in the form of an LED (pin 13).
  Graphical representation is available using serial plotter (Tools > Serial Plotter menu)

  by Morgan Morley Mills
  created 8 March 2017
*/

//Pins:
int LEDPin = 13;
int pulsePin = 0;
int switchPin_1 = 3;
int switchPin_2 = 4;
int photoPin = 6;
//Pulse Data:
float pulseHistory[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
float pulse = 0;
//Misc:
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
  // read the input on analog pin 0:
  sensePulse();
  // turn on the LED according to your pulse and the switches.
  bool isOn = false;
  if (pulse > 0) {
    if (switchValue_1 > 0 || switchValue_2 > 0) {
      goto switches;
    } else {
      digitalWrite(LEDPin, HIGH);
      isOn = true;
    }
  }
  switches:
  if (switchValue_2 > 0) {
    digitalWrite(LEDPin, LOW);
  } else {
    if (switchValue_1 > 0) {
      digitalWrite(LEDPin, HIGH);
      isOn = true;
    }
  }
  if (isOn == false) {
    digitalWrite(LEDPin, LOW);
  }
  // read the input on analog pin 6:
  int light = analogRead(photoPin);
  // print the light reading to the serial monitor:
  Serial.println(light);
  delay(1);        // delay in between reads for stability
}

void sensePulse() 
{
  // read the input on analog pin 0:
  float pulseValue = analogRead(pulsePin);
  // determines if there is an active pulse:
  if (pulseValue > 250) {
    int i;
    float pulseSum = 0;
    for (i = 19; i > 0; i = i - 1) {
      pulseSum = pulseSum + pulseHistory[i];
      pulseHistory[i] = pulseHistory[i-1];
    }
    pulseHistory[0] = pulseValue;
    pulseSum = pulseSum + pulseValue;
    // if the pulse is in active peak, changes pulse variable for LED power
    float baseline = (pulseSum / 20) + 1;
    if (pulseValue > baseline) {
      pulse = pulseValue;
    } else {
      // no LED power
      pulse = 0;
    }
  } else {
    pulse = 0;
  }
}

