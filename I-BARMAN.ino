
#define MACHINE_ID 1000000004
#define USER_ID    32767
int hazne = 545;
const char *server = "ibarman.azure-mobile.net";            // Azure Mobile Service address             
const char *table_name = "sales";                           // Azure Mobile Service  table name
const char *ams_key = "JTSMKtBbxvWMTXToCwfxUPicuURpVu38";   // Azure Mobile Service Application Key (You can find this key in the 'Manage Keys' menu on the dashboard)
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
char Cocktailname[30];                                      // for saving coctail name to EEPROM cocktail name should be 30 char you have indepedent char in send_request Azure 
const int inputLength = 30;                                 //for getting cocktail name
const int typeLength = 30;
char inputString[inputLength];
char requestTypeString[inputLength];
String TypeString = requestTypeString;
String TypeString2;
float pumparray[10];                                        // motor array
float mlarray[10];                                          // ml array
float mlwaterarray[4];                                      // water ml array
float syruprate[4];                                         // water ml array
float motordelay[10];                                       // calibrating values
float Max;                                                  // for declaring while loop motor works time
/////////////////////////////////////////////////-SHIFTREGISTERVARIABLES-/////////////////////////////////////////////////////////
int clockPin = A0;
int latchPin = A1;
int dataPin = A2;
byte switchVar1 = 72;  //01001000
byte switchVar2 = 159; //10011111
//byte switchVar3 = 231; //11100111
//////////////////////////////////////////////////////////////////////////////////////
int ButtonNo=0;
int eepromadress = 0;
long Cocktail=0;
int CocktailNo=0;                                           // sending azure which coctail sold
///////////////////////////////////////////////////////////////////////                      
int Type= 0;                                                // type of button
float  delay1 = 0;                                          // Azure Data Value
float  delay3 = 0;                                          // Azure Data Value
String currentLine = "";                                    // string for incoming serial data
String currRates = "";
boolean readingRates = false;                               // is reading?
String query;
String query2;
String buffer2;
long Time1;                                                 //motors working time
/////////////////////////////////////////////////////-SENSORS-///////////////////////////////////////////////
long Time2;                                                 //if reservoir empty detected saves the time
boolean Time2checker;                                       //if reservoir empty it becomes true
boolean pumpwork;                                           //controls motors working
boolean reservoirchecker;                                   // for displaying empty reservoirs

boolean sensorcheckerup[16];                                 // sensor renew for displaying
boolean sensorcheckerdown[16];                               // sensor renew for displaying
int sensorvalueup[16];                                       //define sensor UP value
int sensorvaluesaveup[16];                                   //saves sensor's last value have to be "1" for startup
int sensorvaluedown[16];                                       //define sensor DOWN value
int sensorvaluesavedown[16];                                   //saves sensor's last value have to be "1" for startup

////////////////////////////////////////////////////-BUTTONS-/////////////////////////////////////////////////
int laststate[10];                                          // previous state of the button
///////////////////////////////////////////////////-DOWNLOADBUTTON-///////////////////////////////////////////////////////////////// 
# define buttonDownload3 3                                  // DOWNLOAD
int buttonPushCounterDownload = 0;                          // counter for the number of button presses
int buttonStateDownload = 0;                                // current state of the button
int lastButtonStateDownload = 0;                            // previous state of the button

///////////////////////////////////////////////////-UPLOADBUTTON-///////////////////////////////////////////////////////////////// 
# define buttonUpload2 2                                    // UPLOAD
int buttonPushCounterUpload = 0;                            // counter for the number of button presses
int buttonStateUpload = 0;                                  // current state of the button
int lastButtonStateUpload = 0;                              // previous state of the button

///////////////////////////////////////////////////-MODEBUTTON-///////////////////////////////////////////////////////////////// 
# define buttonMode8 8                                      // UPLOAD
int buttonPushCounterMode = 0;                              // counter for the number of button presses
int buttonStateMode = 0;                                    // current state of the button
int lastButtonStateMode = 0;                                // previous state of the button
boolean mode = false;                                       // changes the coctail buttons to calibration buttons
int calibratecounter = 0;                                   // if it == 1 vacates sensor's top value, ==2 vacates to the bottom 
float calibratetime;                                        //difference
float calibratetime1;                                       //starting point of vacate
float calibratetime2;                                       //end point of vacate
boolean displaylocker=true;                                 //locks calibration mode on display mode

/////////////////////////////////////////////////-AUTOMATICCONNECTION-////////////////////////////////////////////////////////////////
//const long requestInterval = 20000;
const long requestInterval = 600000;                        // ms delay between requests (15 min=900000) (10 min=600000)
boolean requested;                                          // whether you've made a request since connecting
unsigned long lastAttemptTime = 0;                          // last time you connected to the server, in ms

////////////////////////////////////////////////////-AUTOCALIBRATION-////////////////////////////////////
float timer[9];                                            //for putting up-sensor falling edge time
float timer2[9];                                           //for putting down-sensor falling edge time
int array[9];                                              //for putting which up-sensors going to check
int array2[9];                                             //for putting which down-sensors going to check
float array3[9];                                           //for putting all time form eeprom
float voidarray[9];
boolean upperend[9];                                       //deactivates checking sensor
boolean mediumend[9];                                      //deactivates checking sensor
boolean lowerend[9];                                       //deactivates checking sensor
boolean upper[9];                                          //activates when the sensor fall from up                      
boolean medium[9];                                         //activates when the sensor at medium
boolean lower[9];                                          //activates when the sensor fall from dowm
boolean upperendchecker[9];                                //activates when the sensor fall from up

//////////////////////////////////////////////////////////-EEPROM-////////////////////////////////////////////////////////
#include <EEPROM.h>
long counter;
long cocktailcounter;
long lastsaved;
long difference;

///////////////////////////////////////////////////////-RTC1302-/////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <Time.h>
#include <DS1302RTC.h>
DS1302RTC RTC(5, 6, 7);                                    // 5 Chip Enable(RST) 6 Input/Output(DATA) 7 Serial Clock (CLK)    
String stringtime;
String stringtime2;

/////////////////////////////////////////////////////////-SDCARDVARIABLES-/////////////////////////////////////////////////////////
#include <SD.h>
#include <SPI.h>
const int chipSelect = 4;
File dataFile;
/////////////////////////////////////////////////////////-INTERNET&LCDVARIABLES-/////////////////////////////////////////////////////////

#include <Ethernet.h>
#include <TextFinder.h>
#include <LiquidCrystal.h>
 /*
 * LCD RS pin to digital pin A10
 * LCD Enable pin to digital pin A11
 * LCD D4 pin to digital pin A12
 * LCD D5 pin to digital pin A13
 * LCD D6 pin to digital pin A14
 * LCD D7 pin to digital pin A15
  */
LiquidCrystal lcd(A10, A11, A12, A13, A14, A15);
byte mac[6] = { 0x74, 0x69, 0x69, 0x2D, 0x30, 0x31 };       // Ethernet shield MAC address
char macstr[18];                                            // MAC WRITER
//byte ip[] = { 192, 168, 1, 74 };                          // FOR IP REZERVATION NOT WORK

EthernetClient client;
TextFinder  finder(client); 
char buffer[64];
char inChar;
String inChar2;
////////////////////////////////////////////////////////////-UPLOAD VARIABLES-/////////////////////////////////////////////////////////////
boolean uploadchecker=true;
String date;
String Timeupload;
int buttonno;
int sales;
char Timechar[8];
char datechar[10];
////////////////////////////////////////////////////////////-RESET-/////////////////////////////////////////////////////////////
void(* resetFunc) (void) = 0; //declare reset function @ address 0

