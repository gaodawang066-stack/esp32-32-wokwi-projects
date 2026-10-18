const int LDR_PIN = 34;      // 电位器模拟光敏
const int LED_PIN = 2;
const int THRESHOLD = 2000;  // 阈值

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int lightValue = analogRead(LDR_PIN);
  Serial.print("Light: ");
  Serial.println(lightValue);

  if (lightValue < THRESHOLD) {
    digitalWrite(LED_PIN, HIGH);
    Serial.println("Dark -> LED ON");
  } else {
    digitalWrite(LED_PIN, LOW);
    Serial.println("Bright -> LED OFF");
  }
  delay(500);
}
