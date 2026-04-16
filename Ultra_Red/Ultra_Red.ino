// This code is built from various code examples from the following places
// https://dronebotworkshop.com/esp32-pwm-fan/, https://www.espboards.dev/blog/ssd1306-esp32-s3-super-mini-setup/, https://www.teachmemicro.com/using-the-esp32-internal-temperature-sensor-with-arduino/
static const uint8_t woe[512] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xfe, 0x00, 0x00, 0x00, 0x3f, 0x10, 0x01, 0xf8, 0x00, 0x0f, 0xc0, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xfe, 0x00, 0x00, 0x00, 0x4c, 0xb0, 0x01, 0x88, 0x00, 0x0c, 0xe0, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x0c, 0x30, 0x61, 0xce, 0x0c, 0x3c, 0x39, 0x81, 0xc4, 0x4c, 0x76, 0x88, 0x1e, 0x79, 0xf0, 
    0x00, 0x18, 0xf9, 0xf3, 0xdf, 0x0c, 0x3e, 0xfd, 0xfb, 0xe6, 0xcc, 0x37, 0xcc, 0x7e, 0xfd, 0xf8, 
    0x00, 0x30, 0xdd, 0xbb, 0x11, 0x0c, 0x22, 0xcd, 0x86, 0x33, 0x8c, 0x36, 0x1e, 0x67, 0xcd, 0x98, 
    0x00, 0x60, 0xc1, 0x83, 0x11, 0x0c, 0x22, 0xc1, 0x86, 0x33, 0x8c, 0x36, 0x36, 0x67, 0x8d, 0x98, 
    0x00, 0xe0, 0xc1, 0x83, 0x11, 0x0c, 0x22, 0xc1, 0x86, 0x37, 0x8c, 0x66, 0x63, 0x3f, 0xcd, 0x98, 
    0x01, 0xfe, 0xf9, 0xf3, 0x1f, 0x0c, 0x22, 0xfd, 0x83, 0xe4, 0xcf, 0xc6, 0x3f, 0x7e, 0xfd, 0xb0, 
    0x00, 0x0e, 0x78, 0xf0, 0x0e, 0x0c, 0x20, 0x79, 0x81, 0xc4, 0x4f, 0x06, 0x19, 0x7e, 0x79, 0xa0, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc6, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe6, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x01, 0x81, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x01, 0x99, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x01, 0x99, 0x98, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x99, 0x3c, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xff, 0x66, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0xe7, 0x66, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x42, 0x3c, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x42, 0x38, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WebServer.h>
#define I2C_SCL 2
#define I2C_SDA 1
#define VRY_PIN  9
#define VRX_PIN  8
#define BUTTON 10
#define SCREEN_WIDTH 128 // display width,  in pixels
#define SCREEN_HEIGHT 32 // display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const char* ap_ssid = "Ultra Red";      // WiFi network name
WebServer server(80);  // NEW: Create web server object on port 80
const int PWM_PIN = 4; 
const int TACH_PIN = 5;  
const int PWM_PIN2 = 6;   
const int TACH_PIN2 = 7;  
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
int lastState = 0; 
int currentState;
unsigned long buttonPressTime = 0;
bool buttonHeld = false;
bool webServerEnabled = true;
bool webServerInitialized = false;
void IRAM_ATTR tachISR() {
  tachPulseCount = tachPulseCount + 1;
}
void IRAM_ATTR tachISR2() {
  tachPulseCount2 = tachPulseCount2 + 1;
}

void setup() {
  // Start Serial Monitor
  Serial.begin(9600);
  pinMode(BUTTON, INPUT_PULLUP);
  analogSetAttenuation(ADC_11db);
  Wire.begin(I2C_SDA, I2C_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("yo shit fucked"));
    while (1);
  }
  display.clearDisplay();
  display.drawBitmap(0, 0, woe, 128, 32, 1);
  display.display(); 
  delay(3000);        
  display.clearDisplay();
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
  
  wifi();
}

