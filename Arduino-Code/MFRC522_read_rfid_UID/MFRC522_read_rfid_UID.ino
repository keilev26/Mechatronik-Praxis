
#include <MFRC522.h> //MFRC522 library for communicating with the RFID reader 
#include <SPI.h> //SPI library for using the SPI protocol 

#define SSPIN 10 //SS pin for SPI bus 
#define RESETPIN 9 //RST pin for SPI bus 

byte read_UID[4] = {0,0,0,0}; //Variable to store the retrieved UID 

MFRC522 RFIDreader(SSPIN,RESETPIN);

unsigned long old_time = 0;

#define WAIT_TIME 1000 //1s wait time until a new UID is read 

void setup() {
  SPI.begin(); //Initialize SPI bus
  Serial.begin(9600); //Initialize serial bus
  RFIDreader.PCD_Init(); //Initialize RFID reader
  old_time = millis(); //Save current system time
}

void loop() {
  if (!RFIDreader.PICC_IsNewCardPresent()) { //If no card is in vicinity then return and
                                             //restart void loop()
    return;
  } 
    
  if (!RFIDreader.PICC_ReadCardSerial()) { //If reading the card is not yet finished
                                           //then return and restart void loop()
    return;
  }

  //This following code is executed when a card is in vicinity and has been read. 
  
  //Only execute this code when the card has been removed for the duration of time
  //defined in WAIT_TIME 
  if((millis() - old_time)>WAIT_TIME){

      //Read UID
      for (int i = 0; i < 4; i++){
        read_UID[i] = RFIDreader.uid.uidByte[i];
      }
      Serial.print("Retrieved UID: ");
      for (int i = 0; i < 4; i++){
        Serial.print(read_UID[i],HEX); //Print the separat UID blocks as HEX 
        Serial.print(" "); //Put spaces in between the UID blocks to improve readability. 
      }
      Serial.println();
  }
    
  old_time = millis(); //Save current time 
}
