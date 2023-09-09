//#include <NewPing.h>

// Ultrasonic sensor pin configuration
#define TRIGGER_PIN 2
#define ECHO_PIN 3
#define MAX_DISTANCE 200

// Motor driver pin configuration
#define ENA 5   // Enable pin for Motor A
#define IN1 6   // Input 1 pin for Motor A
#define IN2 7   // Input 2 pin for Motor A
#define IN3 8   // Input 3 pin for Motor B
#define IN4 9   // Input 4 pin for Motor B
#define ENB 10  // Enable pin for Motor B

// Buzzer pin configuration
#define BUZZER_PIN 4

// Speed control
#define MAX_SPEED 255    // Maximum motor speed
#define SLOW_SPEED 150   // Slow motor speed when obstacle is detected
#define STOP_SPEED 0     // Speed to stop the motors

//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
    pinMode(TRIGGER_PIN, OUTPUT);
  Serial.begin (9600);
}

void loop() {
  delay(50);
//  unsigned int distance = sonar.ping_cm();  // Measure distance in centimeters
    long x, inches; 
    inches = microsecs_to_inches(x);
     int distance = inches;
    Serial.println(distance);

  if (distance >=10) {
    // No obstacle or out of range
    moveForward(MAX_SPEED);
    digitalWrite(BUZZER_PIN, LOW);
//    Serial.println("max");
//    Serial.println(inches);
  } else if (distance < 10 && distance > 5) {
    // Obstacle very close, stop and activate buzzer
   
     moveForward(SLOW_SPEED);
    digitalWrite(BUZZER_PIN, HIGH);
//    Serial.println(distance);
  } else {
    // Obstacle detected, slow down and activate buzzer
     stop();
    digitalWrite(BUZZER_PIN, LOW);
//    Serial.println(distance);
   
  }
}

// Function to move the car forward
void moveForward(int speed) {
  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

// Function to stop the car
void stop() {
  analogWrite(ENA, STOP_SPEED);
  analogWrite(ENB, STOP_SPEED);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}


double microsecs_to_inches(long duration)
{
  digitalWrite(TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  duration = pulseIn(ECHO_PIN, HIGH);
  return duration / 74 / 2;
}
