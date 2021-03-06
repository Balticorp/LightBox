/* LightBox Audio Control
 * by Kamran Hetke & Rylan McFarland
 ********************************************
 * Based on code by Amanda Ghassaei
 * http://www.instructables.com/id/Arduino-Frequency-Detection/
 */

//clipping indicator variables
boolean clipping = 0;


//Set frequencies
int f1 = 250;
int f2 = 1000;
int f3 = 1900;
int f4 = 3100;
int f5 = 4850;
int f6 = 10000;
int f7 = 15000;

//data storage variables
byte newData = 0;
byte prevData = 0;
unsigned int time = 0;//keeps time and sends vales to store in timer[] occasionally
int timer[10];//sstorage for timing of events
int slope[10];//storage for slope of events
unsigned int totalTimer;//used to calculate period
unsigned int period;//storage for period of wave
byte index = 0;//current storage index
float frequency;//storage for frequency calculations
int maxSlope = 0;//used to calculate max slope as trigger point
int newSlope;//storage for incoming slope data

//variables for decided whether you have a match
byte noMatch = 0;//counts how many non-matches you've received to reset variables if it's been too long
byte slopeTol = 3;//slope tolerance- adjust this if you need
int timerTol = 10;//timer tolerance- adjust this if you need

//variables for amp detection
unsigned int ampTimer = 0;
byte maxAmp = 0;
byte checkMaxAmp;
byte ampThreshold = 100;//raise if you have a very noisy signal

void setup(){
  
  Serial.begin(9600);
  
  pinMode(13,OUTPUT);//led indicator pin
  pinMode(12,OUTPUT);//output pin
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
  
  cli();//diable interrupts
  
  //set up continuous sampling of analog pin 0 at 38.5kHz
 
  //clear ADCSRA and ADCSRB registers
  ADCSRA = 0;
  ADCSRB = 0;
  
  ADMUX |= (1 << REFS0); //set reference voltage
  ADMUX |= (1 << ADLAR); //left align the ADC value- so we can read highest 8 bits from ADCH register only
  
  ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler- 16mHz/32=500kHz
  ADCSRA |= (1 << ADATE); //enabble auto trigger
  ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN); //enable ADC
  ADCSRA |= (1 << ADSC); //start ADC measurements
  
  sei();//enable interrupts
}

ISR(ADC_vect) {//when new ADC value ready
  
  prevData = newData;//store previous value
  newData = ADCH;//get value from A0
  if (prevData < 127 && newData >=127){//if increasing and crossing midpoint
    newSlope = newData - prevData;//calculate slope
    if (abs(newSlope-maxSlope)<slopeTol){//if slopes are ==
      //record new data and reset time
      slope[index] = newSlope;
      timer[index] = time;
      time = 0;
      if (index == 0){//new max slope just reset
        noMatch = 0;
        index++;//increment index
      }
      else if (abs(timer[0]-timer[index])<timerTol && abs(slope[0]-newSlope)<slopeTol){//if timer duration and slopes match
        //sum timer values
        totalTimer = 0;
        for (byte i=0;i<index;i++){
          totalTimer+=timer[i];
        }
        period = totalTimer;//set period
        //reset new zero index values to compare with
        timer[0] = timer[index];
        slope[0] = slope[index];
        index = 1;//set index to 1
        noMatch = 0;
      }
      else{//crossing midpoint but not match
        index++;//increment index
        if (index > 9){
          reset();
        }
      }
    }
    else if (newSlope>maxSlope){//if new slope is much larger than max slope
      maxSlope = newSlope;
      time = 0;//reset clock
      noMatch = 0;
      index = 0;//reset index
    }
    else{//slope not steep enough
      noMatch++;//increment no match counter
      if (noMatch>9){
        reset();
      }
    }
  }
  
  if (frequency < f1){
    digitalWrite(13,HIGH); 
    clipping = 1;//currently clipping
  }
  if (f1 <= frequency && frequency < f2){
    digitalWrite(12,HIGH);
    clipping = 1;//currently clipping
  }
  if (f2 <= frequency && frequency < f3){
    digitalWrite(11,HIGH);
    clipping = 1;//currently clipping
  }
  if (f3 <= frequency && frequency < f4){
    digitalWrite(10,HIGH);
    clipping = 1;//currently clipping
  }
  if (f4 <= frequency && frequency < f5){
    digitalWrite(9,HIGH);
    clipping = 1;//currently clipping
  }
  if (f5 <= frequency && frequency < f6){
    digitalWrite(8,HIGH);
    clipping = 1;//currently clipping
  }
  if (f6 <= frequency && frequency < f7){
    digitalWrite(7,HIGH);
    clipping = 1;//currently clipping
  }
  if (f7 <= frequency){
    digitalWrite(6,HIGH); 
    clipping = 1;//currently clipping
  }
  
  /*
  if (frequency < 32){
    digitalWrite(13,HIGH); 
    clipping = 1;//currently clipping
  }
  if (32 <= frequency && frequency < 65){
    digitalWrite(12,HIGH);
    clipping = 1;//currently clipping
  }
  if (65 <= frequency && frequency < 130){
    digitalWrite(11,HIGH);
    clipping = 1;//currently clipping
  }
  if (130 <= frequency && frequency < 261){
    digitalWrite(10,HIGH);
    clipping = 1;//currently clipping
  }
  if (261 <= frequency && frequency < 523){
    digitalWrite(9,HIGH);
    clipping = 1;//currently clipping
  }
  if (523 <= frequency && frequency < 1046){
    digitalWrite(8,HIGH);
    clipping = 1;//currently clipping
  }
  if (1046 <= frequency && frequency < 2093){
    digitalWrite(7,HIGH);
    clipping = 1;//currently clipping
  }
  if (2093 <= frequency){
    digitalWrite(6,HIGH); 
    clipping = 1;//currently clipping
  }
  
  /* Setting a clipping LED with Binary & Ports
  if (newData == 0 || newData == 1023){//if clipping
    PORTB |= B00100000;//set pin 13 high- turn on clipping indicator led
    clipping = 1;//currently clipping
  }
  */
  
  time++;//increment timer at rate of 38.5kHz
  
  ampTimer++;//increment amplitude timer
  if (abs(127-ADCH)>maxAmp){
    maxAmp = abs(127-ADCH);
  }
  if (ampTimer==1000){
    ampTimer = 0;
    checkMaxAmp = maxAmp;
    maxAmp = 0;
  }
  
}

void reset(){//clea out some variables
  index = 0;//reset index
  noMatch = 0;//reset match couner
  maxSlope = 0;//reset slope
}


void checkClipping(){//manage clipping indicator LED
  if (clipping){//if currently clipping
    digitalWrite(13,LOW);
    digitalWrite(12,LOW);
    digitalWrite(11,LOW);
    digitalWrite(10,LOW);
    digitalWrite(9,LOW);
    digitalWrite(8,LOW);
    digitalWrite(7,LOW);
    digitalWrite(6,LOW);
    //Binary & Port method of turning pin13 off:
    //PORTB &= B11011111;
    clipping = 0;
  }
}


void loop(){
  
  checkClipping();
  
  if (checkMaxAmp>ampThreshold){
    frequency = 38462/float(period);//calculate frequency timer rate/period
  
    //print results
    Serial.print(frequency);
    Serial.println(" hz");
  }
  
  delay(1);//delete this if you want
  
  //do other stuff here
}

