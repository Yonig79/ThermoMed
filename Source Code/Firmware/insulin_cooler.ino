#include <Wire.h>
#include <SPI.h>
#include <U8g2lib.h>
#include <Adafruit_MCP9808.h>

// === OLED Display Setup ===
U8G2_SH1106_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 5, /* dc=*/ 17, /* reset=*/ 16);

// === Temperature Sensor Setup ===
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();

// === Pin Configuration ===
const int PWM_PIN = 25;
const int BUZZER_PIN = 26;
const int PWM_CHANNEL = 0;

// === System State Flags ===
bool alarmTriggered = false;
bool fixedPWMActive = false;
bool rampFinished = false;
bool controlStarted = false;

// === Soft Start Parameters ===
int rampPWM = 100;
unsigned long lastRampTime = 0;
const unsigned long rampInterval = 8000;

// === Power Consumption Tracking ===
unsigned long startTime = 0;
unsigned long totalPWM = 0;
float avgPowerWatts = -1;
unsigned long lastAvgPowerUpdate = 0;

// === Loop Timing ===
unsigned long lastLoopTime = 0;
const unsigned long loopInterval = 1000;

// === Thermal Evaluation Variables ===
float temperatureInput;
float previousSample = 0;
float currentSample = 0;
bool evaluationActive = false;
bool awaitingNextSample = false;
unsigned long evaluationStartTime = 0;
int belowThresholdCount = 0;
int aboveThresholdCount = 0;


float deviationTotal = 0;
float errorTotal = 0;
int sampleCounter = 0;
String thermalDecision = "Normal";

// === Function Declaration ===
void triggerBeep();

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);
  tempsensor.begin();
  u8g2.begin();

  pinMode(BUZZER_PIN, OUTPUT);
  ledcSetup(PWM_CHANNEL, 5000, 8);
  ledcAttachPin(PWM_PIN, PWM_CHANNEL);

  startTime = millis();
}