////////////////////////////////////////////////////////////-UPLOAD-/////////////////////////////////////////////////////////////
void upload()
{ 
    Serial.print("Cocktailcounter=");                                      //this part will not exist at main version. just for trial version
    Serial.println(EEPROM.get(1304,cocktailcounter));
    Serial.print("lastsaved=");
    Serial.println(EEPROM.get(1308,lastsaved));
    Serial.print("Counter=");
    Serial.println(EEPROM.get(1312,counter));
  if(counter!=lastsaved)
  {       
      if(uploadchecker)
      {                          
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Upload Mode ON");     
      stringtime="";
      stringtime2="";
      stringtime2= String(hour()) + ":" + String(minute()) + ":" + String(second());
      stringtime=String(day()) + "-" + String(month()) + "-" +  String(year());
      Serial.println("\nUpload Mode on");
     // difference=((counter-lastsaved)+1)*9;
     // long x[difference];
      difference=counter-lastsaved;
      long x[9];
      boolean saver=false;
       Serial.print("Difference=");
       Serial.println(difference);
       lcd.setCursor(0,1);
       lcd.print("                   ");
       lcd.setCursor(0,1);
       lcd.print("Remaining ");
       lcd.setCursor(10,1);
       lcd.print(difference);
       int i=0;     
       Serial.print("Lastsaved=");
       Serial.println(lastsaved);
       Serial.print("Counter=");
       Serial.println(counter);
       dataFile = SD.open("SALES.csv");
       
  if (dataFile)                   // if the file opened okay, write to it:
  {   
    while (dataFile.available()) 
  { int a = 0;
  if (i==9)
  {
     dataFile.close();
  }
  else
  {
    a=dataFile.parseInt();
    Serial.println(a);
    if (a==lastsaved)
    {
      saver=true;
      }
      if(saver)
      {
    x[i] = a;
    Serial.print("Saved ");
    Serial.println(x[i]);
    i++;
      }
  }
  }    
  saver=false;
                    // close the file:
    Serial.println("*****************************UPLOADED TO ARRAY****************************");
  }
  else 
  {
    // if the file didn't open, print an error:
    lcd.clear();
    lcd.print("error opening loop");
    lcd.setCursor(0,1);
    lcd.print("5 second");
    Serial.print("error opening loop 5sn");
    delay(5000);
    EEPROM.write(4000,1);
    resetFunc();  //call reset
  }
  int a=0;
//  for (int i=1; i <= (difference/9); i++)

  date="";
  Timeupload="";
  Serial.print("COUNTER=");
  Serial.println(x[a]);
  a++;
  Serial.print("NO=");
  Serial.println(x[a]);
  sales=x[a];
  a++;
  Serial.print("BUTTON_NO=");
  Serial.println(x[a]);
  buttonno=x[a];
  switch (buttonno)
  {
    case 1:
    eepromadress=(buttonno-1)*126;
    Serial.print("EEPROMAlkolOnename=");
    Serial.println(EEPROM.get(eepromadress , Cocktailname));
    
    break;

    case 2:
    eepromadress=(buttonno-1)*126;
    Serial.print("EEPROMAlkolOnename=");
    Serial.println(EEPROM.get(eepromadress , Cocktailname));
    break;
    
    case 3:
    eepromadress=(buttonno-1)*126;
    Serial.print("EEPROMAlkolOnename=");
    Serial.println(EEPROM.get(eepromadress , Cocktailname));
    break;
    
    case 4:
    eepromadress=(buttonno-1)*126;
    Serial.print("EEPROMAlkolOnename=");
    Serial.println(EEPROM.get(eepromadress , Cocktailname));
    break;

    case 5:
    eepromadress=(buttonno-1)*126;
    Serial.print("EEPROMAlkolOnename=");
    Serial.println(EEPROM.get(eepromadress , Cocktailname));
    break;
    
    case 6:
    eepromadress=(buttonno-1)*126;
    Serial.print("EEPROMAlkolOnename=");
    Serial.println(EEPROM.get(eepromadress , Cocktailname));
    break;

    case 7:
    eepromadress=(buttonno-1)*126;
    Serial.print("EEPROMAlkolOnename=");
    Serial.println(EEPROM.get(eepromadress , Cocktailname));
    break;

    case 8:
    eepromadress=(buttonno-1)*126;
    Serial.print("EEPROMAlkolOnename=");
    Serial.println(EEPROM.get(eepromadress , Cocktailname));
    break;
    
    case 9:
    eepromadress=(buttonno-1)*126;
    Serial.print("EEPROMAlkolOnename=");
    Serial.println(EEPROM.get(eepromadress , Cocktailname));
    break;
    
    case 10:
    eepromadress=(buttonno-1)*126;
    Serial.print("EEPROMAlkolOnename=");
    Serial.println(EEPROM.get(eepromadress , Cocktailname));
    break;
  } 
  a++;
  Timeupload+=x[a];
  Timeupload+=":";
  //Serial.println(x[a]);
  a++;
  Timeupload+=x[a];
  Timeupload+=":";
  //Serial.println(x[a]);
  a++;
  Timeupload+=x[a];
  Timeupload.toCharArray(Timechar, 8);
  Serial.println(Timeupload);
  //Serial.println(x[a]);
  a++;
  date+=x[a];
  date+="-";
  //Serial.println(x[a]);
  a++;
  date+=x[a];
  date+="-";
  //Serial.println(x[a]);
  a++;
  date+=x[a];
  Serial.println(date);
  date.toCharArray(datechar, 10);
  //Serial.println(x[a]);
  a++;
  Serial.println("----------");

  send_request(sales, buttonno, Cocktailname,Timechar,datechar);
  wait_response();
  read_response();
  end_request();
  
  lastsaved++;          
  EEPROM.put(1308,lastsaved);
  if(lastsaved<counter)
  {
    Serial.print("Going to save ");
    Serial.println(lastsaved);
    upload();
  }
  else
  {
  lcd.setCursor(0,1);
  lcd.print("                    ");
  lcd.setCursor(4,1);
  lcd.print("Successfull");
  Time2=millis();                    // turns default screen after 5 second
  Time2checker= true;                // turns default screen after 5 second
   dataFile.close();
  }
  }
  else
  {
  Serial.println("internet problem");
  lcd.clear();
  lcd.print("Not Connected");
  Time2=millis();                    // turns default screen after 5 second
  Time2checker= true;                // turns default screen after 5 second
  }
}
else
{
  
    Serial.println("Not recorded any sale until the last update");
    lcd.clear();
    lcd.print("Not recorded");
    lcd.setCursor(0,1);
    lcd.print("any sale until");
    lcd.setCursor(0,2);
    lcd.print("the last update");
    Time2=millis();                    // turns default screen after 5 second
    Time2checker= true;                // turns default screen after 5 second
    return;
    //return loop();
}

}

////////////////////////////////////////////////////////////-SEND_SD_REQUEST-/////////////////////////////////////////////////////////////

void send_sd_request()
{  
  Serial.println("send_sd_request");  
  Serial.print("Cocktailcounter=");
  Serial.println(EEPROM.get(1304,cocktailcounter));
  Serial.print("lastsaved=");
  Serial.println(EEPROM.get(1308,lastsaved));
  Serial.print("Counter=");
  Serial.println(EEPROM.get(1312,counter));
    
   if (EEPROM.read(1300)==255)                                             //For first uploading EEPROMs are empty and got nan value for float and 255 for integer.This provides default values
  {
  Serial.println("DEFAULT VALUES INSTALLED");
  EEPROM.write(1300,0);
  cocktailcounter=0;
  EEPROM.put(1304,cocktailcounter);
  lastsaved=3001;
  EEPROM.put(1308,lastsaved);
  counter=3000;
  EEPROM.put(1312,counter);
  for (int x=1; x<11; x++)
      {
        Serial.println(EEPROM.put((2000+(x*4)),50.0));
      }
  }
 cocktailcounter++;
 counter++;
 EEPROM.put(1304, cocktailcounter);
 Serial.print("Cocktailcounter=");
 Serial.println(cocktailcounter);
 EEPROM.put(1312, counter);
 Serial.print("Counter=");
 Serial.println(counter);
 stringtime="";
 stringtime2="";
 stringtime2= String(hour()) + ":" + String(minute()) + ":" + String(second());
 stringtime=String(day()) + "/" + String(month()) + "/" +  String(year());
 Serial.println(stringtime);
 Serial.println(stringtime2);
 if(!SD.exists("SALES.csv"))
 {
 dataFile = SD.open("SALES.csv", FILE_WRITE);
  if (dataFile)                                                     // if the file exists write to it:
    {     
         dataFile.print("COUNTER");
         dataFile.print(","); 
         dataFile.print("NO");
         dataFile.print(",");
         dataFile.print("BUTTON_NO");
         dataFile.print(",");
         dataFile.print("COCKTAIL_NAME");
         dataFile.print(",");    
         dataFile.print("TIME");
         dataFile.print(",");    
         dataFile.println("DATE");
         Serial.println("HEADERS WROTE");
         dataFile.print(counter);
         dataFile.print(",");
         dataFile.print(cocktailcounter);
         dataFile.print(",");
         dataFile.print(ButtonNo);
         dataFile.print(",");
         dataFile.print(Cocktailname);
         dataFile.print(",");
         dataFile.print(stringtime2);
         dataFile.print(",");
         dataFile.println(stringtime); 
         Serial.println("SALES VALUES SAVED");                          
         dataFile.close();                                           // close the file   
      }          
       else 
     {
        Serial.println("error opening SALES.csv");                     // if the file didn't open, print an error:
      }
 }
  else                                                      // if the file not exists, for the first time folder creating
  {
    dataFile = SD.open("SALES.csv", FILE_WRITE);
  if (dataFile)                                                     // if the file exists write to it:
    {
           Serial.println("SALES VALUES SAVED");
           dataFile.print(counter);
           dataFile.print(",");
           dataFile.print(cocktailcounter);
           dataFile.print(",");
           dataFile.print(ButtonNo);
           dataFile.print(",");
           dataFile.print(Cocktailname);
           dataFile.print(",");
           dataFile.print(stringtime2);
           dataFile.print(",");
           dataFile.println(stringtime);                           
           dataFile.close();                                           // close the file
    }
    else
    {
      Serial.println("error opening SALES.csv");                     // if the file didn't open, print an error:
    }
  }
         
}


////////////////////////////////////////////////////////////-SENDREQUEST-/////////////////////////////////////////////////////////////
void send_request(long cocktailcounter, int buttonno,char cocktailname[30], char timechar[8], char date[8]) //Send an HTTP POST request to the Azure Mobile Service data API START
{  
  Serial.println("\nConnecting...");
  if (client.connect(server, 80)) 
  {
     
     query2="{\"USER_ID\":";
     query2 += USER_ID;
     query2 +=",";
     query2 += "\"MACHINE_ID\":";
     query2 +=MACHINE_ID;
     query2 +=",";
     query2 +="\"SALES\":";
     query2+=cocktailcounter;
     query2 +=",";
     query2 +="\"BUTTON_NO\":";
     query2+=buttonno;
     query2 +=",";
     query2 +="\"COCKTAIL_NAME\":";
     query2 +="\"";
     query2+=cocktailname;
     query2 +="\"";
     query2 +=",";
     query2 +="\"TIME\":";
     query2 +="\"";
     query2+=timechar;
     query2 +="\"";
     query2 +=",";
     query2 +="\"DATE\":";
     query2 +="\"";
     query2+=date;
     query2 +="\"";
     query2 +="}";
     
    Serial.println("Sending ");
    sprintf(buffer, "POST /tables/%s HTTP/1.1", table_name);     // POST URI Table name in Mobile service
    client.println(buffer);
    Serial.println(buffer);
    sprintf(buffer, "Host: %s", server);                         // Host header Server name in Mobile Service
    client.println(buffer); 
    Serial.println(buffer);
    sprintf(buffer, "X-ZUMO-APPLICATION: %s", ams_key);          // Azure Mobile Services application key
    client.println(buffer);
    Serial.println(buffer);
    client.println("Content-Type: application/json");            // JSON content type for the information
    Serial.println(query2);
    //client.println(query2);
   // sprintf(buffer, "{\"user_id\": %d, \"machine_id\": %d, \"buttonno\": %d, \"date\": \"%s\", \"timechar\": \"%s\" }",USER_ID, MACHINE_ID, buttonno, date,timechar);      // POST body   
   // sprintf(buffer, "{\"user_id\": %d, \"machine_id\": %d, \"buttonno\": %d, \"date\": \"%s\"}",USER_ID, MACHINE_ID, buttonno, date);      // POST body   
    //sprintf(buffer, "{\"machine_id\": %lu}", MACHINE_ID);
    //Serial.println(buffer);
        
   // char querychar[1000];
   // query.toCharArray(querychar,)
   Serial.print("Content-Length: ");                             // Content length
    Serial.println(query2.length());
    
    client.print("Content-Length: ");                             // Content length
    client.println(query2.length());
    //client.println(strlen(buffer));
    client.println();                                             // End of headers
    client.println(query2);
    //client.println(buffer);                                       // Request body
    lastAttemptTime = millis();
   
  } 
  else 
  {
      Serial.println("connection failed");
     // digitalWrite(ledPin3Active, LOW);
      lcd.clear();
      lcd.print("Internet connection"); 
      lcd.setCursor(0,1);
      lcd.print("failed...");
      lcd.setCursor(0,2); 
      lcd.print("Trying to connect...");
      getIP();
   // for (;;) ;                                                    //ENTERS LOOP WHILE ETHERNET NOT CONNECTED AND MACHINE NOT WORKS///
  }
}
///////////////////////////////////////////////////////-WAITRESPONSE-////////////////////////////////////////////////////////////////
void wait_response()
{ int responsecounter = 0;
  lastAttemptTime=millis();
  Serial.println("wait_response");
  while (!client.available()) {
    Serial.println("client not available");
      if(responsecounter>80)
      {
        client.connect(server, 80);
        Serial.println("connecting to server...");
        delay(1000);
        //break;
      }
      else
      {
        Serial.println(responsecounter);
      responsecounter++;
      }
    if (!client.connected()) 
    {
      Serial.println("client not connected");
      lcd.clear();
      lcd.print("client not connected");
      return;
      }
    }
  }

