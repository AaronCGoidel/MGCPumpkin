#include <Servo.h>

#define SERVO_OUT 10
#define TRIGGER_OUT 9
#define ECHO_IN 8

Servo clubServo;

int theta = 0;

void swing() {
  clubServo.write(0);
  delay(500);
  clubServo.write(180);
  delay(1000);
  clubServo.write(90);
}

void setup() {
  clubServo.attach(SERVO_OUT, 1000, 2500);

  pinMode(TRIGGER_OUT, OUTPUT);
  pinMode(ECHO_IN, INPUT);

  Serial.begin(9600);

  clubServo.write(90);
  delay(2000);
}

int get_dist(){
  digitalWrite(TRIGGER_OUT, LOW);
  delayMicroseconds(10);
  
  digitalWrite(TRIGGER_OUT, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_OUT, LOW);

  long dt = pulseIn(ECHO_IN, HIGH);
  int dx = dt*.034/2;

  return dx;
}

bool verify_obj(int min_dist) {
  for (int i = 0; i < 10; i++) {
    if (get_dist() > min_dist) {
      return false;
    }
    delay(100);
  }
  return true;
}

void loop() {
  int dx = get_dist();
  int dist_cutoff = 10;
  
  Serial.print("Distance: ");
  Serial.print(dx);

  if (dx <= dist_cutoff) {
    if (verify_obj(dist_cutoff)){
      swing();
      delay(1000);
    }
  }
}
