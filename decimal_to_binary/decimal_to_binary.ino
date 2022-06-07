/*
 * Following program receives a number for Serial input then turns on corresponding LED based on binary conversion of number.
 * It uses 4 led meaning 2^4 -1 value can be represented but can be extended for bigger values as well
 * It assumes 0th index value correspondes to MSB(most significant bit) and last index value to LSB(least significant bit)
 */
int value = 0;
int pin[4] = {5,4,3,2}; // Corresponds to -> {D5, D4, D3, D2} respectively
int totalPins = 4;
int incomingByte = 0; // for reading byte by byte
bool validValue = false;

void setup() {
  Serial.begin(9600); 
  for (int i = 0; i < totalPins; ++i) {
    pinMode(pin[i], OUTPUT);
  }
  // reset all pins
  for (int i = 0; i < totalPins; ++i) {
    digitalWrite(pin[i], LOW);
  }
}

void loop() {
  // read and parse integer
  while (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte >= 48 && incomingByte <= 57) {
      value = value * 10 + incomingByte - 48;
      validValue = true;
    }
    else if(validValue){
      for (int i = 0; i < totalPins; ++i) {
        if (kthBit(value, i)) {
          digitalWrite(pin[i], HIGH);
        }
        else {
          digitalWrite(pin[i], LOW);
        }
      }
      value = 0;
      validValue = false;
      break;
    }
  }

}
// function to find kth bit of a given number e.g. for n = 2 (00000010) will give true for k =2 bit and false for k =1 bit
bool kthBit(int n, int k) {
  return (n & (1 << k)) != 0;
}
