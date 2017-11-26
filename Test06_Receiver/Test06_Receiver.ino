/*
* Arduino Wireless Communication Tutorial
*       Example 1 - Receiver Code
*                
* by Dejan Nedelkovski, www.HowToMechatronics.com
* 
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


struct List{
  char idOwn;
  char brightness;
  char idCurrent;
  char groupSize;
  char singleBits;//bit0: ownBeaconMode bit1: ownMoved bit2: rob1Moved bit3: rob2Moved bit4: rob3Moved bit5: rob4Moved
  char visibleRobots[3][4];
  char otherRobots[14][4];
};
struct List listRobots;
char msgBuffer[32];

#define UNCONNECTED 16
#define IDCONFLICT 32
#define MEASURING1 40
#define MEASURING2 41
#define MEASURING3 42
#define STANDING 48
#define WANTTOMOVE 64
#define MOVING 65
#define BEACON1 66
#define BEACON2 67
#define WAITING 68
#define SPREADINGOUT 80

//=========================================================================================
// Setup and main loop
//=========================================================================================

RF24 radio(7, 8); // CNS, CE
const byte address[6] = "00001";
static char flag;
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_MIN);
  radio.setDataRate(RF24_250KBPS);
  flag=read(flag);

// hardcoded stuff, gets removed later on
  listRobots.idOwn=2;
  listRobots.idCurrent=1;
  listRobots.groupSize=2;
  listRobots.brightness=86;

  
  
}

void loop() {
  static long start;
  static char sendMsg=0;
  static char retry=0;
  
  if(sendMsg==1||retry==1){    
    flag=write(flag);
    int Size=createProtocol(msgBuffer, 32);
    radio.write(msgBuffer, Size);
    Serial.println(Size);
    sendMsg=0;
    retry=2;
    start=millis();
  }else{
    flag=read(flag);
    if (radio.available()) {
      char messageBack[35] = "";
      radio.read(&messageBack, sizeof(messageBack));
      readProtocol(messageBack);
      retry=0;
      start=millis();
    }
  }
  if(listRobots.idCurrent==listRobots.idOwn && millis()-start>1000){
    sendMsg=1;
  }
  if(retry==2 && millis()-start>1100){
    retry=1;
  }
}

//=========================================================================================
// Methods write
//=========================================================================================

char write(char flag){
  if(flag!=0){
    radio.stopListening();
    radio.closeReadingPipe(address);
    radio.openWritingPipe(address);
    radio.flush_tx();
    flag=0;
  }
  return flag;
}

char callculateNextID(){
  char idNext;
  if(listRobots.idOwn<listRobots.groupSize){
    idNext=listRobots.idOwn+1;
  }else{
    idNext=1;
  }
  return idNext;
}

int createProtocol(char *msg, char maxSizeMsg){
  static char task = STANDING;
  char endInformation=0;
  *msg=listRobots.idOwn;
  *(msg+1)=listRobots.groupSize;
  *(msg+3)=task;
  int sizeMsg=4;

  
  Serial.println("======================");
  switch(task) {

   case UNCONNECTED : 
      sizeMsg=3;
      Serial.println("Not connected");
      break; 
      
    case IDCONFLICT : 
      sizeMsg=3;
      Serial.println("ID conflict");
      break; 
      
    case MEASURING1 :
      sizeMsg=3;
      Serial.println("Measuring");
      break; 
      
    case STANDING : 
      endInformation=1;
      Serial.println("Standing still");
      break; 
        
    case WANTTOMOVE : 
      sizeMsg=5;
      Serial.println("Beacon Mode");
      break; 
      
    case MOVING : 
      sizeMsg=9;
      Serial.println("Wants to move");
      break; 
      
    case BEACON1 : 
      sizeMsg=3;
      Serial.println("Moving");
      break; 

    case WAITING : 
      sizeMsg=5;
      Serial.println("Stopped Moving but waiting");
      break; 

    case SPREADINGOUT : 
      sizeMsg=3;
      Serial.println("Spreading out");
      

      break; 
   
   default : 
    Serial.println("task invalid");
  }
  if(endInformation==1){
    *(msg+sizeMsg)=listRobots.brightness;
    sizeMsg++;
    
    char idNext=callculateNextID();
    listRobots.idCurrent=idNext;
    *(msg+sizeMsg)=idNext;
  }
  sizeMsg++;
  *(msg+2)=sizeMsg;
  return sizeMsg;
}


//=========================================================================================
// Methods read
//=========================================================================================

char read(char flag){
  if(flag!=1){
    radio.openReadingPipe(0, address);
    radio.startListening();
    flag=1;
  }
  return flag;
}


void readProtocol(char *message){
  char endInformation=0;
  
  Serial.println("======================");
  char id=*message;
  char groupsize=*(message+1);
  char sizeMsg=*(message+2);
  char task=*(message+3);
  Serial.println((int)id);
  Serial.println((int)groupsize);
  Serial.println((int)sizeMsg);
  Serial.println((int)task);
  if(task==STANDING){
    endInformation=4;
  }

  if(endInformation!=0){
    listRobots.otherRobots[1][id]=*(message+endInformation);
    listRobots.idCurrent=*(message+endInformation+1);
    Serial.println((int)listRobots.otherRobots[1][id]);
    Serial.println((int)listRobots.idCurrent);
  }
  
}