///////////////////////////////////////////////////////////-READRESPONSE-/////////////////////////////////////////////////////////////
void read_response()
{
  Serial.println("read_response");
  bool print = true;
  
  while (client.available()) {
    char c = client.read();
    //Serial.print(c);
    if (c == '\n')                                       // Print only until the first carriage return
      print = false;
    if (print)
      Serial.print(c);
  }
}
/////////////////////////////////////////////////////-ENDREQUEST-/////////////////////////////////////////////////////////
void end_request()
{
  Serial.println("\nend_request");
  client.stop();
}
void end_request2()                            // use this for displaying defaultscreen
{
  Serial.println("\nend_request");
  client.stop();
  defaultscreen();
}
///////////////////////////////////////////////////////////-READCOCKTAILTABLE//////////////////////////////////////
void read_integerbutton()
{
  Serial.println("read_integerbutton");  
    
     if(finder.findUntil("id", "}]"))
     {
                                   //it provides each button number can save specific eeprom bytes
      eepromadress=1260; 
      for(int y=1; y<11; y++)
      {
      Cocktail=finder.getValue();
      Serial.print("id=");
      Serial.println(Cocktail);
      Cocktail=finder.getValue();
      Serial.print("Userid=");
      Serial.println(Cocktail);
      Cocktail=finder.getValue();
      Serial.print("machine_id=");
      Serial.println(Cocktail);
      Cocktail=finder.getValue();
      Serial.print("ButtonNo=");
      Serial.println(Cocktail);
      Cocktail=finder.getValue();
      Serial.print("CocktailID=");
      Serial.println(Cocktail);
      Serial.print("Eepromadress=");
      Serial.println(eepromadress);
      EEPROM.put(eepromadress, Cocktail);    
      eepromadress+=4;
      }
     }
}
///////////////////////////////////////////////////////////-READCOCKTAILTABLE//////////////////////////////////////
void read_integer()
{
  Serial.println("read_integer");  
    
     if(finder.findUntil("NewCocktailName", "}"))
     {    
      eepromadress=(ButtonNo-1)*126;
      finder.getString(":",",",requestTypeString,typeLength);
      TypeString = requestTypeString;
      TypeString = TypeString.substring(1, TypeString.length() - 1);
      TypeString.toCharArray(Cocktailname, 30);
      Serial.print("Cocktail Name=");
      Serial.println(TypeString);
      Serial.println(Cocktailname);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,Cocktailname);
      eepromadress+=30;
       
      pumparray[0]=(finder.getFloat()+39);
      Serial.print("AlkolOne=");
      Serial.println(pumparray[0]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,pumparray[0]); 
      eepromadress+=4; 
           
      mlarray[0]=finder.getFloat();
      Serial.print("AlkolMlOne=");
      Serial.println(mlarray[0]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,mlarray[0]);       
      eepromadress+=4; 
           
      pumparray[1]=(finder.getFloat()+39);
      Serial.print("AlkolTwo=");
      Serial.println( pumparray[1]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,pumparray[1]);      
      eepromadress+=4;  
          
      mlarray[1]=finder.getFloat();
      Serial.print("AlkolMlTwo=");
      Serial.println(mlarray[1]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,mlarray[1]); 
      eepromadress+=4;
      
      pumparray[2]=(finder.getFloat()+39);
      Serial.print("AlkolThree=");
      Serial.println(pumparray[2]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,pumparray[2]);        
      eepromadress+=4;   
         
      mlarray[2]=finder.getFloat();
      Serial.print("AlkolMlThree=");
      Serial.println(mlarray[2]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,mlarray[2]); 
      eepromadress+=4;
      
      pumparray[3]=(finder.getFloat()+39);
      Serial.print("AlkolFour=");
      Serial.println(pumparray[3]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,pumparray[3]);        
      eepromadress+=4; 
           
      mlarray[3]=finder.getFloat();
      Serial.print("AlkolMlFour=");
      Serial.println(mlarray[3]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,mlarray[3]); 
      eepromadress+=4; 
           
      pumparray[4]=(finder.getFloat()+39);
      Serial.print("AlkolFive=");
      Serial.println( pumparray[4]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,pumparray[4]);        
      eepromadress+=4;   
         
      mlarray[4]=finder.getFloat();
      Serial.print("AlkolMlFive=");
      Serial.println(mlarray[4]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,mlarray[4]);        
      eepromadress+=4;
      
      pumparray[5]=(finder.getFloat()+39);
      Serial.print("SyrupSix=");
      Serial.println(pumparray[5]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,pumparray[5]); 
      eepromadress+=4;
            
      mlarray[5]=finder.getFloat();
      Serial.print("SyrupMlSix=");
      Serial.println(mlarray[5]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,mlarray[5]); 
      eepromadress+=4;
      
      syruprate[0]=finder.getFloat();
      Serial.print("SyrupRateSix=");
      Serial.println(syruprate[0]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,syruprate[0]);   
      eepromadress+=4; 
      
      pumparray[6]=(finder.getFloat()+39);
      Serial.print("SyrupSeven=");
      Serial.println(pumparray[6]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,pumparray[6]); 
      eepromadress+=4;  
                
      mlarray[6]=finder.getFloat();
      Serial.print("SyrupMlSeven=");
      Serial.println( mlarray[6]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,mlarray[6]); 
      eepromadress+=4;
      
      syruprate[1]=finder.getFloat();
      Serial.print("SyrupRateSeven=");
      Serial.println(syruprate[1]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,syruprate[1]); 
      eepromadress+=4;

      pumparray[7]=(finder.getFloat()+39);
      Serial.print("SyrupEight=");
      Serial.println(pumparray[7]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,pumparray[7]); 
      eepromadress+=4;
            
      mlarray[7]=finder.getFloat();
      Serial.print("SyrupMlEight=");
      Serial.println( mlarray[7]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,mlarray[7]); 
      eepromadress+=4;
      
      syruprate[2]=finder.getFloat();
      Serial.print("SyrupRateEight=");
      Serial.println(syruprate[2]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,syruprate[2]); 
      eepromadress+=4;

      pumparray[8]=(finder.getFloat()+39);
      Serial.print("SyrupNine=");
      Serial.println(pumparray[8]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,pumparray[8]);       
      eepromadress+=4;      
      
      mlarray[8]=finder.getFloat();
      Serial.print("SyrupMlNine=");
      Serial.println( mlarray[8]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,mlarray[8]);    
      eepromadress+=4;
      
      syruprate[3]=finder.getFloat();
      Serial.print("SyrupRateNine=");
      Serial.println(syruprate[3]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,syruprate[3]);   
      eepromadress+=4; 
      
      pumparray[9]=(finder.getFloat()+39);
      Serial.print("Water=");
      Serial.println(pumparray[9]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,pumparray[9]); 
      eepromadress+=4;   
         
      mlarray[9]=finder.getFloat();
      Serial.print("WaterMl=");
      Serial.println( mlarray[9]);
      Serial.println(eepromadress);
      EEPROM.put(eepromadress,mlarray[9]); 
      eepromadress+=4; 
     }
}

/////////////////////////////////////////////////////-VOIDDOWNLOAD-///////////////////////////////////////////////////////
void connectToServer()
{  
  Serial.println("\nConnectingToServer");         // attempt to connect, and wait a millisecond:
  if (client.connect(server, 80)) 
  {
    Serial.println("making HTTP request...");
    // POST URI
    sprintf(buffer, "POST /tables/%s HTTP/1.1", table_name);
    client.println(buffer);
    /*Serial.println("making HTTP request...");
    query="GET /tables/Butonlar?$filter=machine_id%20eq%20";
    query += "'";
    query += MACHINE_ID;
    query += "'";
    query +="  HTTP/1.1";
    Serial.println(query);
    client.println(query);
    Serial.println("HTTP request made...");*/
    sprintf(buffer, "Host: %s", server);
    client.println(buffer);
    sprintf(buffer, "X-ZUMO-APPLICATION: %s", ams_key);           // Azure Mobile Services application key
    client.println(buffer);
    client.println("Content-Type: application/json");             //  JSON content type
    client.print("Content-Length: ");                             // Content length
    client.println(strlen(buffer));
    client.println();                                             // End of headers
    client.println(buffer);                                       // Request body
    //lcd.setCursor(0,1);
    //lcd.print("Connected");
   
   // String inChar2 = client.readString();     Serial.println(inChar2);                      // to get azure table data

    

  }
else 
    {
      Serial.println("connection failed");
      lcd.clear();
      lcd.print("Internet connection"); 
      lcd.setCursor(0,1);
      lcd.print("failed...");
      lcd.setCursor(0,2); 
      lcd.print("Trying to connect...");
      getIP();
     }
  }
/////////////////////////////////////////////////////-DOWNLOADBUTTON-///////////////////////////////////////////////////////
void downloadbutton()
{
 // ButtonNo=10;
  
  Serial.println("\nConnecting to server downloadbutton mode");         // attempt to connect, and wait a millisecond:
  if (client.connect(server, 80)) 
  {
    Serial.println("making HTTP request...");
    query="GET /tables/Butonlar?$filter=machine_id%20eq%20";
    query += "'";
    query += MACHINE_ID;
    query += "'";
    query +="  HTTP/1.1";
    Serial.println(query);
    client.println(query);
    Serial.println("HTTP request made...");
    sprintf(buffer, "Host: %s", server);
    client.println(buffer);
    sprintf(buffer, "X-ZUMO-APPLICATION: %s", ams_key);           // Azure Mobile Services application key
    client.println(buffer);
    client.println("Content-Type: application/json");             //  JSON content type
    client.print("Content-Length: ");                             // Content length
    client.println(strlen(buffer));
    client.println();                                             // End of headers
    client.println(buffer);                                       // Request body
    lcd.setCursor(0,1);
    lcd.print("Connected");
   
   // String inChar2 = client.readString();     Serial.println(inChar2);                      // to get azure table data
  }
  
else 
    {
      Serial.println("connection failed");
      lcd.clear();
      lcd.print("Internet connection"); 
      lcd.setCursor(0,1);
      lcd.print("failed...");
      lcd.setCursor(0,2); 
      lcd.print("Trying to connect...");
      getIP();
     }
  }


