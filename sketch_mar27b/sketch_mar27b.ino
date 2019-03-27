void setup() {
  // initialize serial:
  Serial.begin(9600);
  while (!Serial){
    ;
  }

}

void loop() {
  while (Serial.available() > 0){
    String str = Serial.readString();
    Serial.println("J'ai reçu");
    Serial.println(str);
  }
}