void loop() {
  checkButtonHold();  // ADD THIS LINE - Check for button hold first
  currentState = digitalRead(BUTTON);
  Serial.print(currentState);
  valueX = analogRead(VRX_PIN);
  valueY = analogRead(VRY_PIN);
  tacho();
  oled();
  pwm();
  temp_celsius = temperatureRead();
  pwmValue = map(fanspeedPercent, 0, 100, 0, 255);
  ledcWrite(PWM_PIN, pwmValue);
  ledcWrite(PWM_PIN2, pwmValue);
  if (webServerEnabled && webServerInitialized) {
    server.handleClient();
  }
  if (!webServerEnabled) {
    delay(10);  // Give CPU a break when server is off
  }
}
void checkButtonHold() {
  if (digitalRead(BUTTON) == LOW) {
    if (buttonPressTime == 0) {
      buttonPressTime = millis();
    }
    else if ((millis() - buttonPressTime) >= 1500 && !buttonHeld) {
      buttonHeld = true;
      
      if (webServerEnabled) {
        // Turn off web server AND WiFi
        server.stop();
        WiFi.mode(WIFI_OFF);  // This actually turns off the WiFi radio
        webServerEnabled = false;
        Serial.println("Web server and WiFi DISABLED");
      } else {
        // Turn WiFi back on and restart server
        WiFi.mode(WIFI_AP);
        WiFi.softAP(ap_ssid);
        server.begin();
        webServerEnabled = true;
        Serial.println("Web server and WiFi ENABLED");
        Serial.print("IP Address: ");
        Serial.println(WiFi.softAPIP());
      }
    }
  } 
  else {
    buttonPressTime = 0;
    buttonHeld = false;
  }
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
  if (currentState == 0){
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print("IP: ");
    display.println(WiFi.softAPIP());
    if (webServerEnabled) {
      display.setCursor(0, 10);
      display.print("Webserver & wifi: ON ");
    } else {
      display.setCursor(0, 10);
      display.print("Webserver & wifi: OFF");
    }
  } else {
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
  }
  display.display();
  delay(50);
  display.clearDisplay();
}