/////////////////////////////////////////////////////-VOIDDOWNLOAD-///////////////////////////////////////////////////////
void download()
{ 
  Serial.println("\nConnecting to server download mode");         // attempt to connect, and wait a millisecond:
  if (client.connect(server, 80)) 
  {
     Serial.println("making HTTP request...");
     query="GET /tables/Kokteyler?$filter=id%20eq%20";
     query += "'";
     query +=CocktailNo;
     query += "'";
     query +="  HTTP/1.1";
    Serial.println(query);
    client.println(query);
    
   /* client.print("GET /tables/BeverageManagement?$filter=machine_id%20eq%20");
    client.print(MACHINE_ID);
    client.println("  HTTP/1.1");*/
    
    Serial.println("HTTP request made...");
    sprintf(buffer, "Host: %s", server);
    client.println(buffer);
    sprintf(buffer, "X-ZUMO-APPLICATION: %s", ams_key);           // Azure Mobile Services application key
    client.println(buffer);
    client.println("Content-Type: application/json");             //  JSON content type
    client.print("Content-Length: ");                             // Content length
    client.println(strlen(buffer));
    client.println();                                             // End of headers
    client.println(buffer);                                       // Request body
    lcd.setCursor(0,2);
    lcd.print("                    ");
    lcd.setCursor(0,2);
    lcd.print("Loading...");

  //  String inChar2 = client.readString();     Serial.println(inChar2);                      // to get azure table data
  
  }
else 
    {
      Serial.println("connection failed");
      lcd.clear();
      lcd.print("Internet connection"); 
      lcd.setCursor(0,1);
      lcd.print("failed...");
      lcd.setCursor(0,2); 
      lcd.print("Trying to connect...");
      getIP();
     }
  }


/////////////////////////////////////////////////////////////////////-GETIP-/////////////////////////////////////////////////
void getIP()
{
  lcd.setCursor(0,4);
  lcd.print("                    ");
  lcd.setCursor(0,4);
  lcd.print("Trying to Connect");
  if (Ethernet.begin(mac) == 0)                                    //ETHERNET ERROR
  {    
    uploadchecker=false;                   
    Serial.println("Failed to configure Ethernet using DHCP");
    Serial.println();
    lcd.clear();
    lcd.print("Internet connection"); 
    lcd.setCursor(0,1);
    lcd.print("failed...");
    delay(3000);
  //  lcd.setCursor(0,2); 
  //  lcd.print("Trying to connect...");
   // getIP();              //ENTERS LOOP until it connects
    // for (;;) ;           //ENTERS LOOP WHILE ETHERNET NOT CONNECTED AND MACHINE NOT WORKS///
  }
  else
  {
    uploadchecker=true;
    Serial.print("IP address:  ");
    lcd.setCursor(0,3);
    lcd.print("                    ");
    lcd.setCursor(0,3);
    lcd.print("IP:");
   // defaultscreen=1;
    for (byte thisByte = 0; thisByte < 4; thisByte++) 
    {
      int x;
      x= Ethernet.localIP()[thisByte];
      Serial.print(x, DEC);          // print the value of each byte of the IP address:
      Serial.print(".");
      lcd.print(x, DEC);
      lcd.print(".");
    }
    delay(1000);                    // without delay can not connect to azure and it shows IP on display
  }
  Serial.println();
  
}

