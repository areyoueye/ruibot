#include <IRremote.h>

#define REMOTE_UP       0xFF629D
#define REMOTE_LEFT     0xFF22DD
#define REMOTE_RIGHT    0xFFC23D
#define REMOTE_DOWN     0xFFA857
#define REMOTE_1        0xFF6897
#define REMOTE_2        0xFF9867
#define REMOTE_3        0xFFB04F
#define REMOTE_4        0xFF30CF
#define REMOTE_5        0xFF18E7
#define REMOTE_6        0xFF7A85
#define REMOTE_7        0xFF10EF
#define REMOTE_8        0xFF38C7
#define REMOTE_9        0xFF5AA5
#define REMOTE_STAR     0xFF42BD
#define REMOTE_POUND    0xFF52AD


#define R_MOTOR_H 8
#define R_MOTOR_L 9
#define R_MOTOR_DRIVE 10

#define L_MOTOR_H 6
#define L_MOTOR_L 7
#define L_MOTOR_DRIVE 5




int RECV_PIN = 2;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  
  pinMode(R_MOTOR_H, OUTPUT);
  pinMode(R_MOTOR_L, OUTPUT);
  pinMode(R_MOTOR_DRIVE, OUTPUT);
}

void left_forward() {
  digitalWrite(L_MOTOR_H, HIGH);
  digitalWrite(L_MOTOR_L, LOW);
}

void right_forward() {
  digitalWrite(R_MOTOR_H, HIGH);
  digitalWrite(R_MOTOR_L, LOW);
}

void left_backward() {
  digitalWrite(L_MOTOR_H, LOW);
  digitalWrite(L_MOTOR_L, HIGH);
}

void right_backward() {
  digitalWrite(R_MOTOR_H, LOW);
  digitalWrite(R_MOTOR_L, HIGH);
}

void forward() {
  right_forward();
  left_forward();
}

void backward() {
  right_backward();
  left_backward();
}

void turn_right() {
  right_backward();
  left_forward();
}

void turn_left() {
  right_forward();
  left_backward();
}


unsigned int go = 0;
void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);

    switch (results.value) {
      case REMOTE_UP:
        forward();
        go = 1;
        break;
      case REMOTE_DOWN:
        backward();
        go = 1;
        break;
      case REMOTE_LEFT:
        turn_left();
        go = 1;
        break;
      case REMOTE_RIGHT:
        turn_right();
        go = 1;
        break;
      case 0xFFFFFFFF:
        break;
      default:
        go = 0;
      break;  
    }
    if (go == 0) {
      analogWrite(L_MOTOR_DRIVE, 0);
      analogWrite(R_MOTOR_DRIVE, 0);
    } else {
      analogWrite(L_MOTOR_DRIVE, 250);
      analogWrite(R_MOTOR_DRIVE, 250);
    }
    irrecv.resume();
  } else {
      analogWrite(L_MOTOR_DRIVE, 0);
      analogWrite(R_MOTOR_DRIVE, 0);
  }
  delay(100);
}
