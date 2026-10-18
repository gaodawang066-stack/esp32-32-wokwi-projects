const int LED_PIN = 0;          // LED 接在 GPIO 0
const int BLINK_INTERVAL = 200; // 闪烁间隔 1000 毫秒

void setup() {
  pinMode(LED_PIN, OUTPUT);      // 把 GPIO 2 设为输出模式
  Serial.begin(115200);          // 打开串口，波特率 115200
  Serial.println("LED Blink Start");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);   // 输出高电平，LED 亮
  Serial.println("LED: ON");
  delay(BLINK_INTERVAL);         // 等 1 秒

  digitalWrite(LED_PIN, LOW);    // 输出低电平，LED 灭
  Serial.println("LED: OFF");
  delay(BLINK_INTERVAL);         // 等 1 秒
}