void defaultscreen()
{
  if (displaylocker)
  {
  lcd.clear();
  lcd.print("1  5   9  13  17  ");
  lcd.setCursor(0,1);
  lcd.print("2  6  10  14  18  ");
  lcd.setCursor(0,2);
  lcd.print("3  7  11  15  19  ");
  lcd.setCursor(0,3);
  lcd.print("4  8  12  16  20  ");
  sensorcheckerup[0] = true;
  sensorcheckerdown[0] = true;
  sensorcheckerup[1] = true;
  sensorcheckerdown[1] = true;
  lastAttemptTime=millis();
  }
}
void defaultscreen2()
{
  if (displaylocker)
  {
  lcd.setCursor(0,0); lcd.print(" "); lcd.setCursor(0,0); lcd.print("1");
  lcd.setCursor(0,1); lcd.print(" "); lcd.setCursor(0,1); lcd.print("2");
  lcd.setCursor(0,2); lcd.print(" "); lcd.setCursor(0,2); lcd.print("3");
  lcd.setCursor(0,3); lcd.print(" "); lcd.setCursor(0,3); lcd.print("4");

  lcd.setCursor(3,0); lcd.print(" "); lcd.setCursor(3,0); lcd.print("5");
  lcd.setCursor(3,1); lcd.print(" "); lcd.setCursor(3,1); lcd.print("6");
  lcd.setCursor(3,2); lcd.print(" "); lcd.setCursor(3,2); lcd.print("7");
  lcd.setCursor(3,3); lcd.print(" "); lcd.setCursor(3,3); lcd.print("8");

  lcd.setCursor(7,0); lcd.print(" "); lcd.setCursor(6,0); lcd.print("9");
  lcd.setCursor(6,1); lcd.print(" "); lcd.setCursor(6,1); lcd.print("10");
  lcd.setCursor(6,2); lcd.print(" "); lcd.setCursor(6,2); lcd.print("11");
  lcd.setCursor(6,3); lcd.print(" "); lcd.setCursor(6,3); lcd.print("12");

  lcd.setCursor(10,0); lcd.print(" "); lcd.setCursor(10,0); lcd.print("13");
  lcd.setCursor(10,1); lcd.print(" "); lcd.setCursor(10,1); lcd.print("14");
  lcd.setCursor(10,2); lcd.print(" "); lcd.setCursor(10,2); lcd.print("15");
  lcd.setCursor(10,3); lcd.print(" "); lcd.setCursor(10,3); lcd.print("16");

  lcd.setCursor(14,0); lcd.print(" "); lcd.setCursor(14,0); lcd.print("17");
  lcd.setCursor(14,1); lcd.print(" "); lcd.setCursor(14,1); lcd.print("18");
  lcd.setCursor(14,2); lcd.print(" "); lcd.setCursor(14,2); lcd.print("19");
  lcd.setCursor(14,3); lcd.print(" "); lcd.setCursor(14,3); lcd.print("20");
  }
}
int timecounter;                    //checking rtc for 5 times
void Time()
{
  setSyncProvider(RTC.get);          // the function to get the time from the RTC
  if(timeStatus() == timeSet)
  {
    Serial.println(" Ok!");
  }
   else                                // SAAT  UYARISI NORMALDE AÇIK
  {
    Serial.println(" FAIL!");
    lcd.setCursor(0,0);
    lcd.print("                    ");
    lcd.setCursor(0,0);
    lcd.print("TIME ERROR");
    delay(500);
    timecounter++;
    if (timecounter<6)
    {
    Time();
    }
    else
    {
      timecounter=0;
    }
  }
  
}
////////////////////////////////////////////////////////////////-BUTTON-////////////////////////////////////////////////////
void button(int ButtonNo)
{
 if(mode==false)
      {
      pumpwork=true;
       dataFile = SD.open("README.txt");
       delay(50);
  if (dataFile) 
  {
    lcd.clear();
    lcd.print("SD CARD ERROR!!!");
    lcd.setCursor(0,1);
    lcd.print("Please Insert ");
    lcd.setCursor(0,2);
    lcd.print("SD Card end ");
    lcd.setCursor(0,3);
    lcd.print("Restart Machine");
    while (dataFile.available()) 
    {
    dataFile.read();
    }             
    dataFile.close();                                                 // close the file:
  } 
  else 
  {
    lcd.clear();
    lcd.print("SD CARD ERROR!!!");
    lcd.setCursor(0,1);
    lcd.print("Please Insert ");
    lcd.setCursor(0,2);
    lcd.print("SD Card end ");
    lcd.setCursor(0,3);
    lcd.print("Restart Machine");
    for(;;); 
  } 
  
      lcd.clear();
      lcd.print("BUTTON ");
      lcd.print(ButtonNo);
      lcd.print(" COCTAIL IS PREPARING...");
      reservoirchecker = true;                           // for displaying empty reservoirs
        
        eepromadress=(ButtonNo-1)*126;
        EEPROM.get(eepromadress ,Cocktailname );  
        eepromadress+=30;                             
        EEPROM.get(eepromadress,pumparray[0]);
        eepromadress+=4;
        EEPROM.get(eepromadress,mlarray[0]) ;    
        eepromadress+=4;
        EEPROM.get(eepromadress,pumparray[1]);
        eepromadress+=4;
        EEPROM.get(eepromadress,mlarray[1]);
        eepromadress+=4;
        EEPROM.get(eepromadress,pumparray[2]);
        eepromadress+=4;
        EEPROM.get(eepromadress,mlarray[2]);
        eepromadress+=4;
        EEPROM.get(eepromadress,pumparray[3]);
        eepromadress+=4;
        EEPROM.get(eepromadress,mlarray[3]);
        eepromadress+=4;
        EEPROM.get(eepromadress,pumparray[4]);
        eepromadress+=4;
        EEPROM.get(eepromadress,mlarray[4]);
        eepromadress+=4;
        EEPROM.get(eepromadress,pumparray[5]);
        eepromadress+=4;
        EEPROM.get(eepromadress,mlarray[5]);
        eepromadress+=4;
        mlwaterarray[0]=mlarray[5]*syruprate[0];                    // water ml for syrup
        EEPROM.get(eepromadress,syruprate[0]);
        eepromadress+=4;
        EEPROM.get(eepromadress,pumparray[6]);
        eepromadress+=4;
        EEPROM.get(eepromadress,mlarray[6]);
        eepromadress+=4;
        EEPROM.get(eepromadress,syruprate[1]);
        mlwaterarray[1]=mlarray[6]*syruprate[1];                    // water ml for syrup
        eepromadress+=4;
        EEPROM.get(eepromadress,pumparray[7]);
        eepromadress+=4;
        EEPROM.get(eepromadress,mlarray[7]);
        eepromadress+=4;
        EEPROM.get(eepromadress,syruprate[2]);
        mlwaterarray[2]=mlarray[7]*syruprate[2];                    // water ml for syrup
        eepromadress+=4;
        EEPROM.get(eepromadress,pumparray[8]);
        eepromadress+=4;
        EEPROM.get(eepromadress,mlarray[8]);
        eepromadress+=4;
        EEPROM.get(eepromadress,syruprate[3]);
        mlwaterarray[3]=mlarray[8]*syruprate[3];                    // water ml for syrup  
        eepromadress+=4;
        EEPROM.get(eepromadress,pumparray[9]);          
        eepromadress+=4;
        EEPROM.get(eepromadress,mlarray[9]);
        mlarray[9]=mlwaterarray[0]+mlwaterarray[1]+mlwaterarray[2]+mlwaterarray[3]+mlarray[9];

        for (int i=0; i<10; i++)                   // checks reservoirs
        {
          for (int y=1; y<11; y++);                         // "y" should be equal to pump amount + 1
          {
            if ((pumparray[i]-39)==1)                       //if ((pumparray[i]-39)==1) default value should be 1
            {
              if ((sensorvaluedown[0]=digitalRead(22))==0)
              {
                pumpwork = false;
                if(reservoirchecker)
                {
                  lcd.clear();
                  reservoirchecker = false;
                  }
                lcd.setCursor(0,0);
                lcd.print("                    ");
                lcd.setCursor(0,0);
                lcd.print("Reservoir 1 Empty");
                Time2=millis();
                Time2checker= true;
              }
            }
            if ((pumparray[i]-39)==2)                  //if ((pumparray[i]-39)==2) default value should be 2
            {
              if ((sensorvaluedown[1]=digitalRead(24))==0)
              {
                pumpwork = false;
                if(reservoirchecker)
                {
                  lcd.clear();
                  reservoirchecker = false;
                  }
                lcd.setCursor(0,1);
                lcd.print("                    ");
                lcd.setCursor(0,1);
                lcd.print("Reservoir 2 Empty");
                Time2=millis();
                Time2checker= true;
              }
            }
            /* // 10 sensor code
            if ((pumparray[i]-39)==3)                  
            {
              if ((sensorvaluedown[1]=digitalRead(26))==0)
              {
                pumpwork = false;
                if(reservoirchecker)
                {
                  lcd.clear();
                  reservoirchecker = false;
                  }
                Serial.println("Reservoir 2 Empty");
                lcd.setCursor(0,1);
                lcd.print("                    ");
                lcd.setCursor(0,1);
                lcd.print("Reservoir 2 Empty");
                Time2=millis();
                Time2checker= true;
              }
            }
            if ((pumparray[i]-39)==4)                  
            {
              if ((sensorvaluedown[1]=digitalRead(39))==0)
              {
                pumpwork = false;
                if(reservoirchecker)
                {
                  lcd.clear();
                  reservoirchecker = false;
                  }
                Serial.println("Reservoir 2 Empty");
                lcd.setCursor(0,1);
                lcd.print("                    ");
                lcd.setCursor(0,1);
                lcd.print("Reservoir 2 Empty");
                Time2=millis();
                Time2checker= true;
              }
            }
            if ((pumparray[i]-39)==5)                  
            {
              if ((sensorvaluedown[1]=digitalRead(30))==0)
              {
                pumpwork = false;
                if(reservoirchecker)
                {
                  lcd.clear();
                  reservoirchecker = false;
                  }
                Serial.println("Reservoir 2 Empty");
                lcd.setCursor(0,1);
                lcd.print("                    ");
                lcd.setCursor(0,1);
                lcd.print("Reservoir 2 Empty");
                Time2=millis();
                Time2checker= true;
              }
            }
            if ((pumparray[i]-39)==6)                  
            {
              if ((sensorvaluedown[1]=digitalRead(32))==0)
              {
                pumpwork = false;
                if(reservoirchecker)
                {
                  lcd.clear();
                  reservoirchecker = false;
                  }
                Serial.println("Reservoir 2 Empty");
                lcd.setCursor(0,1);
                lcd.print("                    ");
                lcd.setCursor(0,1);
                lcd.print("Reservoir 2 Empty");
                Time2=millis();
                Time2checker= true;
              }
            }
            if ((pumparray[i]-39)==7)                  
            {
              if ((sensorvaluedown[1]=digitalRead(34))==0)
              {
                pumpwork = false;
                if(reservoirchecker)
                {
                  lcd.clear();
                  reservoirchecker = false;
                  }
                Serial.println("Reservoir 2 Empty");
                lcd.setCursor(0,1);
                lcd.print("                    ");
                lcd.setCursor(0,1);
                lcd.print("Reservoir 2 Empty");
                Time2=millis();
                Time2checker= true;
              }
            }
            if ((pumparray[i]-39)==8)                  
            {
              if ((sensorvaluedown[1]=digitalRead(36))==0)
              {
                pumpwork = false;
                if(reservoirchecker)
                {
                  lcd.clear();
                  reservoirchecker = false;
                  }
                Serial.println("Reservoir 2 Empty");
                lcd.setCursor(0,1);
                lcd.print("                    ");
                lcd.setCursor(0,1);
                lcd.print("Reservoir 2 Empty");
                Time2=millis();
                Time2checker= true;
              }
            }
            if ((pumparray[i]-39)==9)                  
            {
              if ((sensorvaluedown[1]=digitalRead(38))==0)
              {
                pumpwork = false;
                if(reservoirchecker)
                {
                  lcd.clear();
                  reservoirchecker = false;
                  }
                Serial.println("Reservoir 2 Empty");
                lcd.setCursor(0,1);
                lcd.print("                    ");
                lcd.setCursor(0,1);
                lcd.print("Reservoir 2 Empty");
                Time2=millis();
                Time2checker= true;
              }
            }
            if ((pumparray[i]-39)==10)                  
            {
              if ((sensorvaluedown[1]=digitalRead(40))==0)
              {
                pumpwork = false;
                if(reservoirchecker)
                {
                  lcd.clear();
                  reservoirchecker = false;
                  }
                Serial.println("Reservoir 2 Empty");
                lcd.setCursor(0,1);
                lcd.print("                    ");
                lcd.setCursor(0,1);
                lcd.print("Reservoir 2 Empty");
                Time2=millis();
                Time2checker= true;
              }
            }                 
            */             // 10 sensor code
          }
        }
       
       Max=0;
        for (int a=0; a<10; a++)                      // finds Maximum pump work time for alcohol or syrup
        {
          EEPROM.get((2000+((pumparray[a]-39)*4)),motordelay[a]);  
          if(Max<mlarray[a]*motordelay[a]) 
          {
            Max=mlarray[a]*motordelay[a];
          }  
        }
      
        Max=Max+1000;
        Time2checker=millis()+Max+1000;
        

        
        for(int x=0; x<9; x++)                   //default values
        {
           upper[x]=false;
           medium[x]=true;
           lower[x]=false;
           upperend[x]=true;
           mediumend[x]=true;
           lowerend[x]=true;
           upperendchecker[x]=false;
           array[x]=((pumparray[x]-39)*2)+21;          //calculates which sensors going to check
           array2[x]=((pumparray[x]-39)*2)+20;          //calculates which sensors going to check
        }

        
   if(pumpwork)
   {             
        for (int i=0; i<10; i++)
        {
        digitalWrite(pumparray[i],HIGH);
        }
   }
  Time1 = millis();                         // saves motors activate time
  
while(millis() < Time1+Max && pumpwork)
{    
      ////////////////////////////////////////////UP-SENSOR-CHECK//////////////////////

     if(upperend[0])
     { 
      if(digitalRead(array[0])== 0)
      {
        upperend[0]=false;
        upperendchecker[0]=true;
        medium[0]=false;
      }
     }
     if(upperendchecker[0])
     {
      if(digitalRead(array[0])== 1)
      {
        timer[0]=millis();
        upperendchecker[0]=false;
        upper[0]=true;
      }
     }

     /*         ÜSTTEKİNE GÖRE      DÜZENLE
     if(upperend[1])
     {
      if(digitalRead(array[1])== 0)
      {
        EEPROM.put((((pumparray[1]-39)*4)+3000),0);
        timer[1]=millis();
        upper[1]=true;
        upperend[1]=false;
      }
     }
     if(upperend[2])
     {
      if(digitalRead(array[2])== 0)
      {
        EEPROM.put((((pumparray[2]-39)*4)+3000),0);
        timer[2]=millis();
        upper[2]=true;
        upperend[2]=false;
      }
     }
     if(upperend[3])
     {
      if(digitalRead(array[3])== 0)
      {
        EEPROM.put((((pumparray[3]-39)*4)+3000),0);
        timer[3]=millis();
        upper[3]=true;
        upperend[3]=false;
      }
     }
     if(upperend[4])
     {
      if(digitalRead(array[4])== 0)
      {
        EEPROM.put((((pumparray[4]-39)*4)+3000),0);
        timer[4]=millis();
        upper[4]=true;
        upperend[4]=false;
      }
     }
     if(upperend[5])
     {
      if(digitalRead(array[5])== 0)
      {
        EEPROM.put((((pumparray[5]-39)*4)+3000),0);
        timer[5]=millis();
        upper[5]=true;
        upperend[5]=false;
      }
     }
     if(upperend[6])
     {
      if(digitalRead(array[6])== 0)
      {
        EEPROM.put((((pumparray[6]-39)*4)+3000),0);
        timer[6]=millis();
        upper[6]=true;
        upperend[6]=false;
      }
     }
     if(upperend[7])
     {
      if(digitalRead(array[7])== 0)
      {
        EEPROM.put((((pumparray[7]-39)*4)+3000),0);
        timer[7]=millis();
        upper[7]=true;
        upperend[7]=false;
      }
     }
     if(upperend[8])
     {
      if(digitalRead(array[8])== 0)
      {
        EEPROM.put((((pumparray[8]-39)*4)+3000),0);
        timer[8]=millis();
        upper[8]=true;
        upperend[8]=false;
      }
     }
*/
        ////////////////////////////////////////////DOWN-SENSOR-CHECK//////////////////////
       if(lowerend[0])
        {
        if(digitalRead(array2[0])== 0)
      {
        timer2[0]=millis();
        lower[0]=true;
        lowerend[0]=false;
      }
        }
        
        if(lowerend[1])
        {
      if(digitalRead(array2[1])== 0)
      {
        timer2[1]=millis();
        lower[1]=true;
        lowerend[1]=false;
      }
        }
        if(lowerend[2])
        {
      if(digitalRead(array2[2])== 0)
      {
        timer2[2]=millis();
        lower[2]=true;
        lowerend[2]=false;
      }
        }
        if(lowerend[3])
        {
      if(digitalRead(array2[3])== 0)
      {
        timer2[3]=millis();
        lower[3]=true;
        lowerend[3]=false;
      }
        }
        if(lowerend[4])
        {
      if(digitalRead(array2[4])== 0)
      {
        timer2[4]=millis();
        lower[4]=true;
        lowerend[4]=false;
      }
        }
        if(lowerend[5])
        {
      if(digitalRead(array2[5])== 0)
      {
        timer2[5]=millis();
        lower[5]=true;
        lowerend[5]=false;
      }
        }
        if(lowerend[6])
        {
      if(digitalRead(array2[6])== 0)
      {
        timer2[6]=millis();
        lower[6]=true;
        lowerend[6]=false;
      }
        }
        if(lowerend[7])
        {
      if(digitalRead(array2[7])== 0)
      {
        timer2[7]=millis();
        lower[7]=true;
        lowerend[7]=false;
      }
        }
        if(lowerend[8])
        {
      if(digitalRead(array2[8])== 0)
      {
        timer2[8]=millis();
        lower[8]=true;
        lowerend[8]=false;
      }
        }

       
      if(millis() > Time1+(mlarray[0]*motordelay[0]))
      {
        digitalWrite(pumparray[0],LOW);
        
        if(upper[0])
        {
        timer[0]=millis()- timer[0];
        EEPROM.put((((pumparray[0]-39)*4)+3000),timer[0]);
        upper[0]=false;  
        medium[0]=false;  
        }
        
        if(lower[0])
        {
          timer2[0]=timer2[0]-Time1;
          EEPROM.get((((pumparray[0]-39)*4)+3000),voidarray[0]);
          voidarray[0]+=timer2[0];
          voidarray[0]=(voidarray[0]/hazne);
          EEPROM.put((((pumparray[0]-39)*4)+2000),voidarray[0]);
          lower[0]=false;
          medium[0]=false;
          Serial.println(voidarray[0],6);
        }

        if(medium[0])
        {
        EEPROM.get(((pumparray[0]-39)*4)+3000,voidarray[0]);
        voidarray[0]+=mlarray[0]*motordelay[0];
        EEPROM.put(((pumparray[0]-39)*4)+3000,voidarray[0]);
        medium[0]=false;
        }
        
        }

      if(millis() > Time1+(mlarray[1]*motordelay[1])) 
      {
        digitalWrite(pumparray[1],LOW);

        if(upper[1])
        {
        timer[1]=millis()-timer[1];
        EEPROM.put((((pumparray[1]-39)*4)+3000),timer[1]);
        upper[1]=false;   
        medium[1]=false; 
        }
        
        if(lower[1])
        {
          timer2[1]=timer2[1]-Time1;
          EEPROM.get((((pumparray[1]-39)*4)+3000),voidarray[1]);
          voidarray[1]+=timer2[1];
          voidarray[1]=(voidarray[1]/hazne)*10;
          EEPROM.put((((pumparray[1]-39)*4)+2000),voidarray[1]);
          lower[1]=false;
          medium[1]=false;
        }

        if(medium[1])
        {
        EEPROM.get((((pumparray[1]-39)*4)+3000),voidarray[1]);
        voidarray[1]+=(mlarray[1]*motordelay[1]);
        EEPROM.put((((pumparray[1]-39)*4)+3000),voidarray[1]);
        medium[1]=false;
        }
        
        }
        
        if(millis() > Time1+(mlarray[2]*motordelay[2])) 
      {
        digitalWrite(pumparray[2],LOW);

        if(upper[2])
        {
        timer[2]=millis()-timer[2];
        EEPROM.put((((pumparray[2]-39)*4)+3000),timer[2]);
        upper[2]=false; 
        medium[2]=false;   
        }
        
        if(lower[2])
        {
          timer2[2]=timer2[2]-Time1;
          EEPROM.get((((pumparray[2]-39)*4)+3000),voidarray[2]);
          voidarray[2]+=timer2[2];
          voidarray[2]=(voidarray[2]/hazne)*10;
          EEPROM.put((((pumparray[2]-39)*4)+2000),voidarray[2]);
          lower[2]=false;
          medium[2]=false;
        }

        if(medium[2])
        {
        EEPROM.get((((pumparray[2]-39)*4)+3000),voidarray[2]);
        voidarray[2]+=(mlarray[2]*motordelay[2]);
        EEPROM.put((((pumparray[2]-39)*4)+3000),voidarray[2]);
        medium[2]=false;
        }
        
        }
        
      if(millis() > Time1+(mlarray[3]*motordelay[3])) 
      {
        digitalWrite(pumparray[3],LOW);

        if(upper[3])
        {
        timer[0]=millis()-timer[3];
        EEPROM.put((((pumparray[3]-39)*4)+3000),timer[3]);
        upper[3]=false; 
        medium[3]=false;   
        }
        
        if(lower[3])
        {
          timer2[3]=timer2[3]-Time1;
          EEPROM.get((((pumparray[3]-39)*4)+3000),voidarray[3]);
          voidarray[3]+=timer2[3];
          voidarray[3]=(voidarray[3]/hazne)*10;
          EEPROM.put((((pumparray[3]-39)*4)+2000),voidarray[3]);
          lower[3]=false;
          medium[3]=false;
        }

        if(medium[3])
        {
        EEPROM.get((((pumparray[3]-39)*4)+3000),voidarray[3]);
        voidarray[3]+=(mlarray[3]*motordelay[3]);
        EEPROM.put((((pumparray[3]-39)*4)+3000),voidarray[3]);
        medium[3]=false;
        }
        
        }
        
        if(millis() > Time1+(mlarray[4]*motordelay[4])) 
      {
        digitalWrite(pumparray[4],LOW);

        if(upper[4])
        {
        timer[4]=millis()-timer[4];
        EEPROM.put((((pumparray[4]-39)*4)+3000),timer[4]);
        upper[4]=false;   
        medium[4]=false; 
        }
        
        if(lower[4])
        {
          timer2[4]=timer2[4]-Time1;
          EEPROM.get((((pumparray[4]-39)*4)+3000),voidarray[4]);
          voidarray[4]+=timer2[4];
          voidarray[4]=(voidarray[4]/hazne)*10;
          EEPROM.put((((pumparray[4]-39)*4)+2000),voidarray[4]);
          lower[4]=false;
          medium[4]=false;
        }

        if(medium[4])
        {
        EEPROM.get((((pumparray[4]-39)*4)+3000),voidarray[4]);
        voidarray[4]+=(mlarray[4]*motordelay[4]);
        EEPROM.put((((pumparray[4]-39)*4)+3000),voidarray[4]);
        medium[4]=false;
        }
        
        }
        
        if(millis() > Time1+(mlarray[5]*motordelay[5])) 
      {
        digitalWrite(pumparray[5],LOW);

        if(upper[5])
        {
        timer[5]=millis()-timer[5];
        EEPROM.put((((pumparray[5]-39)*4)+3000),timer[5]);
        upper[5]=false;  
        medium[5]=false;  
        }
        
        if(lower[5])
        {
          timer2[5]=timer2[5]-Time1;
          EEPROM.get((((pumparray[5]-39)*4)+3000),voidarray[5]);
          voidarray[5]+=timer2[5];
          voidarray[5]=(voidarray[5]/hazne)*10;
          EEPROM.put((((pumparray[5]-39)*4)+2000),voidarray[5]);
          lower[5]=false;
          medium[5]=false;
        }

        if(medium[5])
        {
        EEPROM.get((((pumparray[5]-39)*4)+3000),voidarray[5]);
        voidarray[5]+=(mlarray[5]*motordelay[5]);
        EEPROM.put((((pumparray[5]-39)*4)+3000),voidarray[5]);
        medium[5]=false;
        }
        
        }
        
      if(millis() > Time1+(mlarray[6]*motordelay[6])) 
      {
        digitalWrite(pumparray[6],LOW);

        if(upper[6])
        {
        timer[6]=millis()-timer[6];
        EEPROM.put((((pumparray[6]-39)*4)+3000),timer[6]);
        upper[6]=false;    
        medium[6]=false;
        }
        
        if(lower[6])
        {
          timer2[6]=timer2[6]-Time1;
          EEPROM.get((((pumparray[6]-39)*4)+3000),voidarray[6]);
          voidarray[6]+=timer2[6];
          voidarray[6]=(voidarray[6]/hazne)*10;
          EEPROM.put((((pumparray[6]-39)*4)+2000),voidarray[6]);
          lower[6]=false;
          medium[6]=false;
        }

        if(medium[6])
        {
        EEPROM.get((((pumparray[6]-39)*4)+3000),voidarray[6]);
        voidarray[6]+=(mlarray[6]*motordelay[6]);
        EEPROM.put((((pumparray[6]-39)*4)+3000),voidarray[6]);
        medium[6]=false;
        }
        
        }
        
        if(millis() > Time1+(mlarray[7]*motordelay[7])) 
      {
        digitalWrite(pumparray[7],LOW);

        if(upper[7])
        {
        timer[7]=millis()-timer[7];
        EEPROM.put((((pumparray[7]-39)*4)+3000),timer[7]);
        upper[7]=false; 
        medium[7]=false;   
        }
        
        if(lower[7])
        {
          timer2[7]=timer2[7]-Time1;
          EEPROM.get((((pumparray[7]-39)*4)+3000),voidarray[7]);
          voidarray[7]+=timer2[7];
          voidarray[7]=(voidarray[7]/hazne)*10;
          EEPROM.put((((pumparray[7]-39)*4)+2000),voidarray[7]);
          lower[7]=false;
          medium[7]=false;
        }

        if(medium[7])
        {
        EEPROM.get((((pumparray[7]-39)*4)+3000),voidarray[7]);
        voidarray[7]+=(mlarray[0]*motordelay[7]);
        EEPROM.put((((pumparray[7]-39)*4)+3000),voidarray[7]);
        medium[7]=false;
        }
        
        }
        
      if(millis() > Time1+(mlarray[8]*motordelay[8])) 
      {
        digitalWrite(pumparray[8],LOW);

        if(upper[8])
        {
        timer[8]=millis()-timer[8];
        EEPROM.put((((pumparray[8]-39)*4)+3000),timer[8]);
        upper[8]=false;
        medium[8]=false;    
        }
        
        if(lower[8])
        {
          timer2[8]=timer2[8]-Time1;
          EEPROM.get((((pumparray[8]-39)*4)+3000),voidarray[8]);
          voidarray[8]+=timer2[8];
          voidarray[8]=(voidarray[8]/hazne)*10;
          EEPROM.put((((pumparray[8]-39)*4)+2000),voidarray[8]);
          lower[8]=false;
          medium[8]=false;
        }

        if(medium[8])
        {
        EEPROM.get((((pumparray[8]-39)*4)+3000),voidarray[8]);
        voidarray[8]+=(mlarray[8]*motordelay[8]);
        EEPROM.put((((pumparray[8]-39)*4)+3000),voidarray[8]);
        medium[8]=false;
        }
        
        }
        
        if(millis() > Time1+(mlarray[9]*100))
      {
        digitalWrite(pumparray[9],LOW);   // water is standart no need to calibration
      //  Serial.println("WATER");
        }
        
        if (millis() >= (Time1+Max)-50)                              //shows default screen
        {
           send_sd_request();     
        }

}

    }
/////////////////////////////////////////////////////////////-MANUALCALIBRATION-///////////////////////////////////////////////////////
    else                                                      
    {
      
      calibratecounter++;
      lcd.setCursor(0,1);
      lcd.print("                    ");
      lcd.setCursor(0,2);
      lcd.print("                    ");
      lcd.setCursor(0,3);
      lcd.print("                    ");
      lcd.setCursor(0,1);
      lcd.print("RESERVOIR ");
      lcd.print(ButtonNo);
      lcd.setCursor(0,2);
      lcd.print("PREPARING... ");
      ButtonNo= (2*ButtonNo)-1;                  //provides to check correct sensor

      if (calibratecounter==1)
      {
        if (digitalRead(ButtonNo+22) == 1)
        {
          lcd.setCursor(0,2);
          lcd.print("                    ");
          lcd.setCursor(0,2);
          lcd.print("PLEASE FILL THE");
          lcd.setCursor(0,3);
          lcd.print("                    ");
          lcd.setCursor(0,3);
          lcd.print("RESERVOIR");
          lcd.print((ButtonNo+1)/2);
          lcd.print("COMPLETELY");
          while(digitalRead(ButtonNo+22) == 1)
          {
            lcd.setCursor(17,2);
            lcd.print("   ");
            delay(250);
            lcd.setCursor(17,2);
            lcd.print("!!!");
            delay(250);
          }
          lcd.setCursor(0,2);
          lcd.print("                    ");
          lcd.setCursor(0,3);
          lcd.print("                    ");
          lcd.setCursor(0,2);
          lcd.print("PREPARING...");
          
        }
        
        while(digitalRead(ButtonNo+22) == 0)
        {
        digitalWrite((ButtonNo+39),HIGH);
        }
        digitalWrite((ButtonNo+39),LOW);
        lcd.setCursor(0,3);
        lcd.print("PRESS BUTTON ");
        lcd.print((ButtonNo+1)/2);
      }

      if(calibratecounter==2)
      {
        lcd.setCursor(0,3);
        lcd.print("                    ");
        calibratetime1=millis();
        while(digitalRead(ButtonNo+21)==1)
        {
        digitalWrite((ButtonNo+39),HIGH);
        }
        calibratetime2=millis();
        digitalWrite((ButtonNo+39),LOW);
        calibratecounter=0;
        calibratetime=(calibratetime2-calibratetime1)/hazne;
        EEPROM.put(2000+(((ButtonNo+1)/2)*4),calibratetime);
        lcd.setCursor(0,2);
        lcd.print("                    ");
        lcd.setCursor(0,2);
        lcd.print("DONE");
        lcd.setCursor(5,2);
        lcd.print(calibratetime,6);
      }
    }
}
/////////////////////////////////////////////////////////////-ARDUINOSETUP-///////////////////////////////////////////////
void setup()
{
  Serial.begin(9600); 

  //////////////////////////////////////////////SHIFTREGISTER///////////////////////////
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, INPUT);
  
  for (int x=0; x<17; x++)                      // sensor variables default values
{
  sensorcheckerup[x]=true;
  sensorcheckerdown[x]=true;
  sensorvalueup[x]=1;
  sensorvaluesaveup[x]=1;
  sensorvaluedown[x]=1;
  sensorvaluesavedown[x]=1;
}
  
  for (int x=22; x<40; x++)                     // sensor pins defining as input               
  {
  pinMode(x,INPUT);  
  }
  //Serial.println(EEPROM.put(1308,3035));       //    lastsaved
  
 
