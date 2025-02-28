#include <Servo.h>
#include <Wire.h>

#define R1 2
#define R2 3
#define L1 4
#define L2 5

#define trigPin 9
#define echoPin 10

#define servoPin 6
Servo myServo;

long duration;
int distance, distanceRight, distanceLeft;

void setup() {
  // Set motor control pins as output
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);

  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Attach the servo motor
  myServo.attach(servoPin);
  myServo.write(90);  // Set servo to forward position (90 degrees)

  // Initialize serial for debugging
  Serial.begin(9600);

 
}

void loop() {
  distance = getDistance();

  if (distance > 0 && distance <= 30) {
    moveStop();
    delay(500);
    moveBackward();
    delay(200);
    moveStop();
    distanceRight = lookRight();
    distanceLeft = lookLeft();
delay(500);
   

    if (distanceRight > distanceLeft) {
      turnRight();
    } else {
      turnLeft();
    }

    delay(300);
    moveStop();
  } else {
    moveForward();
  }

  delay(50);
}

// Function to get the distance from the ultrasonic sensor
int getDistance() {
  // Trigger the ultrasonic pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the echo time with a timeout of 20000 microseconds
  duration = pulseIn(echoPin, HIGH, 20000);  // Timeout in case of no echo

  // If duration is zero, no echo was received
  if (duration == 0) {
    Serial.println("No echo received");
    return 0;
  }

  // Calculate the distance in cm
  int distance = duration * 0.034 / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);

  return distance;
}

// Look to the right
int lookRight() {
  myServo.write(0);
  delay(500);
  int distance = getDistance();
  myServo.write(90);  // Reset to forward position
  return distance;
}

// Look to the left
int lookLeft() {
  myServo.write(180);
  delay(500);
  int distance = getDistance();
  myServo.write(90);  // Reset to forward position
  return distance;
}

// Move functions
void moveForward() {
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
}

void moveBackward() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
}

void turnRight() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
}

void turnLeft() {
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
}

void moveStop() {
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
}


