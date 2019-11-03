#include <Braccio.h>
#include <Servo.h>

Servo base;       //Erstellen der Objekte durch Instanzieren der Klasse Servo
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

String inputString="";    //String to hold incoming data
bool verbunden=false;
bool runFor=false;
bool runBack=false;
bool runRight=false;
bool runLeft=false;
bool runUp=false;
bool runDown=false;


double a1,a2,a3,a4,a5,a6;

void setup() {        // put your setup code here, to run once:
  // initialize Serial:
  Braccio.begin();
  Serial.begin(9600); //9600=Baudrate in Millisekunden
  
}

void loop() {         // put your main code here, to run repeatedly:     
  if(verbunden){
    maxAngle();
    if(runFor&&!runRight&&!runLeft&&!runBack&&!runUp&&!runDown)        
        runForward(); 
    if(!runFor&&runRight&&!runLeft&&!runBack&&!runUp&&!runDown)
        runToTheRight();
    if(!runFor&&!runRight&&runLeft&&!runBack&&!runUp&&!runDown)
        runToTheLeft();
    if(!runFor&&!runRight&&!runLeft&&runBack&&!runUp&&!runDown)
        runBackwards();
    if(!runFor&&!runRight&&!runLeft&&!runBack&&runUp&&!runDown)
        runUpwards();
    if(!runFor&&!runRight&&!runLeft&&!runBack&&!runUp&&runDown)
        runDownwards();
  }  
}

void maxAngle(){           //if-Abfragen, damit nicht mit Zahlen gerechnet wird, die die Motoren nicht verarbeiten können:
    if(a2<15)          
    {
      a2=15;
    }
    if(a2>165)
    {
      a2=165;
    }
    if(a3<0)
    {
      a3=0;
    }
    if(a3>180)
    {
      a3=180;
    }
    if(a4<0)
    {
      a4=0;
    }
    if(a4>180)
    {
      a4=180;
    }
}
void runForward(){
  if(a2>90)
    {
      a2-=1;
      a3+=0.8;
      Braccio.ServoMovement(30,         a1, a2, a3, a4, a5, a6);
    }
    if(a2<=90)
    {
      a2-=0.8;
      a3+=0.8;
      Braccio.ServoMovement(30,         a1, a2, a3, a4, a5, a6);
    } 
}

void runToTheRight(){
    a1+=1;      
    Braccio.ServoMovement(30,         a1, a2, a3, a4, a5,  a6);
}

void runToTheLeft(){
    a1-=1;      
    Braccio.ServoMovement(30,         a1, a2, a3, a4, a5,  a6);
}

void runBackwards(){
  if(a2>90)
    {
      a2+=1;
      a3-=0.8;
      Braccio.ServoMovement(30,         a1, a2, a3, a4, a5, a6);
    }
  if(a2<=90)
    {
      a2+=0.8;
      a3-=0.8;
      Braccio.ServoMovement(30,         a1, a2, a3, a4, a5, a6);
    }
}

void runUpwards(){
  if(a2>90)
    {
      a2-=1;
      a3+=1;
      a4-=0.5;
      Braccio.ServoMovement(30,         a1, a2, a3, a4, a5, a6);
    }
  if(a2<=90)
    {
      a2+=0.5;
      a3+=1;
      a4-=1.5;
      
      Braccio.ServoMovement(30,         a1, a2, a3, a4, a5, a6);
    }
}

void runDownwards(){
  if(a2>90&&a2<165)
    {
      a2+=1;
      a3-=1.5;
      a4+=0.5;
      Braccio.ServoMovement(30,         a1, a2, a3, a4, a5, a6);
    }
  if (a2<=90&&a2>15)
    {
      a2+=1;
      a3-=1.5;
      a4+=0.5;
      Braccio.ServoMovement(30,         a1, a2, a3, a4, a5, a6);
    }
  if(a3<=0||a3>=180)
    {
      if(a4>0)
      {
        a4-=1;
        Braccio.ServoMovement(30,         a1, a2, a3, a4, a5, a6);
      }
    }
  if(a2<=15||a2>=165)
    {
      if(a4>0)
      {
        a4-=1;
        Braccio.ServoMovement(30,         a1, a2, a3, a4, a5, a6);
      }      
    }
}

void serialEvent()
{  
  while(Serial.available())
  {
    char input = Serial.read();
    inputString+=input;
  }
  if(inputString=="verbunden\n")
  {
    a1=90;a2=90;a3=90;a4=90;a5=90;a6=40;
    Braccio.ServoMovement(30,         a1, a2, a3, a4, a5, a6); 
    inputString="";
  }
  if(inputString=="moveRight\n")
  {
    runRight=true;
    inputString="";       
  }
  if(inputString=="moveLeft\n")
  {
    runLeft=true;
    inputString="";    
  }
  if(inputString=="dosenehmen\n")
  {
    Braccio.ServoMovement(30,         90, 90, 90, 90, 90, 20); 
    Braccio.ServoMovement(30,         90, 90, 0, 60, 90, 20);
    Braccio.ServoMovement(30,         90, 40, 0, 140, 90, 20);
    Braccio.ServoMovement(30,         90, 40, 0, 140, 90, 40);
    Braccio.ServoMovement(30,         10, 40, 45, 90, 120, 40);
    inputString="";
  }
  if(inputString=="doseabsetzen\n")
  {
    Braccio.ServoMovement(30,         90, 40, 60, 90, 90, 40);
    Braccio.ServoMovement(30,         90, 40, 0, 140, 90, 40);
    Braccio.ServoMovement(30,         90, 40, 0, 140, 90, 20);
    delay(500);
    Braccio.ServoMovement(30,         90, 90, 90, 90, 90, 20); 
    inputString="";
  }
  if(inputString=="strohhalm\n")
  {
    Braccio.ServoMovement(30,         110, 90, 90, 90, 90, 20); 
    Braccio.ServoMovement(30,         110, 90, 40, 10, 90, 20); 
    Braccio.ServoMovement(30,         110, 125, 0, 30, 90, 10);
    Braccio.ServoMovement(30,         110, 125, 0, 30, 90, 73);
    Braccio.ServoMovement(30,         110, 100, 60, 30, 90, 73);
    Braccio.ServoMovement(30,         110, 90, 90, 30, 90, 73);
    Braccio.ServoMovement(30,         90, 70, 90, 80, 90, 73);
    Braccio.ServoMovement(30,         90, 70, 40, 80, 90, 73);
    inputString="";
  }
  if(inputString=="greifposition\n")
  {
    Braccio.ServoMovement(30,         90,120,10,50,90,10);
    inputString="";
  }
  if(inputString=="STOP\n")
  {
    runFor=false;
    runBack=false;
    runRight=false;
    runLeft=false;
    runUp=false;
    runDown=false;
    inputString="";
  }  
  if(inputString=="nachvorne\n")
  {    
    runFor=true;
    inputString="";
  }
  if(inputString=="nachhinten\n")
  {
    runBack=true;
    inputString="";
  }
  if(inputString=="nachoben\n")
  {
    runUp=true;
    inputString="";   
  }
  if(inputString=="nachunten\n")
  {
    runDown=true;
    inputString="";    
  }
  if(inputString=="setup\n") //SETUP UND TRENNEN SIND GLEICH, 1 MUSS GELÖSCHT WERDEN
  {
    Braccio.begin();
    inputString="";
  }  
  if(inputString=="trennen\n")
  {
    Braccio.begin();
    inputString="";
  }
}
