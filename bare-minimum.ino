// This code is built from various code examples from the following places
// https://dronebotworkshop.com/esp32-pwm-fan/, https://www.espboards.dev/blog/ssd1306-esp32-s3-super-mini-setup/, https://www.teachmemicro.com/using-the-esp32-internal-temperature-sensor-with-arduino/

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define I2C_SCL 5
#define I2C_SDA 6
#define VRY_PIN  9 // ESP32 pin GPIO36 (ADC0) connected to VRY pin
#define VRX_PIN  10 // ESP32 pin GPIO39 (ADC3) connected to VRX pin
#define SCREEN_WIDTH 128 // display width,  in pixels
#define SCREEN_HEIGHT 32 // display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const int PWM_PIN = 1; 
const int TACH_PIN = 2;  
const int PWM_PIN2 = 3;   
const int TACH_PIN2 = 4;  
const int PWM_FREQ = 25000;    // 25 kHz frequency for computer fans
const int PWM_RESOLUTION = 8;  // 8-bit resolution (0-255)
int valueX = 0; // to store the X-axis value
int valueY = 0; // to store the Y-axis value
volatile unsigned long tachPulseCount = 0;
volatile unsigned long tachPulseCount2 = 0;
unsigned long lastTachTime = 0;
unsigned long lastTachTime2 = 0;
const unsigned long TACH_SAMPLE_TIME = 500;  // Sample period in milliseconds
const unsigned long TACH_SAMPLE_TIME2 = 500;
int rpm = 0;
int rpm2 = 0;
int pwmValue = 0;
int fanspeedPercent = 0;
unsigned long temp_celsius = 0;
void IRAM_ATTR tachISR() {
  tachPulseCount = tachPulseCount + 1;
}
void IRAM_ATTR tachISR2() {
  tachPulseCount2 = tachPulseCount2 + 1;
}

void setup() {

  // Start Serial Monitor
  Serial.begin(115200);
  analogSetAttenuation(ADC_11db);
  Wire.begin(I2C_SDA, I2C_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("yo shit fucked"));
    while (1);
  }
  delay(2000);         // wait two seconds for initializing
  display.clearDisplay(); // clear display
  ledcAttach(PWM_PIN, PWM_FREQ, PWM_RESOLUTION);
  ledcAttach(PWM_PIN2, PWM_FREQ, PWM_RESOLUTION);
  pinMode(TACH_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TACH_PIN), tachISR, FALLING);
  pinMode(TACH_PIN2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(TACH_PIN2), tachISR2, FALLING);
  ledcWrite(PWM_PIN, 0);
  ledcWrite(PWM_PIN2, 0);
  lastTachTime = millis();
  lastTachTime2 = millis();
}

void loop() {
  tacho();
  oled();
  pwm();
  temp_celsius = temperatureRead();
  pwmValue = map(fanspeedPercent, 0, 100, 16, 255);
  ledcWrite(PWM_PIN, pwmValue);
  ledcWrite(PWM_PIN2, pwmValue);
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);
}
void tacho(){
    // Calculate RPM every second
  unsigned long currentTime = millis();
  unsigned long currentTime2 = millis();
  if (currentTime - lastTachTime >= TACH_SAMPLE_TIME) {
    // Calculate RPM (2 pulses per revolution for most fans)
    rpm = (tachPulseCount * 60000) / (TACH_SAMPLE_TIME * 2);
    tachPulseCount = 0;
    lastTachTime = currentTime;
  }
  if (currentTime2 - lastTachTime2 >= TACH_SAMPLE_TIME2) {
    rpm2 = (tachPulseCount2 * 60000) / (TACH_SAMPLE_TIME2 * 2);
    tachPulseCount2 = 0;
    lastTachTime2 = currentTime2;
  }
}

void pwm(){
  if (valueX >= 2200){
    fanspeedPercent = fanspeedPercent + 5;
    fanspeedPercent = constrain(fanspeedPercent, 0, 100);
    Serial.print("Fan Speed: ");
    Serial.print(fanspeedPercent);
    Serial.println("%");
    delay(100);
  }
  if (valueX <= 1000){
    fanspeedPercent = fanspeedPercent - 5;
    fanspeedPercent = constrain(fanspeedPercent, 0, 100);
    Serial.print("Fan Speed: ");
    Serial.print(fanspeedPercent);
    Serial.println("%");
    delay(100);
  }
  if (valueY >= 2400){
    fanspeedPercent = fanspeedPercent - 1;
    fanspeedPercent = constrain(fanspeedPercent, 0, 100);
    Serial.print("Fan Speed: ");
    Serial.print(fanspeedPercent);
    Serial.println("%");
    delay(100);
  }
  if (valueY <= 800){
    fanspeedPercent = fanspeedPercent + 1;
    fanspeedPercent = constrain(fanspeedPercent, 0, 100);
    Serial.print("Fan Speed: ");
    Serial.print(fanspeedPercent);
    Serial.println("%");
    delay(100);
  }
}

void oled(){
  display.setTextSize(1.3);
  display.setTextColor(WHITE);

  display.setCursor(70, 0);
  display.print("x=");
  display.print(valueX);

  display.setCursor(70, 10);
  display.print("y=");
  display.println(valueY);

  display.setCursor(0, 0);
  display.print(rpm);
  display.println(" RPM-I");

  display.setCursor(0, 10);
  display.print(rpm2);
  display.println(" RPM-E");

  display.setCursor(0, 20);
  display.print(fanspeedPercent);
  display.println("%");

  display.setCursor(30, 20);
  display.print(pwmValue);
  display.println("PWM");

  display.setCursor(70, 20);
  display.print("Temp ");
  display.print(temp_celsius);
  display.println("C");

  display.display();
  delay(50);
  display.clearDisplay();
}

