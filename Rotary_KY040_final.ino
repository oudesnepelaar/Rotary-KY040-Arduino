int DATApin = 6;
int CLOCKpin = 7;

int dataValue = -1;
int clockValue = -1;
int dataPrev = -1;
int clockPrev = -1;

int bufferLevel = 5;
int resultValue = 0;

boolean turnDetected = false;

void setup() {

  pinMode(DATApin, INPUT);
  pinMode(CLOCKpin, INPUT);
  
  Serial.begin(19200);
  while (! Serial);
  Serial.println("System initiated...\n");
}

void loop() {
  
  sample();
  if (turnDetected) determineDirection();  
}

void sample() {

  dataPrev = dataValue;
  clockPrev = clockValue;

  dataValue = digitalRead(DATApin);
  clockValue = digitalRead(CLOCKpin);

  if ((dataValue != dataPrev) || (clockValue != clockPrev)) turnDetected = true;
}

void determineDirection() {

  turnDetected = false;
  boolean isCW;
  
  if (dataValue == clockValue) {

    isCW = (dataValue == dataPrev);
    
  } else {

    isCW = (clockValue == clockPrev);
  }

  if (isCW) {
    
    bufferLevel++;
    
  } else {

    bufferLevel--;
  }

  interpretBuffer();
}

void interpretBuffer() {

  if (bufferLevel == 0) { // full complement of CCW

    bufferLevel = 5;
    decrease();
    return;
  }

  if (bufferLevel == 10) { // full complement of CW

    bufferLevel = 5;
    increase();
    return;
  }
}

void increase() {

  resultValue++;
  Serial.println(resultValue);
}

void decrease() {

  resultValue--;
  Serial.println(resultValue);
}
