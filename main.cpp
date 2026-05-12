#include "mbed.h"
#include "Ultrasonic.h"
#include "Motor.h"
#include <cstdio>

// Ultrasonic sensor pins
#define TRIG_PIN    D9
#define ECHO_PIN    D10

// Motor 1 driver pins 
#define MOTOR1_PWM   D5
#define MOTOR1_FWD   D3
#define MOTOR1_REV   D4

// Motor 2 driver pins 
#define MOTOR2_PWM   D6
#define MOTOR2_FWD   D7
#define MOTOR2_REV   D8

#define FORWARD_SPEED      0.4f

int main() {
    Ultrasonic sensor(TRIG_PIN, ECHO_PIN);
    
    // Initialize both motors
    Motor motor1(MOTOR1_PWM, MOTOR1_FWD, MOTOR1_REV);
    Motor motor2(MOTOR2_PWM, MOTOR2_FWD, MOTOR2_REV);
    
    while (true) {
        int distance_cm = sensor.getDistance();
        
        if (distance_cm <=15) {
            // Sensor error - stop both motors
            motor1.stop();
            motor2.stop();
            printf("Sensor error! Both motors stopping.\r\n");
        }
        else {
            // Clear path - move forward with both motors
           motor1.forward(FORWARD_SPEED);
           motor2.forward(FORWARD_SPEED);
           printf("Object at %d cm - BOTH MOTORS MOVING FORWARD at %.1f%%\r\n", 
                   distance_cm, FORWARD_SPEED * 100);
        }
        
        ThisThread::sleep_for(100ms);
    }
}
