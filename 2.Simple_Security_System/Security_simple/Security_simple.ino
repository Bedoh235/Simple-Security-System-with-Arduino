const int ledPin = 8;
const int buzzerPin = 9;
const int motionSensorPin = 7;
const int buttonPin = 4;
bool securityEnabled = false;
bool disableSecurity = false;
int motion;
void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(motionSensorPin, INPUT);
  pinMode(buttonPin, INPUT);

}

void loop() {
  int motion = digitalRead(motionSensorPin);
  if(Serial.available() > 0) {
    char incomingChar = Serial.read();
    switch (incomingChar) {
      case 'a':
        securityEnabled = true; break;  
      case 'b':
        securityEnabled = false; break;
      case 'c':
        disableSecurity = true;
    } 
  }
  if (motion == HIGH and securityEnabled == true) {
      while (disableSecurity == false) {
            tone(buzzerPin, 2000);
            digitalWrite(ledPin, HIGH);
            delay(1500); 
            noTone(buzzerPin);
            digitalWrite(ledPin, LOW);
            if (digitalRead(buttonPin) == HIGH) {
                disableSecurity = true;
                noTone(buzzerPin);
                digitalWrite(ledPin, LOW);
            }
                  
              } 
   }    
            
  else if (motion == LOW and disableSecurity == true) {
    disableSecurity = false;
    noTone(buzzerPin);
    digitalWrite(ledPin, LOW);
    delay(5000);

  }
  noTone(buzzerPin);
  digitalWrite(ledPin, LOW);
}
