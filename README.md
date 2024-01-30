# fanController

This is a simple Arduino project intended to control an exhaust fan when the temperature rises above a set point.

I used an old Arduino Diecimila, an AM2315 Humidity / Temperature Sensor, and a 2 Channel 5V Relay Module.

The temperature threshold, interval (both fan run time and interval between temperature checks) and the pin the relay is connected to are configured by adjusting these lines in the code:

``` C
#define tempThreshold 90 // Setpoint to trigger relay on if temp is above (in degrees F)
#define useInterval true // If true wait for intervalMinutes before rechecking. If false, recheck every 2 seconds.
#define intervalMinutes 10 // Interval in minutes to wait before rechecking temperature.

#define relayPin 3 // Pin that relay IN1 is attached to.
```


