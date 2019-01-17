// Simple gamepad example that demonstraits how to read five Arduino
// digital pins and map them to the Arduino Joystick library.
//
// The digital pins 2 - 6 are grounded when they are pressed.
// Pin 2 = UP
// Pin 3 = RIGHT
// Pin 4 = DOWN
// Pin 5 = LEFT
// Pin 6 = FIRE
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2016-11-24
//--------------------------------------------------------------------

#include <Joystick.h>
#include <NintendoExtensionCtrl.h>

ClassicController classic;
bool mashDownMode = false;
int mashValue = 0;

void setup() {
  Serial.begin(115200);

  Joystick.begin(false);

  classic.begin();
  while (!classic.connect()) {
    Serial.println("Classic Controller not detected!");
    delay(1000);
  }
}

int rightStick(uint8_t input) {
  if (input > 24)
    return 127;
  else if (input > 20)
    return 64;
  else if (input < 8)
    return -127;
  else if (input < 12)
    return -64;
  return 0;
}

int leftStick(uint8_t input) {
  if (input > 45)
    return 127;
  else if (input > 35)
    return 64;
  else if (input < 15)
    return -127;
  else if (input < 25)
    return -64;
  return 0;
}

void loop() {
  boolean success = classic.update();

  if (!success) {
    //Serial.println("Controller disconnected!");
    classic.reconnect();
    //delay(100);
  } else {
    //classic.printDebug();

    if (classic.buttonHome()) {
      //Modifier

      Joystick.setButton(12, classic.buttonPlus()); //Home
      Joystick.setButton(13, classic.buttonMinus()); //Capture

      if (classic.buttonA()) {
        mashDownMode = true;
      } else if (classic.buttonB()) {
        mashDownMode = false;
        Joystick.setYAxis(0);
      }

    } else {

      if (mashDownMode) {
        mashValue += 10;
        if(mashValue > 127)
        mashValue = 0;
        
        Joystick.setXAxis(0);
        Joystick.setYAxis(mashValue);
        Joystick.setZAxis(0);
        Joystick.setZAxisRotation(0);
      } else {
        Joystick.setButton(2, classic.buttonA());
        Joystick.setButton(1, classic.buttonB());
        Joystick.setButton(3, classic.buttonX());
        Joystick.setButton(0, classic.buttonY());

        Joystick.setButton(4, classic.buttonL());
        Joystick.setButton(5, classic.buttonR());
        Joystick.setButton(6, classic.buttonZL());
        Joystick.setButton(7, classic.buttonZR());

        Joystick.setButton(9, classic.buttonPlus());
        Joystick.setButton(8, classic.buttonMinus());
        //Home has been changed to a modifier

        Joystick.setXAxis(leftStick(classic.leftJoyX()));
        Joystick.setYAxis(leftStick(classic.leftJoyY()) * -1);
        Joystick.setZAxis(rightStick(classic.rightJoyX()));
        Joystick.setZAxisRotation(rightStick(classic.rightJoyY()) * -1);

        if (classic.dpadUp()) {
          if (classic.dpadLeft())
            Joystick.setHatSwitch(7);
          else if (classic.dpadRight())
            Joystick.setHatSwitch(1);
          else
            Joystick.setHatSwitch(0);
        } else if (classic.dpadDown()) {
          if (classic.dpadLeft())
            Joystick.setHatSwitch(5);
          else if (classic.dpadRight())
            Joystick.setHatSwitch(3);
          else
            Joystick.setHatSwitch(4);
        } else if (classic.dpadRight())
          Joystick.setHatSwitch(2);
        else if (classic.dpadLeft())
          Joystick.setHatSwitch(6);
        else
          Joystick.setHatSwitch(-1);
      }
    }
  }

  Joystick.sendState();

  delay(1);
}
