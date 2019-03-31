
#include <Stepper.h>

const int stepPin_x = 1;         //set steppin and dirpin
const int dirPin_x = 2;
const int stepPin_y = 3;
const int dirPin_y = 4;
const int stepPin_z = 5;
const int dirPin_z = 6;
int Electromagnet = 7;

int dir_x=1;             //these values should not be changed
int dir_y=2;

void setup(){
  Serial.begin(9600);
  // Sets the two pins as Outputs
  pinMode(stepPin_x,OUTPUT);
  pinMode(dirPin_x,OUTPUT);
  pinMode(stepPin_y,OUTPUT);
  pinMode(dirPin_y,OUTPUT);
  pinMode(stepPin_z,OUTPUT);
  pinMode(dirPin_z,OUTPUT);
  digitalWrite(dirPin_x,HIGH);
  digitalWrite(dirPin_y,HIGH);
  pinMode(Electromagnet, OUTPUT);
}

int curr_i=0;
int curr_j=0;

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

void movstepper_x(int val){
  int flag=0;
  if(val<0){    //if val is -ve chage dir of stepper
    val-=val;
    flag=1;
    change_dir_x();
  }
  for(int i=0;i<200*1;i++){   //specify no. of rev. in place of 1 in i=200*1;replace 200*1 with 200*rev
                              //rev=val/(lead of lead screw in x dir)
    digitalWrite(stepPin_x,HIGH);
    delayMicroseconds(500);
  }
  if(flag==1){
    change_dir_x();
  }
}

void movstepper_y(int val){
  int flag=0;
  if(val<0){    //if val is -ve chage dir of stepper
    val-=val;
    flag=1;
    change_dir_y();
  }
  for(int i=0;i<200*1;i++){   //specify no. of rev. in place of 1 in i=200*1 in y direction
    digitalWrite(stepPin_x,HIGH);
    delayMicroseconds(500);
  }
  if(flag==1){
    change_dir_x();
  }
}

void upper_z(){
  digitalWrite(dirPin_z,LOW);    //change high or low according to movement
  for(int i=0;i<200*5;i++){      //this will make 5 rev. to go up
    delayMicroseconds(500);
    digitalWrite(stepPin_x,HIGH);
  }
}

void lower_z(){
  digitalWrite(dirPin_z,HIGH);    //change high or low according to movement
  for(int i=0;i<200*5;i++){
    delayMicroseconds(500);
    digitalWrite(stepPin_x,HIGH);     //this will make 5 rev. to go up
  }
}

void movto_loc(int i,int j){
  movstepper_x(i-curr_i);
  curr_i=i;
  movstepper_y(j-curr_j);
  curr_j=j;
}

void magnet_on(){
  digitalWrite(Electromagnet, HIGH);
}

void magnet_off(){
  digitalWrite(Electromagnet, LOW);
}

int main(){
  setup();
  int l[81];   //define some random l and note that that if it is moving fine.
  for(int i=0;i<81;i++){   //this for loop is only for testing and should be removed.
    l[i]=i;
  }
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      if(l[i*9+j]==0)  continue;
      int val=l[i*9+j];
      movto_loc(i,j);     //add space between two grids for x and y axis resp.
      lower_z();
      magnet_on();
      upper_z();
      int f_i=(val+1)/9;
      int f_j=(val+1)%9;
      movto_loc(f_i,f_j);
      lower_z();
      magnet_off();
      upper_z();
    }
  }
}