/*
  for(int x=1; x<11; x++)
  {
  Serial.println((2000+(x*4)));
  EEPROM.put((2000+(x*4)),100.0);  
  Serial.println(EEPROM.get((2000+(x*4)),motordelay[x]),10);
  }
  */
  for(int x=40; x<50; x++)
  {
  (pinMode(x,OUTPUT));      //works between 40-49
  }

  lcd.begin(20, 4);
  lcd.clear();
  

/////////////////////////////////////////////////////////////-SDCARD-//////////////////////////////////////////////////////
 // Open serial communications and wait for port to open:
Serial.print("Initializing SD card...");

  if (!SD.begin(4)) 
  {
    Serial.println("initialization failed!");
    lcd.clear();
    lcd.print("      ERROR!!!");
    lcd.setCursor(0,1);
    lcd.print("Please Insert ");
    lcd.setCursor(0,2);
    lcd.print("SD Card end ");
    lcd.setCursor(0,3);
    lcd.print("Restart Machine");
    for(;;);
  }
  Serial.println("initialization done.");

    if(!SD.exists("README.txt"))
    {
    dataFile = SD.open("README.txt", FILE_WRITE);
    if (dataFile) 
     {
       Serial.println("Writing to README.txt...");
        dataFile.println("To open SALES file in MS OFFICE 2010 open an Empty Excel File -> Data -> From Text -> Select Your SALES Folder -> Next -> Choose Comma and Next -> Finish -> OK OR search from Google how can you export .csv files to excel");
       // close the file:
       dataFile.close();
      }
   
      else 
    {
      // if the file didn't open, print an error:
      Serial.println("error opening README.txt");
      }
   }
   /*
  SD.remove("SALES.csv");
  if(!SD.exists("SALES.csv"))
  {
    Serial.println("SALES.csv deleted");
  }
  else
  {
    Serial.println("SALES.csv not deleted");
  }
  EEPROM.put(1304,0);
  EEPROM.put(1308,3001);                 
  EEPROM.put(1312,3000); 
  Serial.println(EEPROM.get(1304,cocktailcounter));
  Serial.println(EEPROM.get(1308,lastsaved)); 
  Serial.println(EEPROM.get(1312,counter)); 
  Serial.println(); 
*/
  
  Time();
  stringtime="";
  stringtime2="";
  stringtime2= String(hour()) + ":" + String(minute()) + ":" + String(second());
  stringtime=String(day()) + "-" + String(month()) + "-" +  String(year());;
  
  Serial.println(stringtime2);
  Serial.println(stringtime);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(stringtime2);
  lcd.setCursor(10,0);
  lcd.print(stringtime);
  Serial.print("\nMACHINE ID:  ");
  Serial.println(MACHINE_ID);
  lcd.setCursor(0,1);
  lcd.print("ID:");
  lcd.print(MACHINE_ID);
  Serial.print("MAC address: ");
  snprintf(macstr, 18, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Serial.println(macstr);
  lcd.setCursor(0,2);
  lcd.print("MAC");
  lcd.print(macstr);
  delay(1000);
  getIP();
  defaultscreen();

  Serial.println(EEPROM.read(4000));             // if it is equal 1 function will go to upload mode
 /* 
  download();                                  //download DELAY times form azure
  end_request();
  download();
  end_request();
  delay(5000);                        // without delay can not connect to azure at setup step moreover it shows IP on display

    downloadbutton();
    read_integerbutton();
    end_request();
    ButtonNo=0;
   for (int y=1; y<11; y++ )
   {
    ButtonNo++;
    Serial.println();
    Serial.println(y);
    EEPROM.get((y*4)+1256,CocktailNo);
    Serial.println();
    Serial.println((y*4)+1256);
    Serial.println(CocktailNo);
    download();
    read_integer();
    end_request();
   }
*/
/////////////////////////////////////////////////////////////-RESET-/////////////////////////////////////////////////////////////
if(EEPROM.read(4000)==1)
  {
    Serial.println("Going to upload mode");
    upload();
    EEPROM.write(4000,0);
  }
}
      
