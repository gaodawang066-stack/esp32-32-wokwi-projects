const int LED_PIN = 4;
const int BUTTON_PIN = 5;
const int PWM_FREQ = 5000;       // PWM 频率 5000Hz
const int PWM_RESOLUTION = 8;    // 8位分辨率，占空比 0~255

enum LightMode { MODE_OFF, MODE_ON, MODE_BLINK, MODE_BREATHE };
LightMode currentMode = MODE_OFF;

bool lastButtonState = HIGH;
bool currentButtonState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long DEBOUNCE_DELAY = 50;

unsigned long lastBlinkTime = 0;
bool blinkState = false;

int breathBrightness = 0;
int breathDirection = 5;
unsigned long lastBreatheTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION);
  ledcWrite(LED_PIN, 0);
  Serial.println("Ready. Press button to change mode.");
}

void checkButton() {
  bool reading = digitalRead(BUTTON_PIN);
  if (reading != lastButtonState) lastDebounceTime = millis();

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != currentButtonState) {
      currentButtonState = reading;
      if (currentButtonState == LOW) {
        currentMode = (LightMode)((currentMode + 1) % 4);
        Serial.print("Mode: ");
        Serial.println(currentMode);
      }
    }
  }
  lastButtonState = reading;
}

void handleBlink() {
  if (millis() - lastBlinkTime > 300) {
    blinkState = !blinkState;
    ledcWrite(LED_PIN, blinkState ? 255 : 0);
    lastBlinkTime = millis();
  }
}

void handleBreathe() {
  if (millis() - lastBreatheTime > 15) {
    breathBrightness += breathDirection;
    if (breathBrightness >= 255 || breathBrightness <= 0) {
      breathDirection = -breathDirection;
    }
    ledcWrite(LED_PIN, breathBrightness);
    lastBreatheTime = millis();
  }
}

void loop() {
  checkButton();
  switch (currentMode) {
    case MODE_OFF:     ledcWrite(LED_PIN, 0); break;
    case MODE_ON:      ledcWrite(LED_PIN, 255); break;
    case MODE_BLINK:   handleBlink(); break;
    case MODE_BREATHE: handleBreathe(); break;
  }
}