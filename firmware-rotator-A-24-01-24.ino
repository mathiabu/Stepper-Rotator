#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility\Adafruit_MS_PWMServoDriver.h"
#include <LiquidCrystal_I2C.h>
// Steps for a full rotation with 0.9 deg step angle
#define STEPS 400
// Microstepping divides one step by 16
#define MICROSTEPS 16
// delay in ms for debouncing
#define BUTTON_DELAY 200

// Set motor shield I2C adress to 0x60
Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x60);
Adafruit_StepperMotor *myMotor;

// LCD pins <--> Arduino pins
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int pot    = A2;    //controls stepper motor
const int button = 2;     //linked to an interrupt

unsigned long time_0 = 0;
int speed_ = 1, new_speed = 1;
unsigned long period = 10;
byte direction_ = FORWARD;
volatile bool state_ = false, state_old = false;
volatile unsigned long button_time = 0;

// ISR to change state of the firmware when button is pressed
void toggleMotor() {
  if((millis() - button_time) < BUTTON_DELAY)
    return;
  state_old = state_;
  state_ ^= 1;
  button_time = millis();      
}

void setup() {
  // Set PWM modulation frequency to 500 Hz
  AFMS.begin(500);
  // put your setup code here, to run once:
  myMotor = AFMS.getStepper(STEPS/MICROSTEP,1);
  myMotor->setSpeed(1);
  myMotor->release();
  // set the time for button debouncing
  button_time = millis();
  // Initialize digitial input and ISR for button
  pinMode(button, INPUT);
  attachInterrupt(digitalPinToInterrupt(button), toggleMotor, FALLING);
  // Initialize analog input for potentiometer
  pinMode(pot, INPUT);
  analogReference(DEFAULT);
  // Initialize LCD display
  lcd.init();
  lcd.backlight();
  lcd.setCursor(12, 0);
  lcd.print("OFF");
}

void loop() { 
  // Machine is turned on: Motor off and display "off" on display
  if((state_ == false) && (state_old == true)) {
    lcd.setCursor(12, 0);
    lcd.print("OFF ");
    myMotor->release();
    state_old = false;
  }
  // Machine is turned on: Display "on", lock user input and start rotating
  else if((state_ == true) && (state_old == false)) {
    lcd.setCursor(12, 0);
    lcd.print("ON ");
    state_old = true;
  }
  // No change: Read potentiometer and set rotation speed
  else if((state_ == false) && (state_old == false)) {
    // Map reading of input to -2.5 to 2.5 rpm (multiplied by 100)
    new_speed = map(analogRead(pot), 1023, 0, -250, 250);

    if ((speed_ != new_speed) && (abs(new_speed) > 0)) // if the speed was changed
    { 
      speed_ = new_speed;
      // Calculate time between two steps in ms
      period = 6000000/abs(speed_)/STEPS/MICROSTEPS-2;
    
      lcd.setCursor(0, 0);         // move cursor to second row
      lcd.print("Dir: ");
      // Set direction based on polarity: negative: counterclockwise rotation (CCW). positive: clockwise rotation (CW)
      if(speed_ < 0) {
        direction_ = BACKWARD;
        lcd.print("CCW");
      }
      else {
        lcd.print("CW ");
        direction_ = FORWARD;
      }
     
      lcd.setCursor(0, 1);         // move cursor to second row
      lcd.print("Speed: ");
      lcd.print((float) abs(speed_)/100);
      lcd.setCursor(13, 1);
      lcd.print("rpm");
    }
  }
  // If GUI is locked: Check if elapsed time since last step > period between steps and move one step in the selected direction
  else {
    if((millis() - time_0) >= period) {
        myMotor->onestep(direction_, MICROSTEP);
        time_0 = millis();
    }
  }

}
