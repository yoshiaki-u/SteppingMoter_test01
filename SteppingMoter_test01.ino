#include <Stepper.h>
const int stepsPerRevolution = 32;
const int stepsPerGearedRevolution = 32 * 64; //gear reduction ration 1/64
const int stepsPerCycle = stepsPerGearedRevolution / 8; // 1/8 turn at one time to avoid WDT reset
#define PIN_STP_IN1 12
#define PIN_STP_IN2 13
#define PIN_STP_IN3 14
#define PIN_STP_IN4 15

// initialize the stepper library on pins 
Stepper myStepper(stepsPerGearedRevolution, PIN_STP_IN1, PIN_STP_IN3, PIN_STP_IN2, PIN_STP_IN4);
 
void setup() {
 // initialize the serial port:
 Serial.begin(115200); 
 myStepper.setSpeed(10);
}
 
void loop() {
  Serial.println("Rotate CW");
  // To avoid watchdog reset and allow utility functions to run, number of steps at once should be limited.
  for(int i = 0; i < 8; i++){
    myStepper.step(stepsPerCycle);
    // ウォッチドッグタイマによるリセットを防ぐために1/8回転毎にyield()を実行する
    yield();
  }
  delay(500);
  Serial.println("Rotate ACW");
  for(int i = 0; i < 8; i++){
    myStepper.step(-stepsPerCycle);
    yield();
  }
  delay(500);
  Serial.println("END");
}