#define TOLERANCE 4

int LastValue[] = {A0, A1, A2, A3, A4, A5};

int pot1 = A0;
int pot2 = A1;
int pot3 = A2;
int pot4 = A3;
int pot5 = A4;
int pot6 = A5;

int lastPot1Value, lastPot2Value = 0;
int value = 0;

void SendValue(int Pin, int val){
  String PinString;
  //do I need to send a comma delimited string?
  //do I need to convert the Pin integer values to the Analog label?
  //Serial.print(Pin);
  /*int pin_written = Serial.write(Pin);
  if (pin_written = 0)
    {
    Serial.println("Write Pin to port failed");
    }
  int value_written = Serial.write(x);
  if (value_written = 0)
    {
    Serial.println("Write Value to port failed");
    }*/
  //Serial.print(" : Sending to Pi = ");
  //Serial.println(x);
  int x = map(val, 0, 1023, 0, 127);
  if (Pin == 54) {
    PinString = "A0";
  }
  if (Pin == 56) {
    PinString = "A1";
  }
  //String PinString = String(Pin);
  String ValueString = String(x);
  String Message = PinString + "," + ValueString + "\r\n";
  Serial.print(Message);
  //for (int i = 0; i < Message.length(); i++)
  //  {
  //  Serial.write(Message[i]);
  //  }
}


void ReadAnalogPin (int x, int Pin, int value)
{
  int diff = 0;
  diff = abs(value - LastValue[x]);
  if (diff > TOLERANCE )
    {
    if (value != LastValue[x])
      {
      SendValue(Pin, value);  
      LastValue[x] = value;
      }
    }
}


void setup()
{
  Serial.begin(57600);  //For some reason my code only works at 115200..
  pinMode(pot1, INPUT); 
  pinMode(pot2, INPUT); 
  pinMode(pot3, INPUT); 
  pinMode(pot4, INPUT); 
  pinMode(pot5, INPUT); 
  pinMode(pot6, INPUT); 
}

void loop()
{
  //This shows the pin floating....I may need a cap on the pot
  /*value = analogRead(pot1);
  if (value != lastPot1Value)
    {
    Serial.print("!pos1 ");
    Serial.print(value);
    Serial.println(" ;");
    lastPot1Value = value;
    }
    
  value = analogRead(pot2);
  if (value != lastPot2Value)
    {
    Serial.print("!pos2 ");
    Serial.print(value);
    Serial.println(" ;");
    lastPot2Value = value;
    }*/
  ReadAnalogPin(1, pot1, analogRead(pot1));
  //ReadAnalogPin(2, pot2, analogRead(pot2));
  ReadAnalogPin(3, pot3, analogRead(pot3));
  //ReadAnalogPin(4, pot4, analogRead(pot4));
  //ReadAnalogPin(5, pot5, analogRead(pot5));
  //ReadAnalogPin(6, pot6, analogRead(pot6));

  //while(!Serial.available());  //wait until a byte was received
  //Serial.println(Serial.read());//output received byte
}


//Saving for later.....
/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/

/*void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}*/

