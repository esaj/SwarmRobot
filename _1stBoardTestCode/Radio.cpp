#include "Radio.h"

struct List listRobots;
char msgBuffer[32];
RF24 radio(7, 8); // CNS, CE
const byte address[6] = "00001";
static char flag;

void initRadio() {
  radio.begin();
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.enableAckPayload();
  flag=read(flag);

// hardcoded stuff, gets removed later on
  listRobots.idOwn=2;
  listRobots.idCurrent=1;
  listRobots.groupSize=2;
  listRobots.brightness=86;
}

void checkRadio(){
  static char sendMsg=0;

  if(listRobots.idCurrent==listRobots.idOwn){
    sendMsg=1;
  }else{
    if (radio.available()) {
      char messageBack[35] = "";
      radio.read(&messageBack, sizeof(messageBack));
      readProtocol(messageBack);
      sendMsg=2;
    }else{
      if(sendMsg!=2){
        sendMsg=1;
      }
    }
  }
    Serial.println((int)sendMsg);
  if(sendMsg==1){    
    flag=write(flag);
    int Size=createProtocol(msgBuffer, 32);
    radio.write(msgBuffer, Size);
    Serial.println(Size);
    sendMsg=0;
    flag=read(flag);
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

