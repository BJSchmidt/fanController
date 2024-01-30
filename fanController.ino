#include <Adafruit_AM2315.h>

/***************************************************
  Simple temperature based fan controller.
  Triggers relay if temperature is above tempThreshold
  I'm using a 2 Channel 5V Relay Module: http://wiki.sunfounder.cc/index.php?title=2_Channel_5V_Relay_Module

  Based on an example for the AM2315 Humidity + Temp sensor from Adafruit:
  https://learn.adafruit.com/am2315-encased-i2c-temperature-humidity-sensor/arduino-code
 ****************************************************/
// Connect RED of the AM2315 sensor to 5.0V
// Connect BLACK to Ground
// Connect WHITE to i2c clock (Arduino Diecimila A5)
// Connect YELLOW to i2c data (Arduino Diecimila A4)

// Relay Input:
// Connect GND
// Connect IN1 or IN2 to Pin 3
// Connect VCC to Arduino VCC

// Relay Output:
// For Normally Open opperation: (Load is off until relay is triggered)
// Connect Relay output Center screw terminal to Load voltage
// Connect Relay output Left screw terminal (Normally Open) to Load


Adafruit_AM2315 am2315;

#define tempThreshold 90 // Setpoint to trigger relay on if temp is above (in degrees F)
#define useInterval true // If true wait for intervalMinutes before rechecking. If false, recheck every 2 seconds.
#define intervalMinutes 10 // Interval in minutes to wait before rechecking temperature.

#define relayPin 3 // Pin that relay IN1 is attached to.

bool relay = false;

void setup() {
  pinMode(relayPin, OUTPUT); // Use pin 2 to trigger relay (Connected to IN1 or IN2 of relay module)
  digitalWrite(relayPin, HIGH); // Ensure relay starts disabled

  Serial.begin(9600);
  while (!Serial) {
    delay(10);
  }
  Serial.println("AM2315 Test!");

  if (! am2315.begin()) {
     Serial.println("Sensor not found, check wiring & pullups!");
     while (1);
  }

  // begin() does a test read, so need to wait 2secs before first read
  delay(2000);
}

void loop() {
  float temperatureC, tempF, humidity;

  if (! am2315.readTemperatureAndHumidity(&temperatureC, &humidity)) {
    Serial.println("Failed to read data from AM2315");
    return;
  }

  tempF = (temperatureC * 9/5) + 32; // Convert from C to F

  //Serial.print("Temp *C: "); Serial.println(temperature);
  Serial.print("Temp *F: "); Serial.println(tempF);
  Serial.print("Hum %: "); Serial.println(humidity);

  if (tempF > tempThreshold) {
  //if (humidity > 50) { // Humidity is faster to change for testing (with breath).
    relayOn();
  } else {
    relayOff();
  }

  if (useInterval) {
    long minute = 60000; // 60 seconds
    delay(intervalMinutes * minute);
  } else {
    delay(2000); // wait at least 2secs for sensor before next read.
  }
}

void relayOn() {
    if (!relay) {
      digitalWrite(relayPin, LOW); // This relay board uses LOW to trigger the relay ON
      Serial.println("Relay On");
      relay = true;
    }
}

void relayOff() {
  if (relay) {
    digitalWrite(relayPin, HIGH); // This relay board uses HIGH to turn relay off.
    Serial.println("Relay Off");
    relay = false;
  }
}