//////////////////////////////////////////////////////////////-ARDUINOLOOP-/////////////////////////////////////////////////
void loop()
{  
  
//////////////////////////////////////////////////////////////-SDCARD TO AZURE-/////////////////////////////////////
/*
if(hour()==12 && minute()==30 && second()<5 )
{ 
  getIP();
  connectToServer();
  wait_response();
  read_response();
  end_request();
  upload();
}
*/

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
if(Time2checker)                             //if reservoir empty while cocktail is trying to get, shows lcd screen error. it provides to deleting error and returning default screen 
{
  if(millis()>Time2+5000)
  {
    defaultscreen();
    Time2checker=false;
  }
}
//////////////////////////////////////////////////////////////-SENSOR1-////////////////////////////////////////////////

sensorvalueup[0]=digitalRead(23);
sensorvaluedown[0]=digitalRead(22);
if (sensorcheckerup[0] || sensorcheckerdown[0] )
{
  if(sensorvalueup[0] < sensorvaluedown[0])
  {
    sensorcheckerdown[0]=false;
  }
}

if ((sensorvaluesaveup[0] != sensorvalueup[0]) || sensorcheckerup[0])
{
if (sensorvalueup[0] == 0 && displaylocker)
   {
    Serial.println("FULL");
    sensorvaluesaveup[0] = sensorvalueup[0]; 
    sensorcheckerup[0] = false;
    pumpwork = true;
      defaultscreen2();      
      lcd.setCursor(1,0);
      lcd.print(" ");
      lcd.setCursor(1,0);
      lcd.print("F");
   }
if (sensorvalueup[0] == 1 && displaylocker)
   {
    Serial.println("MEDIUMup");
    sensorvaluesaveup[0] = sensorvalueup[0];
    sensorcheckerup[0] = false;
    pumpwork = true;
      defaultscreen2();
      lcd.setCursor(1,0);
      lcd.print(" ");
      lcd.setCursor(1,0);
      lcd.print("M");
   }
}
if (sensorvaluesavedown[0] != sensorvaluedown[0] || sensorcheckerdown[0]) 
{
if (sensorvaluedown[0] == 0 && displaylocker)
   {
    Serial.println("EMPTY");
    sensorvaluesavedown[0] = sensorvaluedown[0]; 
    sensorcheckerdown[0] = false;
    pumpwork = false;
      defaultscreen2();
      lcd.setCursor(1,0);
      lcd.print(" ");
      lcd.setCursor(1,0);
      lcd.print("E");
   }
if (sensorvaluedown[0] == 1 && displaylocker)
   {
    Serial.println("MEDIUMdown");
    sensorvaluesavedown[0] = sensorvaluedown[0];
    sensorcheckerdown[0] = false;
    pumpwork = true;
      defaultscreen2();
      lcd.setCursor(1,0);
      lcd.print(" ");
      lcd.setCursor(1,0);
      lcd.print("M");
   }
}
//////////////////////////////////////////////////////////////-SENSOR2-////////////////////////////////////////////////
sensorvalueup[1]=digitalRead(25);
sensorvaluedown[1]=digitalRead(24);
if (sensorcheckerup[1] || sensorcheckerdown[1] )
{
  if(sensorvalueup[1] < sensorvaluedown[1])
  {
    sensorcheckerdown[1]=false;
  }
}

if ((sensorvaluesaveup[1] != sensorvalueup[1]) || sensorcheckerup[1])
{
if (sensorvalueup[1] == 0 && displaylocker)
   {
    Serial.println("FULL2");
    sensorvaluesaveup[1] = sensorvalueup[1]; 
    sensorcheckerup[1] = false;
    pumpwork = true;
      defaultscreen2();      
      lcd.setCursor(1,1);              //lcd.setCursor(1,1);          default value
      lcd.print(" ");
      lcd.setCursor(1,1);              //lcd.setCursor(1,1);          default value
      lcd.print("F");
   }
if (sensorvalueup[1] == 1 && displaylocker)
   {
    Serial.println("MEDIUMup2");
    sensorvaluesaveup[1] = sensorvalueup[1];
    sensorcheckerup[1] = false;
    pumpwork = true;
      defaultscreen2();
      lcd.setCursor(1,1);
      lcd.print(" ");
      lcd.setCursor(1,1);
      lcd.print("M");
   }
}
if (sensorvaluesavedown[1] != sensorvaluedown[1] || sensorcheckerdown[1]) 
{
if (sensorvaluedown[1] == 0 && displaylocker)
   {
    Serial.println("EMPTY2");
    sensorvaluesavedown[1] = sensorvaluedown[1]; 
    sensorcheckerdown[1] = false;
    pumpwork = false;
      defaultscreen2();
      lcd.setCursor(1,1);
      lcd.print(" ");
      lcd.setCursor(1,1);
      lcd.print("E");
   }
if (sensorvaluedown[1] == 1 && displaylocker)
   {
    Serial.println("MEDIUMdown2");
    sensorvaluesavedown[1] = sensorvaluedown[1];
    sensorcheckerdown[1] = false;
    pumpwork = true;
      defaultscreen2();
      lcd.setCursor(1,1);
      lcd.print(" ");
      lcd.setCursor(1,1);
      lcd.print("M");
   }
}

//////////////////////////////////////////////////////////////////-SHIFTREGISTER-/////////////////////////////////////////////////////////
  digitalWrite(latchPin,1);                                        //Pulse the latch pin set it to 1 to collect parallel data
  delayMicroseconds(20);                                           //set it to 1 to collect parallel data, wait  
  digitalWrite(latchPin,0);                                        //set it to 0 to transmit data serially
  switchVar1 = shiftIn(dataPin, clockPin);                         //while the shift register is in serial mode collect each shift register into a byte the register attached to the chip comes in first 
  switchVar2 = shiftIn(dataPin, clockPin);
//  switchVar3 = shiftIn(dataPin, clockPin);
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

switch (switchVar1)
{
  case 1:
  ButtonNo=1;
  button(ButtonNo);
  break;
  case 2:
  ButtonNo=2;
  button(ButtonNo);
  break;
  case 4:
  ButtonNo=3;
  button(ButtonNo);
  break;
  case 8:
  ButtonNo=4;
  button(ButtonNo);
  break;
  case 16:
  ButtonNo=5;
  button(ButtonNo);
  break;
  case 32:
  ButtonNo=6;
  button(ButtonNo);
  break;
  case 64:
  ButtonNo=7;
  button(ButtonNo);
  break;
  case 128:
  ButtonNo=8;
  button(ButtonNo);
  break;
}

switch (switchVar2)
{
  case 1:
  ButtonNo=9;
  button(ButtonNo);
  break;
  case 2:
  ButtonNo=10;
  button(ButtonNo);
  break;  
  case 4:
  ButtonNo=11;
  Serial.print("BUTTON NO ");
  Serial.println(ButtonNo);
 // button(ButtonNo);
  break;
  case 8:
  ButtonNo=12;
  Serial.print("BUTTON NO ");
  Serial.println(ButtonNo);
 // button(ButtonNo);
  break;
  case 16:
  ButtonNo=13;
  Serial.print("BUTTON NO ");
  Serial.println(ButtonNo);
//  button(ButtonNo);
  break;
  case 32:
  ButtonNo=14;
  Serial.print("BUTTON NO ");
  Serial.println(ButtonNo);
 // button(ButtonNo);
  break;
  case 64:
  ButtonNo=15;
  Serial.print("BUTTON NO ");
  Serial.println(ButtonNo);
 // button(ButtonNo);
  break;
  case 128:
  ButtonNo=16;
  Serial.print("BUTTON NO ");
  Serial.println(ButtonNo);
//  button(ButtonNo);
  break;

}

//////////////////////////////////////////////////////////////////-DOWNLOAD-////////////////////////////////////////////////////
/*
  buttonStateDownload = digitalRead(buttonDownload3);              // read the pushbutton input pin:

  if (buttonStateDownload != lastButtonStateDownload)         // compare the buttonState to its previous state
  {
    // if the state has changed, increment the counter
    if (buttonStateDownload == HIGH)
    {
      if(mode==false)
      {
      getIP();                         
      CocktailNo=0;                       // for creating bridge to azure, try to get undefined value
      lcd.clear();                       // if the current state is HIGH then the lcd clear
      lcd.setCursor(0,0);
      lcd.print("Download Mode ON");
      buttonPushCounterDownload++;
      Serial.print("\nDownload on");
    download();                                  //download DELAY times form azure
    end_request();
    download();
    end_request();
    delay(5000);                        // without delay can not connect to azure at setup step moreover it shows IP on display

    downloadbutton();
    read_integerbutton();
    end_request();
    ButtonNo=0;
   for (int y=1; y<11; y++ )
   {
    ButtonNo++;
    Serial.println();
    Serial.println(y);
    EEPROM.get((y*4)+1256,CocktailNo);
    Serial.println();
    Serial.println((y*4)+1256);
    Serial.println(CocktailNo);
    download();
    read_integer();
    end_request();
   }
      }
      else
      {
      Serial.println("You can not upload when calibration mode on");
      lcd.setCursor(0,1);
      lcd.print("                    ");
      lcd.setCursor(0,2);
      lcd.print("                    ");
      lcd.setCursor(0,3);
      lcd.print("                    ");
      lcd.setCursor(0,1);
      lcd.print("You can not download");
      lcd.setCursor(0,2);
      lcd.print("Change your mode");
      }
    }
    else
    { /*
      Serial.println();
      Serial.println("Ready");
      Serial.println();
      lcd.setCursor(0,3);
      lcd.print("                   ");
      lcd.setCursor(0,3);
      lcd.print("Ready");
      */
      /*
      Time2=millis();
      Time2checker= true;
    }
  
    delay(50);                                                // Delay a little bit to avoid bouncing
  lastButtonStateDownload = buttonStateDownload;              // save the current state as the last state for next time through the loop
  }
  */
//////////////////////////////////////////////////////////////////-UPLOAD-////////////////////////////////////////////////////
/*
  buttonStateUpload = digitalRead(buttonUpload2);              // read the pushbutton input pin:

  if (buttonStateUpload != lastButtonStateUpload)         // compare the buttonState to its previous state
  {
    // if the state has changed, increment the counter
    if (buttonStateUpload == HIGH)
    {
     if (mode==false)
     {
      Serial.print("Cocktailcounter=");                                      //this part will not exist at main version. just for trial version
    Serial.println(EEPROM.get(1304,cocktailcounter));
    Serial.print("lastsaved=");
    Serial.println(EEPROM.get(1308,lastsaved));
    Serial.print("Counter=");
    Serial.println(EEPROM.get(1312,counter));
      if(counter!=lastsaved)
      {
    getIP();
    connectToServer();
    wait_response();
    read_response();
    end_request();
    upload();
      }
      else
      {
    Serial.println("Not recorded any sale until the last update");
    lcd.clear();
    lcd.print("Not recorded");
    lcd.setCursor(0,1);
    lcd.print("any sale until");
    lcd.setCursor(0,2);
    lcd.print("the last update");
    Time2=millis();                    // turns default screen after 5 second
    Time2checker= true;                // turns default screen after 5 second
    return;
    //return loop();
      }
     }
     else
     {
      Serial.println("You can not upload when calibration mode on");
      lcd.setCursor(0,1);
      lcd.print("                    ");
      lcd.setCursor(0,2);
      lcd.print("                    ");
      lcd.setCursor(0,3);
      lcd.print("                    ");
      lcd.setCursor(0,1);
      lcd.print("You can not upload");
      lcd.setCursor(0,2);
      lcd.print("Change your mode");
     }
   }
    delay(50);                                                // Delay a little bit to avoid bouncing
  lastButtonStateUpload = buttonStateUpload;              // save the current state as the last state for next time through the loop 
  }

  //////////////////////////////////////////////////////////////////-MODE-////////////////////////////////////////////////////

  buttonStateMode = digitalRead(buttonMode8);              // read the pushbutton input pin:

  if (buttonStateMode != lastButtonStateMode)         // compare the buttonState to its previous state
  {
    // if the state has changed, increment the counter
    if (buttonStateMode == HIGH)
    {
      if(mode)
      {
        mode=false;
        Serial.println("Mode=False");
        lcd.clear();
        lcd.print("Calibration Mode OFF");
        Time2=millis();
        Time2checker= true;
        displaylocker=true;
        Time2=millis();
      Time2checker= true;
      }
      else
      {
        mode=true;
        Serial.println("Mode=True");
        lcd.clear();
        lcd.print("CALIBRATION MODE ON");
        displaylocker=false;
      }
   }
    delay(50);                                                // Delay a little bit to avoid bouncing
  lastButtonStateMode = buttonStateMode;              // save the current state as the last state for next time through the loop 
  }
  */
//////////////////////////////////////////////////////////////////-TIMEINTERVAL-////////////////////////////////////////////////
if (displaylocker)
{
if (millis() - lastAttemptTime > requestInterval) 
  {
    Serial.println("\n\nTimeinterval-1...");                   // if you're not connected, and requestInterval has passed since. Your last connection, then attempt to connect again:
    Serial.println(lastAttemptTime);
    Serial.println(millis());
   // connectToServer();
   // wait_response(); beware it has return upload code
   // read_response();
   // end_request();
    defaultscreen();
    delay(1000);                                               // not important just to see led is working
    Serial.println("Ready");
  }
}
}
//////////////////////////////////////////////////////////////-SHIFTREGISTER-/////////////////////////////////////////////////////////////////////
byte shiftIn(int myDataPin, int myClockPin) 
{ 
  int i;
  int temp = 0;
  int pinState;
  byte myDataIn = 0;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, INPUT);
  for (i=7; i>=0; i--)
  {
    digitalWrite(myClockPin, 0);
    delayMicroseconds(20);
    temp = digitalRead(myDataPin);
    if (temp) 
    {
      pinState = 1;
      myDataIn = myDataIn | (1 << i);
    }
    else 
    {
      pinState = 0;
    }
    digitalWrite(myClockPin, 1);

  }
  return myDataIn;
}
