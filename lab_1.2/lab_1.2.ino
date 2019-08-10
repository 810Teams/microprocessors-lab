/**
 * MICROPROCESSORS LAB 1.2
 * by Teerapat Kraisrisirikul
 */

void displaySevenSegment(int num);
void writeSevenSegment(int a, int b, int c, int d, int e, int f, int g);

void setup() {
  // Default Function: Set up
  pinMode(13, OUTPUT); // Output for upper middle segment (A)
  pinMode(12, OUTPUT); // Output for upper right segment (B)
  pinMode(11, OUTPUT); // Output for lower right segment (C)
  pinMode(10, OUTPUT); // Output for lower middle segment (D)
  pinMode(9,  OUTPUT); // Output for lower left segment (E)
  pinMode(8,  OUTPUT); // Output for upper left segment (F)
  pinMode(7,  OUTPUT); // Output for middle segment (G)
  pinMode(3,  OUTPUT); // Output for left digit common
  pinMode(2,  OUTPUT); // Output for right digit common
}

void loop() {
  // Default Function: Loop
  const double freq = 100; // Refresh rate in 1 second, default is 200, must be at least 2, should be at least 75.
  
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      for (int k = 0; k < freq/2; k++) {
        displaySevenSegment(i);
        digitalWrite(3, i == 0);
        digitalWrite(2, HIGH);
        delay(1000/freq);
        displaySevenSegment(j);
        digitalWrite(3, HIGH);
        digitalWrite(2, LOW);
        delay(1000/freq);
      }
    }
  }
}

void displaySevenSegment(int num) {
  // Function: Display a single seven segment digit
  switch (num) {
    case 0:
      writeSevenSegment(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW);
      break;
    case 1:
      writeSevenSegment(LOW, HIGH, HIGH, LOW, LOW, LOW, LOW);
      break;
    case 2:
      writeSevenSegment(HIGH, HIGH, LOW, HIGH, HIGH, LOW, HIGH);
      break;
    case 3:
      writeSevenSegment(HIGH, HIGH, HIGH, HIGH, LOW, LOW, HIGH);
      break;
    case 4:
      writeSevenSegment(LOW, HIGH, HIGH, LOW, LOW, HIGH, HIGH);
      break;
    case 5:
      writeSevenSegment(HIGH, LOW, HIGH, HIGH, LOW, HIGH, HIGH);
      break;
    case 6:
      writeSevenSegment(HIGH, LOW, HIGH, HIGH, HIGH, HIGH, HIGH);
      break;
    case 7:
      writeSevenSegment(HIGH, HIGH, HIGH, LOW, LOW, LOW, LOW);
      break;
    case 8:
      writeSevenSegment(HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH);
      break;
    case 9:
      writeSevenSegment(HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH);
      break;
    default:
      writeSevenSegment(LOW, LOW, LOW, LOW, LOW, LOW, LOW);
      break;
  }
}

void writeSevenSegment(int a, int b, int c, int d, int e, int f, int g) {
  // Function: Write a single seven segment digit
  digitalWrite(13, a);
  digitalWrite(12, b);
  digitalWrite(11, c);
  digitalWrite(10, d);
  digitalWrite(9,  e);
  digitalWrite(8,  f);
  digitalWrite(7,  g);
}

