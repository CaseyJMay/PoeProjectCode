char data;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
            
}

void loop() {
  while (Serial.available() > 0) {
    data = Serial.readString().toInt();
    
    if (data == 1) {
      Serial.print("LED On");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(1000);
    }
    else if (data == 0) {
      Serial.print("LED Off");
      digitalWrite(LED_BUILTIN, LOW);
      delay(1000); 
    }
    else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
