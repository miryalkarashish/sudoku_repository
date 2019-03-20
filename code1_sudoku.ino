/*  written on:13th march 2019
 *  title:code1 for sudoku solver robot
 *   
 * this code will will move in first 9*9 grid cell by cell and gives information 
 * about the block present in grid
 * 
 */



#include <Stepper.h>

const int stepsPerRevolution_x = 24;//9+9+6 change this to fit the number of steps per revolution
const int stepsPerRevolution_y = 12; //9+3 3 for spare
const int stepsPerRevolution_z = 12; //9+3  ""

// initialize the stepper library on pins
Stepper myStepperx(stepsPerRevolution_x, 8, 9, 10, 11);//specifypin numbers of motor x
Stepper mySteppery(stepsPerRevolution_y, 8, 9, 10, 11);
Stepper myStepperz(stepsPerRevolution_z, 8, 9, 10, 11);

int stepCount = 0;  // number of steps the motor has taken
/* code for color sorting */
int S0=1;
int S1=2,S2=3,S3=4;
int color=0,frequency=0;
int sensorOut=6;

int getinfo(){
  // Setting red filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.print("  ");
  delay(50);

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);

  if(R<45 & R>32 & G<65 & G>55){
    color = 1; // Red
  }
  if(G<55 & G>43 & B<47 &B>35){
    color = 2; // Orange
  }
  if(R<53 & R>40 & G<53 & G>40){
    color = 3; // Green
  }
  if(R<38 & R>24 & G<44 & G>30){
    color = 4; // Yellow
  }
  if(R<56 & R>46 & G<65 & G>55){
    color = 5; // Brown
  }
  if (G<58 & G>45 & B<40 &B>26){
    color = 6; // Blue
  }
  if(R<10 & G<10 & B<10){
    color = 7; //black
  }
  if(R>240 & G<240 & B<240){
    color = 8; //white
  }
  if(R>120 & R<140 & G>120 & G<140 & B>120 & B<140){
    color = 9; //grey
  }
  return color;  
}


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myStepperx.setSpeed(1);
  mySteppery.setSpeed(1);
  myStepperz.setSpeed(1);
  pinMode(S0,OUTPUT);     //set s0,s1,s2,s3 values connected to pins
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  pinMode(sensorOut,INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

int main() {
  int l[81];
  for(int i=0;i<81;i++){
    l[i]=0;
  }
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      l[i*9+j]=getinfo();     //get info about block
      if(i==8 && j==8){
        myStepperx.step(-9);     //stepper.step()   used for moving in steps
        mySteppery.step(-9);
        break;
      }
      if(j==8){
        mySteppery.step(-9);
        myStepperx.step(1);
        break;
      }
      mySteppery.step(1);
      // put your main code here, to run repeatedly: 
    }
  }
  return 0;
}
