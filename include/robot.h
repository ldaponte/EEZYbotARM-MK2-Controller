/*
  robot.h - Library for EZRobotArm MK2.
  Created by Larry da Ponte, November 17, 2019.
  Released into the public domain.
*/

#ifndef Robot_h
#define Robot_h
#define FREQUENCY 50

#include "Arduino.h"
#include "Adafruit_PWMServoDriver.h"

class Robot
{
    public:
        Robot();

        bool inputAvailable();
        int readInput();
        void resetSettings();
        void resetSettings(int servo);
        void setServo(int servo);
        void getServo();
        void setMinPosition(int position);
        void setMinPosition(int servo, int position);
        int getMinPosition();
        int getMinPosition(int servo);
        void setMaxPosition(int position);
        void setMaxPosition(int servo, int position);
        int getMaxPosition();
        int getMaxPosition(int servo);
        void setSpeed(int speed);
        void setSpeed(int servo, int speed);
        int getSpeed();
        void displaySettings();
        void saveSettings();
        void loadSettings();
        void setPosition(int position);
        int getPosition();
        int getPosition(int servo);
        void setPosition(int servo, int position);
        void start();

    private:
        int _servo = 0;

        int _position[4] = {0, 0, 0, 0};
        int _minPosition[4] = {0, 0, 0, 0};
        int _maxPosition[4] = {1000, 1000, 1000, 1000};
        int _speed[4] = {1, 1, 1, 1};

        char _printdata[100];
        char _header[6] = {'s', 'a', 'v', 'e', 'd', '\0'};

        Adafruit_PWMServoDriver pwm;
};

void loop(){}
void setup(){}

#endif