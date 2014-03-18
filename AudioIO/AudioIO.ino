/* LightBox Audio Control
 * by Kamran Hetke & Rylan McFarland
 */

// Data storage variables
byte newData = 0;
byte prevData = 0;

// Frequency variables
unsigned int timer = 0; // Counts the period of wave
unsigned int period;
int frequency;

// Strand Designators
int strand1 = 13;
int strand2 = 12;
int strand3 = 11;
int strand4 = 10;
int strand5 = 9;
int strand6 = 8;
int strand7 = 7;
int strand8 = 6;

// Hertz Designators
int c1 = 32;
int c2 = 65;
int c3 = 130;
int c4 = 261;
int c5 = 523;
int c6 = 1046;
int c7 = 2093;

void setup() {
  // Serial Begin:
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(strand1, OUTPUT);
  pinMode(strand2, OUTPUT);
  pinMode(strand3, OUTPUT);
  pinMode(strand4, OUTPUT);
  pinMode(strand5, OUTPUT);
  pinMode(strand6, OUTPUT);
  pinMode(strand7, OUTPUT);
  pinMode(strand8, OUTPUT);

  cli(); // Disable interrupts
  
  // Setting up continuous sampling of analog pin 0
  
  // Clear ADCSRA and ADCSRB registers
  ADCSRA = 0;
  ADCSRB = 0;
  
  ADMUX |= (1 << REFS0); // Set reference voltage
  ADMUX |= (1 << ADLAR); // Align the ADC value to the left so we can read highest 8 bits from ADCH register only
  
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0); // Set the ADC clock with 32 prescaler- 16mHz/32=500kHz
  ADCSRA |= (1 << ADATE); // Enable auto trigger
  ADCSRA |= (1 << ADIE); // Enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN); // Enable ADC
  ADCSRA |= (1 << ADSC); // Start ADC measurements
  
  sei(); // Enable interrupts
}

ISR(ADC_vect) {

  prevData = newData; // Store previous value
  newData = ADCH; // Get value from Analog input (A0)
  if (prevData < 127 && newData >=127){
    period = timer; // Get the period
    timer = 0; // Reset the timer
  }
  
  
  // Sets specific pins to "on" when they fall between a certain hertz range
  if (frequency <= c1){
    digitalWrite(strand1, HIGH); // Set pin 13 high
    clipping = 1; // Currently clipping
  }
  if (c1 < frequency <= c2){
    digitalWrite(strand2, HIGH); // Set pin 12 high
    clipping = 1; // Currently clipping
  }
  if (c2 < frequency <= c3){
    digitalWrite(strand3, HIGH); // Set pin 11 high
    clipping = 1; // Currently clipping
  }
  if (c3 < frequency <= c4){
    digitalWrite(strand4, HIGH); // Set pin 10 high
    clipping = 1; // Currently clipping
  }
  if (c4 < frequency <= c5){
    digitalWrite(strand5, HIGH); // Set pin 9 high
    clipping = 1; // Currently clipping
  }
  if (c5 < frequency <= c6){
    digitalWrite(strand6, HIGH); // Set pin 8 high
    clipping = 1; // Currently clipping
  }
  if (c6 < frequency <= c7){
    digitalWrite(strand7, HIGH); // Set pin 7 high
    clipping = 1; // Currently clipping
  }
  if (c7 < frequency){
    digitalWrite(strand8, HIGH); // Set pin 6 high
    clipping = 1; // Currently clipping
  }

  timer++; // Increment timer at rate of 38.5kHz
}

void loop(){
  // If currently clipping
  if (clipping){
    digitalWrite(strand1, LOW); // Turn off the strand
    digitalWrite(strand2, LOW); // Turn off the strand
    digitalWrite(strand3, LOW); // Turn off the strand
    digitalWrite(strand4, LOW); // Turn off the strand
    digitalWrite(strand5, LOW); // Turn off the strand
    digitalWrite(strand6, LOW); // Turn off the strand
    digitalWrite(strand7, LOW); // Turn off the strand
    digitalWrite(strand8, LOW); // Turn off the strand
    clipping = 0;
  }

  frequency = 38462/period;// Timer rate divided by the period
  // Print results
  Serial.print(frequency);
  Serial.println(" hz");
  
  delay(100);
}

