
#include <MFRC522.h> //MFRC522 library for communicating with the RFID reader 
#include <SPI.h> //SPI library for using the SPI protocol 

#define SSPIN 10 //SS pin for SPI bus 
#define RESETPIN 9 //RST pin for SPI bus 
#define LEDGREEN 8 //Green LED pin
#define LEDRED 7 //Red LED pin

byte valid_UID[4] = {0xA6,0x73,0x53,0x83}; //valid UID in HEX

MFRC522 RFIDreader(SSPIN,RESETPIN);

unsigned long old_time = 0;
boolean card_removed = true;

#define WAIT_TIME 1000 //1s wait time until a new UID is read 

void setup() {
  SPI.begin(); //Initialize SPI bus
  Serial.begin(9600); //Initialize serial bus
  RFIDreader.PCD_Init(); //Initialize RFID reader
  pinMode(LEDGREEN,OUTPUT);
  pinMode(LEDRED,OUTPUT);
}

void loop() {
  if (!RFIDreader.PICC_IsNewCardPresent()) { //If no card is in vicinity then return and
                                             //restart void loop()
                                             
     if((millis() - old_time)>WAIT_TIME){ //Card has been removed
        
        if (!card_removed){ //Check if the current card has been labeled "removed"
          Serial.println("Card removed");
          //Switch off both LEDs
          digitalWrite(LEDGREEN,LOW);
          digitalWrite(LEDRED,LOW);
          card_removed = true;}
      }
      
    return;
    } 
    
  if (!RFIDreader.PICC_ReadCardSerial()) { //If reading the card is not yet finished
                                           //then return and restart void loop()
    return;
    }

  //This following code is executed when a card is in vicinity and has been read.
  
    //Read and check UID
    if(compareByteArray(valid_UID,RFIDreader.uid.uidByte)){
          
      //If UID is valid     
        if (card_removed){ //If card has been removed before
          Serial.println("Access");
          //Light green LED
          digitalWrite(LEDGREEN,HIGH);
          card_removed = false; //set card_removed to false so that the code above
                                //is repeated only if the card has been removed before
          }
    
    }
    
    else{ //If UID is not valid
      if (card_removed){ //If card has been removed before
        Serial.println("Access denied");
        digitalWrite(LEDRED,HIGH);
        card_removed = false;
        }
    }

    old_time = millis(); //store current time in old_time
}

//Function used to compare the read UID with the valid UID stored above
boolean compareByteArray (byte byteArray1[], byte byteArray2[]){

  for (int i = 0; i < 4; i++){ //Every UID has 4 blocks
    if (byteArray1[i]!=byteArray2[i]){return false;} //If the current block does not match
                                                     //the corresponding block from the valid UID
                                                     //stop and return false 
    }

  return true; //This statement is only reached when all UID blocks are valid
  }
