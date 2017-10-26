int buzzPin=1; 
int timeOn=800; //specified in milliseconds
int timeOff=300; //specified in millisecods

int start = 523;

int third = start * 1.25;
int fifth = start * 1.5;
int octave = start * 2;

int triad[] = {start, third, fifth, octave};
int len = 4;
int counter = 0;
int step = 1;

void setup() {
  Serial.begin(9600);
}

void loop() {  
  tone(buzzPin, triad[counter]);
  delay(timeOn);
  noTone(buzzPin);
  delay(timeOff); 
  counter += step;
  if (counter == 0 || counter >= len-1) step = -step;
}
