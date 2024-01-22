#include <ezButton.h>
#include <Wire.h>
#include <ServoTimer2.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include "util/twi.h"
#define STEPS 200
Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x60);
Adafruit_StepperMotor *myMotor;
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int stepperPot = A0;  //controls stepper motor
int sensorpin = 3;          // sensor is attached to Pin 3
int sensorvalue;            //sensor's threshold

ServoTimer2 myServo;          // create servo object to control a servo
const int BUTTON_PIN = 4;     // Arduino pin connected to button's pin
ezButton button(BUTTON_PIN);  // create ezButton object that attach to pin 4;
int lastButtonState;          // the previous state of button
int currentButtonState;       // the current state of button

unsigned long time_0 = 0, time_1 = 0;
int speed_ = 1;
unsigned long period = 10;
int direction_ = 1;
bool state_ = false;
int tilt = 0;
float EMA_a = 0.6;
int EMA_S = 0;
int new_tilt = 0;
volatile int real_tilt = 0;

ISR(TIMER1_COMPA_vect) {
  OCR1A += 50000;  // Advance The COMPA Register handle The Timer Interrupt, 25 ms

  myServo.write(real_tilt);
}

void updatePeriodAndScreen() {
  lcd.setCursor(13, 0);
  if (state_)
    lcd.print("ON ");

  else {
    lcd.print("OFF");
    myMotor->release();
  }

  char msg[16] = "";
  tilt = analogRead(A3);
  EMA_S = (EMA_a * tilt) + ((1 - EMA_a) * EMA_S);


  int new_tilt = map(EMA_S, 0, 1023, 0, 45);  // scales it to use it with the servo (values between 0 and 45)
  lcd.setCursor(0, 1);
  sprintf(msg, "Tilt: %02d", new_tilt);  // printing 09 when angle is below 10
  lcd.print(msg);

  lcd.setCursor(0, 0);  // move cursor to first row, first character
  lcd.print("RPM: ");
  lcd.print((float)abs(speed_) / 100);
  if (speed_ < 0) {
    direction_ = -1;
    lcd.print("CCW");
  } else {
    lcd.print("CW ");
    direction_ = 1;
  }

  int speedValue = analogRead(stepperPot);
  int new_speed = map(speedValue, 0, 1023, -400, 400);  // scale the value of pot to control the rotation speed
  if ((speed_ != new_speed) && (abs(new_speed) > 0))    // if the speed was changed
  {
    speed_ = new_speed;               // set the speed of the motor
    period = 1875 / abs(speed_) - 3;  //time between steps of the motor
  }
}


void updatePeriodAndDirection() {
  int speedValue = analogRead(stepperPot);
  int new_speed = map(speedValue, 0, 1023, -400, 400);
  if ((speed_ != new_speed) && (abs(new_speed) > 0)) {
    speed_ = new_speed;

    period = 1875 / abs(speed_) - 3;

    lcd.setCursor(13, 0);
    if (state_)
      lcd.print("ON ");

    else {
      lcd.print("OFF");
      myMotor->release();
    }

    if (speed_ < 0) {
      direction_ = -1;
    } else {
      direction_ = 1;
    }
  }
}


void runMotor() {
  while (state_) {
    lastButtonState = currentButtonState;
    currentButtonState = digitalRead(4);

    if ((millis() - time_1) >= 1000) {
      updatePeriodAndDirection();
    time_1 = millis();
    }

    if ((millis() - time_0) >= period) {
      if (state_ && (direction_ > 0))
        myMotor->onestep(FORWARD, MICROSTEP);
      else if (state_)
        myMotor->onestep(BACKWARD, MICROSTEP);
      time_0 = millis();
    }

    if (lastButtonState == HIGH && currentButtonState == LOW) {
      state_ = !state_;
      if ((millis() - time_1) >= 1000) {
        updatePeriodAndDirection();
      time_1 = millis();
      }
    }
  }
}


void runMotorFast() {
  while (state_) {
    lastButtonState = currentButtonState;
    currentButtonState = digitalRead(4);
    if ((millis() - time_1) >= 1000) {
      updatePeriodAndDirection();
    time_1 = millis();
    }
    if (state_ && (direction_ > 0))
      myMotor->onestep(FORWARD, MICROSTEP);
    else if (state_)
      myMotor->onestep(BACKWARD, MICROSTEP);

    if (lastButtonState == HIGH && currentButtonState == LOW) {
      state_ = !state_;
      if ((millis() - time_1) >= 1000) {
        updatePeriodAndDirection();
      time_1 = millis();
      }
    }
  }
}


