#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Setup PCA9685 Module
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Setup DS18B20 sensor on Pin 2
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// Safe limits for servo motors
#define SERVO_0_DEG   150 
#define SERVO_MAX_DEG 400 

// Variables
int fanSpeed = 0;
int sCommand = 0;
int nCommand = 0;
int prevNCommand = 0; 

// Swing State Machine
enum SwingState { IDLE, GOING, HOLDING, RETURNING };
SwingState swingState = IDLE;
unsigned long lastSwingMoveTime = 0;
unsigned long swingHoldStartTime = 0;
int currentSwingPos = SERVO_0_DEG;
const int swingDelay = 15; 

unsigned long lastTempTime = 0;

void setup() {
  Serial.begin(9600); 
  
  pwm.begin();
  pwm.setPWMFreq(50); 
  sensors.begin();
  
  // Initialize all actuators to Off/0 position
  pwm.setPWM(5, 0, 0); 
  pwm.setPWM(0, 0, SERVO_0_DEG);  
  pwm.setPWM(8, 0, SERVO_0_DEG);  
  pwm.setPWM(10, 0, SERVO_0_DEG); 
  pwm.setPWM(12, 0, SERVO_0_DEG); 
  pwm.setPWM(14, 0, SERVO_0_DEG); 
}

void loop() {
  
  // ==========================================
  // 1. Bulletproof Data Parsing from LabVIEW
  // ==========================================
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim(); // Remove unnecessary whitespace
    
    int fIndex = data.indexOf('F');
    int sIndex = data.indexOf('S');
    int nIndex = data.indexOf('N');
    
    // Extract Fan Speed if 'F' is found
    if (fIndex != -1) {
      fanSpeed = data.substring(fIndex + 1).toInt();
    }
    
    // Extract Swing Command if 'S' is found
    if (sIndex != -1) {
      sCommand = data.substring(sIndex + 1).toInt();
    }
    
    // Extract Net Command if 'N' is found
    if (nIndex != -1) {
      nCommand = data.substring(nIndex + 1).toInt();
    }
  }

  // ==========================================
  // 2. Control Fan Speed
  // ==========================================
  pwm.setPWM(5, 0, fanSpeed);

  // ==========================================
  // 3. Cradle Swing Logic (Activates on S1)
  // ==========================================
  switch (swingState) {
    case IDLE:
      if (sCommand == 1) {
        swingState = GOING;
        lastSwingMoveTime = millis();
      }
      break;
      
    case GOING:
      if (millis() - lastSwingMoveTime >= swingDelay) {
        currentSwingPos++;
        pwm.setPWM(0, 0, currentSwingPos);
        lastSwingMoveTime = millis();
        
        if (currentSwingPos >= SERVO_MAX_DEG) {
          swingState = HOLDING;
          swingHoldStartTime = millis(); 
        }
      }
      break;
      
    case HOLDING:
      if (millis() - swingHoldStartTime >= 10000) { // Swing for 10 seconds
        swingState = RETURNING;
        lastSwingMoveTime = millis();
      }
      break;
      
    case RETURNING:
      if (millis() - lastSwingMoveTime >= swingDelay) {
        currentSwingPos--;
        pwm.setPWM(0, 0, currentSwingPos);
        lastSwingMoveTime = millis();
        
        if (currentSwingPos <= SERVO_0_DEG) {
          swingState = IDLE; 
        }
      }
      break;
  }

  // ==========================================
  // 4. Mosquito Net Operation (Activates on N1)
  // ==========================================
  if (nCommand == 1 && prevNCommand == 0) {
    // Lower 4 motors safely
    pwm.setPWM(8, 0, SERVO_MAX_DEG);  delay(200);
    pwm.setPWM(10, 0, SERVO_MAX_DEG); delay(200);
    pwm.setPWM(12, 0, SERVO_MAX_DEG); delay(200);
    pwm.setPWM(14, 0, SERVO_MAX_DEG);
    
    delay(1500); 
    
    // Reset motors back to locked position
    pwm.setPWM(8, 0, SERVO_0_DEG);  delay(200);
    pwm.setPWM(10, 0, SERVO_0_DEG); delay(200);
    pwm.setPWM(12, 0, SERVO_0_DEG); delay(200);
    pwm.setPWM(14, 0, SERVO_0_DEG);
  }
  prevNCommand = nCommand; 

  // ==========================================
  // 5. Send Temperature Data to LabVIEW
  // ==========================================
  if (millis() - lastTempTime >= 1000) {
    sensors.requestTemperatures();
    float tempC = sensors.getTempCByIndex(0);
    Serial.println(tempC); 
    lastTempTime = millis();
  }
}