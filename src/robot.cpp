/*
  robot.cpp - Library for EZRobotArm MK2.
  Created by Larry da Ponte, November 17, 2019.
  Released into the public domain.
*/

#include "Adafruit_PWMServoDriver.h"
#include "Arduino.h"
#include "robot.h"
#include <Wire.h>
#include "EEPROM.h"

Robot::Robot()
{
  pwm = Adafruit_PWMServoDriver();
}

bool Robot::inputAvailable()
{
  return Serial.available();
}

int Robot::readInput()
{
  return Serial.read();
}

void Robot::start()
{
    pwm.begin();
    pwm.setPWMFreq(FREQUENCY);

    Serial.begin(115200);
    Serial.println("starting...");
    char isSaved[6];
    int eeAddress = 0;
    EEPROM.get(eeAddress, isSaved);

    if (strcmp(isSaved, _header) == 0) {
        Serial.println("Loading saved servo information...");

        eeAddress += sizeof(_header); 
        for(int i = 0; i < 4; i++) {

            EEPROM.get(eeAddress, _minPosition[i]);
            eeAddress+= sizeof(_minPosition[i]);

            EEPROM.get(eeAddress, _maxPosition[i]);
            eeAddress+= sizeof(_maxPosition[i]);

            EEPROM.get(eeAddress, _position[i]);
            eeAddress+= sizeof(_position[i]);

            EEPROM.get(eeAddress, _speed[i]);
            eeAddress+= sizeof(_speed[i]);

            pwm.setPWM(i, 0, _position[i]);

            sprintf(_printdata, "Servo %d min: %d, max: %d, pos: %d, speed: %d", i, _minPosition[i], _maxPosition[i], _position[i], _speed[i]);
            Serial.println(_printdata);
        }  
    } else {
      Serial.println("No saved servo information found");
    }
}

void Robot::saveSettings()
{
  Serial.println("Saving min and max servo values");
  int eeAddress = 0;
  EEPROM.put(eeAddress, _header);
  eeAddress += sizeof(_header); 
  for(int i = 0; i < 4; i++) {

      EEPROM.put(eeAddress, _minPosition[i]);
      eeAddress+= sizeof(_minPosition[i]);

      EEPROM.put(eeAddress, _maxPosition[i]);
      eeAddress+= sizeof(_maxPosition[i]);

      EEPROM.put(eeAddress, _position[i]);
      eeAddress+= sizeof(_position[i]);

      EEPROM.put(eeAddress, _speed[i]);
      eeAddress+= sizeof(_speed[i]);
  }
}

void Robot::setServo(int servo)
{
  _servo = servo;

  sprintf(_printdata, "Servo %d selected", servo);
  Serial.println(_printdata);
}

void Robot::setPosition(int servo, int position)
{
  if (position > _maxPosition[servo])
  {
    position = _maxPosition[servo];
  }
  else if (position < _minPosition[servo])
  {
    position = _minPosition[servo];
  }

  _position[servo] = position;
  pwm.setPWM(servo, 0, position);

  sprintf(_printdata, "Setting the position of servo %d to %d", servo, position);
  Serial.println(_printdata);
}

void Robot::setPosition(int position)
{
  setPosition(_servo, position);
}

int Robot::getPosition()
{
  return getPosition(_servo);
}

int Robot::getPosition(int servo)
{
  return _position[servo];
}

void Robot::setMinPosition(int servo, int position)
{
  _minPosition[servo] = position;

  sprintf(_printdata, "Setting servo %d min to: %d", servo, position);
  Serial.println(_printdata);
}

void Robot::setMinPosition(int position)
{
  setMinPosition(_servo, position);
}

void Robot::setMaxPosition(int servo, int position)
{
  _maxPosition[_servo] = position;

  sprintf(_printdata, "Setting servo %d max to: %d", servo, position);
  Serial.println(_printdata);
}

void Robot::setMaxPosition(int position)
{
  setMaxPosition(_servo, position);
}

void Robot::setSpeed(int speed)
{
  setSpeed(_servo, speed);
}

int Robot::getSpeed()
{
  return _speed[_servo];
}

void Robot::setSpeed(int servo, int speed)
{
  if(speed <= 0)
  {
    speed = 1;
  } 
  else if (speed > 10)
  {
    speed = 10;
  }

  _speed[_servo] = speed;

  sprintf(_printdata, "Setting speed of servo %d to %d", servo, speed);
  Serial.println(_printdata);
}

void Robot::displaySettings()
{
  for(int i = 0; i < 4; i++) {
    sprintf(_printdata, "Servo %d min: %d, max: %d, pos: %d, speed: %d", i, _minPosition[i], _maxPosition[i], _position[i], _speed[i]);
    Serial.println(_printdata);
  }
}

void Robot::resetSettings(int servo)
{
  _position[servo] = 0;
  _minPosition[servo] = 0;
  _maxPosition[servo] = 1000;
  _speed[servo] = 1;

  sprintf(_printdata, "Resetting servo %d values", servo);
  Serial.println(_printdata);
}

void Robot::resetSettings()
{
  resetSettings(_servo);
}