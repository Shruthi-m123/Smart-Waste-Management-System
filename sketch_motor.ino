#include <Servo.h>

Servo motor1;  // Motor 1: Servo for rotation (Segregation)
Servo motor2;  // Motor 2: Servo for holding and releasing the object
int plasticType = 0;  // Variable to store the type of plastic
int angle1 = 0;        // Variable to store the angle for Servo 1 (Segregation)
int angle2 = 0;        // Variable to store the angle for Servo 2 (Object Release)

void setup() {
  Serial.begin(9600);     // Initialize serial communication at 9600 baud
  motor1.attach(9);       // Attach Servo Motor 1 (Segregation) to pin 9
  motor2.attach(11);      // Attach Servo Motor 2 (Object Holding/Release) to pin 10

  motor1.write(0);        // Set initial position of Servo 1 to 0° (Segregation position)
  motor2.write(0);        // Set initial position of Servo 2 to 0° (Hold position)
  delay(3000);            // Wait for 1 second to ensure motors are at initial position
}

void loop() {
  // Check if serial data is available
  if (Serial.available() > 0) {
    plasticType = Serial.parseInt();   // Read the plastic type sent from Python

    // Map the plastic type (1-6) to specific angles for Servo 1 (Motor 1)
    switch (plasticType) {
      case 1:
        angle1 = 0;    // Plastic type 1 goes to angle 0° (Segregation position 1)
        break;
      case 2:
        angle1 = 45;   // Plastic type 2 goes to angle 30° (Segregation position 2)
        break;
      case 3:
        angle1 = 90;   // Plastic type 3 goes to angle 60° (Segregation position 3)
        break;
      case 4:
        angle1 = 135;   // Plastic type 4 goes to angle 90° (Segregation position 4)
        break;
      case 5:
        angle1 = 180;  // Plastic type 5 goes to angle 120° (Segregation position 5)
        break;
      default:
        angle1 = 0;    // Default to 0° if the input is invalid
        break;
    }

    // Move Motor 1 (Servo 1) to the calculated segregation angle
    motor1.write(angle1);
    delay(3000);            // Wait for 1 second to ensure Servo 1 reaches the position

    // After Motor 1 reaches its position, activate Motor 2 to release the object
    releaseObject(); // Wait here until Motor 2 completes its task

    // After releasing the object, return both motors to their initial position (0°)
    motor1.write(0);       // Return Motor 1 to its initial position (0°)
    motor2.write(0);       // Return Motor 2 to its initial position (Hold position)
    delay(3000);           // Wait for 1 second before processing the next plastic type
  }
}

// Function to release the object using Motor 2 (Servo 2)
void releaseObject() {
  motor2.write(25);     // Move Motor 2 to 90° to release the object
  delay(3000);          // Wait for 1 second to release the object
  motor2.write(0);      // Return Motor 2 to its initial position (Hold position)
  delay(2000);           // Wait for 0.5 second before returning to initial position
}
