//might get some problem with color check carefully with all specified colors for safe side.

#include <Stepper.h>

const int stepPin_x = 1;         //set steppin and dirpin
const int dirPin_x = 2;
const int stepPin_y = 3;
const int dirPin_y = 4;
int dir_x=1;             //be careful these values should not be changed
int dir_y=1;

#define S0 8      //pins color sensor to arduino
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 9
int frequency = 0;   //dont change this value

void setup(){
  // Sets the two pins as Outputs
  pinMode(stepPin_x,OUTPUT);
  pinMode(dirPin_x,OUTPUT);
  pinMode(stepPin_y,OUTPUT);
  pinMode(dirPin_y,OUTPUT);
  digitalWrite(dirPin_x,HIGH);
  digitalWrite(dirPin_y,HIGH);
  pinMode(S0,OUTPUT);           //set s0,s1,s2,s3 values connected to pins
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  pinMode(sensorOut,INPUT);
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  //Enables the motor to move in a particular direction
  Serial.begin(9600);
}


void change_dir_x(){
  if(dir_x==1){
    digitalWrite(dirPin_x,LOW);
    dir_x=0;
    return;
  }
  digitalWrite(dirPin_x,HIGH);
  dir_x=1;
  return;
}

void change_dir_y(){
  if(dir_y==1){
    digitalWrite(dirPin_y,LOW);
    dir_y=0;
    return;
  }
  digitalWrite(dirPin_y,HIGH);
  dir_y=1;
  return;
}



void movstepper_y(int val){
  int flag=0;
  if(val<0){    //if val is -ve chage dir of stepper
    val-=val;
    flag=1;
    change_dir_y();
  }
  for(int i=0;i<200*(20/8);i++){   //specify no. of rev. in place of 1 in i=200*1 in y direction
    digitalWrite(stepPin_x,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin_x,LOW);
    delayMicroseconds(1000);
  }
  if(flag==1){
    change_dir_y();
  }
}


void movstepper_x(int val){
  int flag=0;
  if(val<0){    //if val is -ve chage dir of stepper
    val-=val;
    flag=1;
    change_dir_x();
  }
  for(int i=0;i<200*(20/8);i++){   //specify no. of rev. in place of 1 in i=200*1 in x direction
                              //rev=(dist between 2 adjecent blocks)/(lead of lead screw in x dir)
    digitalWrite(stepPin_x,HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin_x,LOW);
    delayMicroseconds(1000);
  }
  if(flag==1){
    change_dir_x();
  }
}


int getinfo(){
  /* code for color sorting */
  // Setting red filtered photodiodes to be read
  int color=0;
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

int main(){
  void setup();    //check with values before testing in setup
  int l[81];
  for(int i=0;i<81;i++){
    l[i]=0;
  }
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      int data=getinfo();
      l[i*9+j]=data;
      if(i==8 and j==8){
        movstepper_x(-9);
        movstepper_y(-9);
        continue;
      }
      if(j==8){
        movstepper_y(-9);
        movstepper_x(1);
        continue;
      }
      movstepper_y(1);
    }
  }
  for(int i=0;i<81;i++){
    Serial.println(l[i]);
  }
  return 0;
}