void eightWellsChip() {
  while (state_) {
    if ((millis() - time_1) >= 1000) {
      updatePeriodAndScreen();
      time_1 = millis();
    }

    for (int y = 0; y < 950; y++) {
      lastButtonState = currentButtonState;
      currentButtonState = digitalRead(4);

      if (state_ && (direction_ > 0))
        myMotor->onestep(FORWARD, MICROSTEP);
      else if (state_)
        myMotor->onestep(BACKWARD, MICROSTEP);

      if (lastButtonState == HIGH && currentButtonState == LOW) {
        state_ = !state_;
        if ((millis() - time_1) >= 1000) {
          updatePeriodAndDirection();
        time_1 = millis();
    }
      }
    }

    for (int i = 0; i < 650; i++) {
      lastButtonState = currentButtonState;
      currentButtonState = digitalRead(4);

      if ((millis() - time_0) >= period) {
        if (state_ && (direction_ > 0))
          myMotor->onestep(FORWARD, MICROSTEP);
        else if (state_)
          myMotor->onestep(BACKWARD, MICROSTEP);

        time_0 = millis();
        int speedValue = analogRead(stepperPot);
        int new_speed = map(speedValue, 0, 1023, -400, 400);
        tilt = analogRead(A3);
        EMA_S = (EMA_a * tilt) + ((1 - EMA_a) * EMA_S);


        int new_tilt = map(EMA_S, 0, 1023, 0, 45);  // scales it to use it with the servo (values between 0 and 45)

        if ((millis() - time_1) >= 1000) {
          updatePeriodAndDirection();
        time_1 = millis();
    }
      } else i--;
      if (lastButtonState == HIGH && currentButtonState == LOW) {
        state_ = !state_;
        if ((millis() - time_1) >= 1000) {
          updatePeriodAndDirection();
        time_1 = millis();
    }
      }
    }
  }
}


void homing() {
  myMotor->release();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("HOMING");
  while (digitalRead(sensorpin) != 0) {
    myMotor->onestep(FORWARD, MICROSTEP);  // rotate the motor by one step
  }
}


void setup() {
  Serial.begin(9600);          // initialize serial
  button.setDebounceTime(90);  // set debounce time to 90 milliseconds
  myServo.attach(9);           // attaches the servo on pin 9 to the servo object
  myServo.write(tilt);         //sets the servo to 0 deg tilt

  Wire.begin();
  Wire.setClock(400000UL);  //High Speed I2C mode, increase the sample rate to 4kHz.

  AFMS.begin();
  myMotor = AFMS.getStepper(STEPS, 1);
  myMotor->setSpeed(1);

  //homing();// setting the platform to the home position;
  myMotor->release();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(13, 0);
  lcd.print("OFF");
  currentButtonState = digitalRead(4);
  EMA_S = analogRead(A3);
  TCCR1A = 0;           // Init Timer1A
  TCCR1B = 0;           // Init Timer1B
  TCCR1B |= B00000010;  // Prescaler = 8
  OCR1A = 50000;        // Timer Compare1A Register
  TIMSK1 |= B00000010;  // Enable Timer COMPA Interrupt
}

void loop() {
  lastButtonState = currentButtonState;
  currentButtonState = digitalRead(4);

  //myServo.write(0); //use this line only in testing mode

  int analogTiltPot = analogRead(A3);
  EMA_S = (EMA_a * analogTiltPot) + ((1 - EMA_a) * EMA_S);
  //new_tilt = map(EMA_S, 0, 1023, 0, 45);  // scales it to use it with the servo (values between 0 and 45)
  real_tilt = map(EMA_S, 0, 1023, 750, 1500);


  if ((millis() - time_1) >= 1000) {
    updatePeriodAndScreen();
    time_1 = millis();
  }


  if (lastButtonState == HIGH && currentButtonState == LOW) {
    state_ = !state_;  // toggle state
    if ((millis() - time_1) >= 1000) {
      updatePeriodAndScreen();
      time_1 = millis();
    }
    //eightWellsChip();
    runMotor();
    //runMotorFast();
  }
}