void wifi() {
  // Start ESP32 in Access Point mode (creates its own WiFi network)
  WiFi.softAP(ap_ssid);
  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());
  
  // Define what happens when someone visits the main webpage
  server.on("/", []() {
    // Basic HTML with Arial font and input box
    String html = "<!DOCTYPE html>\n";
    html += "<html>\n";
    html += "<head>\n";
    html += "  <title>OwO :3</title>\n";
    html += "  <meta charset='UTF-8'>\n";
    html += "  <style>\n";
    html += "    body { font-family: Arial, sans-serif; }\n";
    html += "  </style>\n";
    html += "  <script>\n";
    html += "    // Function to send new fan speed to ESP32 when slider moves\n";
    html += "    function updateFanSpeed(value) {\n";
    html += "      fetch('/setFanSpeed?value=' + value);\n";
    html += "      document.getElementById('fanPercent').innerHTML = value + '%';\n";
    html += "      document.getElementById('speedInput').value = value;\n";
    html += "    }\n";
    html += "    \n";
    html += "    // Function to set fan speed from input box\n";
    html += "    function setSpeedFromInput() {\n";
    html += "      var inputValue = document.getElementById('speedInput').value;\n";
    html += "      var speed = parseInt(inputValue, 10);\n";
    html += "      if (!isNaN(speed) && speed >= 0 && speed <= 100) {\n";
    html += "        // Send the value to ESP32\n";
    html += "        fetch('/setFanSpeed?value=' + speed);\n";
    html += "        // Update the displayed percentage\n";
    html += "        document.getElementById('fanPercent').innerHTML = speed + '%';\n";
    html += "        // Update the slider position\n";
    html += "        document.getElementById('slider').value = speed;\n";
    html += "      } else {\n";
    html += "        alert('Please enter a number between 0 and 100');\n";
    html += "      }\n";
    html += "    }\n";
    html += "    \n";
    html += "    // Function to get latest data from ESP32 (updates displays but NOT the input box)\n";
    html += "    function fetchData() {\n";
    html += "      fetch('/data')\n";
    html += "        .then(response => response.json())\n";
    html += "        .then(data => {\n";
    html += "          document.getElementById('rpm1').innerHTML = data.rpm1 + ' RPM';\n";
    html += "          document.getElementById('rpm2').innerHTML = data.rpm2 + ' RPM';\n";
    html += "          document.getElementById('pwm').innerHTML = data.pwm + ' PWM';\n";
    html += "          document.getElementById('fanPercent').innerHTML = data.fanPercent + '%';\n";
    html += "          document.getElementById('temp').innerHTML = data.temp + '°C';\n";
    html += "          document.getElementById('slider').value = data.fanPercent;\n";
    html += "          // IMPORTANT: Do NOT update the input box here!\n";
    html += "        })\n";
    html += "        .catch(error => {\n";
    html += "          console.log('Error fetching data:', error);\n";
    html += "        });\n";
    html += "    }\n";
    html += "    \n";
    html += "    // Allow pressing Enter key in the input box\n";
    html += "    document.addEventListener('DOMContentLoaded', function() {\n";
    html += "      var inputBox = document.getElementById('speedInput');\n";
    html += "      if (inputBox) {\n";
    html += "        inputBox.addEventListener('keypress', function(event) {\n";
    html += "          if (event.key === 'Enter') {\n";
    html += "            event.preventDefault();\n";
    html += "            setSpeedFromInput();\n";
    html += "          }\n";
    html += "        });\n";
    html += "      }\n";
    html += "    });\n";
    html += "    \n";
    html += "    // Auto-refresh data every 1 second\n";
    html += "    setInterval(fetchData, 500);\n";
    html += "  </script>\n";
    html += "</head>\n";
    html += "<body>\n";
    html += "  <h1>Ultra Red</h1>\n";
    html += "  <hr>\n";
    html += "  \n";
    html += "  <h2>Fan 1 (Intake) RPM:</h2>\n";
    html += "  <p id='rpm1'>0 RPM</p>\n";
    html += "  \n";
    html += "  <h2>Fan 2 (Exhaust) RPM:</h2>\n";
    html += "  <p id='rpm2'>0 RPM</p>\n";
    html += "  \n";
    html += "  <h2>PWM Value (0-255):</h2>\n";
    html += "  <p id='pwm'>0 PWM</p>\n";
    html += "  \n";
    html += "  <h2>Fan Speed Percentage:</h2>\n";
    html += "  <p id='fanPercent'>0%</p>\n";
    html += "  \n";
    html += "  <h3>Adjust Fan Speed:</h3>\n";
    html += "  <input type='range' min='0' max='100' value='0' id='slider' onchange='updateFanSpeed(this.value)'>\n";
    html += "  <br><br>\n";
    html += "  <label>Enter Speed (0-100): </label>\n";
    html += "  <input type='number' id='speedInput' min='0' max='100' value='0' step='1'>\n";
    html += "  <button onclick='setSpeedFromInput()'>Set Speed</button>\n";
    html += "  <br><br>\n";
    html += "  \n";
    html += "  <h2>Temperature:</h2>\n";
    html += "  <p id='temp'>0°C</p>\n";
    html += "  \n";
    html += "  <hr>\n";
    html += "</body>\n";
    html += "</html>\n";
    
    server.send(200, "text/html", html);
  });
  
  // NEW: Endpoint that sends data as JSON (for JavaScript to read)
  server.on("/data", []() {
    String json = "{";
    json += "\"rpm1\":" + String(rpm) + ",";
    json += "\"rpm2\":" + String(rpm2) + ",";
    json += "\"pwm\":" + String(pwmValue) + ",";
    json += "\"fanPercent\":" + String(fanspeedPercent) + ",";
    json += "\"temp\":" + String(temp_celsius);
    json += "}";
    server.send(200, "application/json", json);
  });
  
  // NEW: Endpoint that receives new fan speed from the slider or input box
  server.on("/setFanSpeed", []() {
    if (server.hasArg("value")) {
      fanspeedPercent = server.arg("value").toInt();
      fanspeedPercent = constrain(fanspeedPercent, 0, 100);
      Serial.print("Web interface set fan speed to: ");
      Serial.print(fanspeedPercent);
      Serial.println("%");
      server.send(200, "text/plain", "OK");
    } else {
      server.send(400, "text/plain", "Bad Request");
    }
  });
  
  server.begin();
  webServerEnabled = true;
  webServerInitialized = true;
  Serial.println("Web server initialized and started");
}