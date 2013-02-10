int tree1 = 13;
int tree2 = 12;
int tree3 = 11;
int tree4 = 10;
int tree5 = 9;
int tree6 = 8;

int incomingByte;      // a variable to read incoming serial data into

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  // initialize the LED pin as an output:
  pinMode(tree1, OUTPUT);
  pinMode(tree2, OUTPUT);
  pinMode(tree3, OUTPUT);
  pinMode(tree4, OUTPUT);
  pinMode(tree5, OUTPUT);
  pinMode(tree6, OUTPUT);
}

void loop() {
  // see if there's incoming serial data:
  if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial.read();

    if (incomingByte == 'q') {
  digitalWrite(tree1,HIGH);
  delay(150);
    digitalWrite(tree1,LOW);
    }

    if (incomingByte == 'w') {
        digitalWrite(tree2,HIGH);
        delay(150);
        digitalWrite(tree2,LOW);
    }
   
        if (incomingByte == 'e') {
        digitalWrite(tree3,HIGH);
        delay(150);
        digitalWrite(tree3,LOW);
    }
   
        if (incomingByte == 'r') {
        digitalWrite(tree4,HIGH);
        delay(150);
        digitalWrite(tree4,LOW);
    }
   
        if (incomingByte == 't') {
        digitalWrite(tree5,HIGH);
        delay(150);
        digitalWrite(tree5,LOW);
    }
   
        if (incomingByte == 'y') {
        digitalWrite(tree6,HIGH);
        delay(150);
        digitalWrite(tree6,LOW);
    }
   
        if (incomingByte == 's') {
        digitalWrite(tree1,HIGH);
        digitalWrite(tree2,HIGH);
        delay(150);
        digitalWrite(tree1,LOW);
        digitalWrite(tree2,LOW);
    }
   
        if (incomingByte == 'd') {
        digitalWrite(tree2,HIGH);
        digitalWrite(tree3,HIGH);
        delay(150);
        digitalWrite(tree2,LOW);
        digitalWrite(tree3,LOW);
    }
   
        if (incomingByte == 'f') {
        digitalWrite(tree3,HIGH);
        digitalWrite(tree4,HIGH);
        delay(150);
        digitalWrite(tree3,LOW);
        digitalWrite(tree4,LOW);
    }

        if (incomingByte == 'g') {
        digitalWrite(tree4,HIGH);
        digitalWrite(tree5,HIGH);
        delay(150);
        digitalWrite(tree4,LOW);
        digitalWrite(tree5,LOW);
    }
   
        if (incomingByte == 'h') {
        digitalWrite(tree5,HIGH);
        digitalWrite(tree6,HIGH);
        delay(150);
        digitalWrite(tree5,LOW);
        digitalWrite(tree6,LOW);
    }
   
        if (incomingByte == 'u') {
        digitalWrite(tree1,HIGH);
        digitalWrite(tree2,HIGH);
        digitalWrite(tree5,HIGH);
        digitalWrite(tree6,HIGH);
        delay(150);
        digitalWrite(tree1,LOW);
        digitalWrite(tree2,LOW);
        digitalWrite(tree5,LOW);
        digitalWrite(tree6,LOW);
    }
   
        if (incomingByte == 'i') {
        digitalWrite(tree1,HIGH);
        digitalWrite(tree2,HIGH);
        digitalWrite(tree4,HIGH);
        digitalWrite(tree5,HIGH);
        delay(150);
        digitalWrite(tree1,LOW);
        digitalWrite(tree2,LOW);
        digitalWrite(tree4,LOW);
        digitalWrite(tree5,LOW);
    }
   
        if (incomingByte == 'j') {
        digitalWrite(tree2,HIGH);
        digitalWrite(tree3,HIGH);
        digitalWrite(tree5,HIGH);
        digitalWrite(tree6,HIGH);
        delay(150);
        digitalWrite(tree2,LOW);
        digitalWrite(tree3,LOW);
        digitalWrite(tree5,LOW);
        digitalWrite(tree6,LOW);
    }
   
        if (incomingByte == 'o') {
        digitalWrite(tree5,HIGH);
        digitalWrite(tree3,HIGH);
        digitalWrite(tree4,HIGH);
        delay(150);
        digitalWrite(tree5,LOW);
        digitalWrite(tree3,LOW);
        digitalWrite(tree4,LOW);
    }
   
        if (incomingByte == 'p') {
        digitalWrite(tree2,HIGH);
        digitalWrite(tree3,HIGH);
        digitalWrite(tree4,HIGH);
        delay(150);
        digitalWrite(tree2,LOW);
        digitalWrite(tree3,LOW);
        digitalWrite(tree4,LOW);
    }
   
        if (incomingByte == 'b') {
        digitalWrite(tree1,HIGH);
        digitalWrite(tree6,HIGH);
        delay(150);
        digitalWrite(tree1,LOW);
        digitalWrite(tree6,LOW);
    }
   
        if (incomingByte == 'c') {
        digitalWrite(tree1,HIGH);
        digitalWrite(tree3,HIGH);
        delay(150);
        digitalWrite(tree1,LOW);
        digitalWrite(tree3,LOW);
    }

        if (incomingByte == 'v') {
        digitalWrite(tree4,HIGH);
        digitalWrite(tree6,HIGH);
        delay(150);
        digitalWrite(tree4,LOW);
        digitalWrite(tree6,LOW);
    }
        if (incomingByte == 'a') {
  digitalWrite(tree1,HIGH);
  digitalWrite(tree2,HIGH);
  digitalWrite(tree3,HIGH);
  digitalWrite(tree4,HIGH);
  digitalWrite(tree5,HIGH);
  digitalWrite(tree6,HIGH);
  delay(150);
  digitalWrite(tree1,LOW);
  digitalWrite(tree2,LOW);
  digitalWrite(tree3,LOW);
  digitalWrite(tree4,LOW);
  digitalWrite(tree5,LOW);
  digitalWrite(tree6,LOW);
    }
   
  }
}