void loop() {
  static int pwmValue = 0;
  String pwmStatus = "";

  if (millis() - lastLoopTime >= loopInterval) {
    lastLoopTime = millis();

    // === Read Temperature ===
    temperatureInput = tempsensor.readTempC();

    // === Start Control Logic When Temperature Reaches 6°C ===

if (!controlStarted && rampFinished && temperatureInput <= 6.0) {
  controlStarted = true;
  evaluationActive = true;
  evaluationStartTime = millis();
  previousSample = temperatureInput;
  awaitingNextSample = true;
}

// === Thermal Evaluation: Sequential Logic with 60s Decision Cycle ===

if (evaluationActive && awaitingNextSample && millis() - evaluationStartTime >= 3000) {
  currentSample = temperatureInput;
  awaitingNextSample = false;

  // Protective logic: count consecutive samples below or above threshold

  if (currentSample < 6.0) {
    belowThresholdCount++;
    aboveThresholdCount = 0;
  } else if (currentSample > 6.0) {
    aboveThresholdCount++;
    belowThresholdCount = 0;
  }

  // Always calculate error between samples

  float error = abs(currentSample - previousSample) / 2.0;
  errorTotal += error;

  bool sameSideOfThreshold = (previousSample > 6.0 && currentSample > 6.0) ||
                             (previousSample < 6.0 && currentSample < 6.0);

  if (sameSideOfThreshold) {
    previousSample = currentSample;
    awaitingNextSample = true;
  } else {
    float deviation = abs(abs(currentSample - 6.0) - abs(previousSample - 6.0));
    deviationTotal += deviation;
    sampleCounter++;

    previousSample = currentSample;
    awaitingNextSample = true;
  }
}

if (evaluationActive && millis() - evaluationStartTime >= 60000) {
  float averageDeviation = deviationTotal / max(sampleCounter, 1);
  float averageError = errorTotal / max(sampleCounter + 1, 1); // +1 to avoid zero division if no transitions

  // Final decision logic with protection

  if (belowThresholdCount >= 10) {
    thermalDecision = "Negative";
    averageDeviation = averageError ;
  } else if (aboveThresholdCount >= 10) {
    thermalDecision = "Positive";
    averageDeviation = averageError ;
  } else if (averageDeviation > 0.5) {
    thermalDecision = (currentSample > 6.0) ? "Positive" : "Negative";
  } else {
    thermalDecision = "Normal";
  }

  Serial.println("=== Final Thermal Evaluation ===");
  Serial.print("Decision: "); Serial.println(thermalDecision);
  Serial.print("Average Deviation: "); Serial.println(averageDeviation, 2);
  Serial.print("Average Error:+- "); Serial.println(averageError, 2);

  // Restart evaluation for next 60-second cycle
  evaluationStartTime = millis();
  deviationTotal = 0;
  errorTotal = 0;
  sampleCounter = 0;
  awaitingNextSample = true;
  previousSample = currentSample;

  // Reset protection counters
  belowThresholdCount = 0;
  aboveThresholdCount = 0;
}

    // === PWM Control Based on Temperature and Decision ===
    
    if (controlStarted) {
      if (temperatureInput <= 5.2) {
        pwmValue = (thermalDecision == "Positive") ? 120 : (thermalDecision == "Negative") ? 90 : 100;
      } else if (temperatureInput <= 5.3) {
        pwmValue = (thermalDecision == "Positive") ? 135 : (thermalDecision == "Negative") ? 105 : 115;
      } else if (temperatureInput <= 5.4) {
        pwmValue = (thermalDecision == "Positive") ? 150 : (thermalDecision == "Negative") ? 120 : 130;
      } else if (temperatureInput <= 5.5) {
        pwmValue = (thermalDecision == "Positive") ? 175 : (thermalDecision == "Negative") ? 140 : 155;
      } else if (temperatureInput <= 5.6) {
        pwmValue = (thermalDecision == "Positive") ? 230 : (thermalDecision == "Negative") ? 180 : 215;
      } else if (temperatureInput <= 5.7) {
        pwmValue = (thermalDecision == "Positive") ? 245 : (thermalDecision == "Negative") ? 200 : 240;
      } else if (temperatureInput <= 5.8) {
        pwmValue = (thermalDecision == "Positive") ? 247 : (thermalDecision == "Negative") ? 210 : 242;
      } else if (temperatureInput <= 5.9) {
        pwmValue = (thermalDecision == "Positive") ? 250 : (thermalDecision == "Negative") ? 220 : 245;
      } else if (temperatureInput <= 6.0) {
        pwmValue = (thermalDecision == "Positive") ? 253 : (thermalDecision == "Negative") ? 230 : 248;
      } else if (temperatureInput <= 6.1) {
        pwmValue = (thermalDecision == "Positive") ? 255 : (thermalDecision == "Negative") ? 240 : 252;
      } else {
        pwmValue = 255;
      }

      pwmValue = constrain(pwmValue, 100, 255);
      ledcWrite(PWM_CHANNEL, pwmValue);
      pwmStatus = "Stepped";

      if (temperatureInput <= 6.0 && !alarmTriggered) {
        triggerBeep();
        alarmTriggered = true;
      }

      fixedPWMActive = true;
    }

    // === Soft Start Ramp Before Fixed Control ===
    if (!fixedPWMActive && !rampFinished) {
      pwmValue = rampPWM;
      pwmValue = constrain(pwmValue, 100, 255);
      ledcWrite(PWM_CHANNEL, pwmValue);
      pwmStatus = "Soft Start";

      if (millis() - lastRampTime >= rampInterval && rampPWM < 255) {
        rampPWM = min(rampPWM + 10, 255);
        if (rampPWM == 255) rampFinished = true;
        lastRampTime = millis();
      }
    }

    // === Accumulate PWM for Power Tracking ===
    totalPWM += pwmValue;

    // === Calculate and Display Average Power Every 30 Minutes ===

    if (millis() - lastAvgPowerUpdate >= 1800000) {
      float elapsedSeconds = (millis() - startTime) / 1000.0;
      avgPowerWatts = (totalPWM / elapsedSeconds) * (44.0 / 255.0);

      Serial.print("Average Power (30 min): ");
      Serial.print(avgPowerWatts);
      Serial.println(" W");

      totalPWM = 0;
      startTime = millis();
      lastAvgPowerUpdate = millis();
    }

    // === OLED Display Output ===
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_logisoso20_tf);
    u8g2.setCursor(30, 40);
    char tempBuffer[10];
    dtostrf(temperatureInput, 4, 1, tempBuffer);
    u8g2.print(tempBuffer);

    if (temperatureInput < 8.0) {
      u8g2.setFont(u8g2_font_6x10_tf);
      u8g2.setCursor(100, 40);
      u8g2.print("Ready");
    }

    u8g2.setFont(u8g2_font_6x10_tf);
    u8g2.setCursor(128 - u8g2.getStrWidth(thermalDecision.c_str()), 64);
    u8g2.print(thermalDecision.c_str());

    u8g2.sendBuffer();
  }
}
// === Buzzer Alert Function ===
void triggerBeep() {
  for (int i = 0; i < 2; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
}
