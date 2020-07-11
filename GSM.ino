/*
Writes a value to a channel on ThingSpeak every 20 seconds.

Hardware: Arduino MKR GSM 1400
  
!!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!
  
Note:
  - Requires MKRGSM library.
  - Reqires GSM access (SIM card or credentials).
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud.
  
*/


#include "ThingSpeak.h"
#include <MKRGSM.h>
#include "secrets.h"


const char GPRS_APN[]      = SECRET_GPRS_APN;
const char GPRS_LOGIN[]    = SECRET_GPRS_LOGIN;
const char GPRS_PASSWORD[] = SECRET_GPRS_PASS;

GSMClient client;
GPRS gprs;
GSM gsmAccess;
GSMScanner scannerNetworks;

String apiKey = "0AGCPVZ34ZLRKRV8";
unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;
const char* server = "api.thingspeak.com";
int duration=15;//delay between each data measurement and uploading

float voltage=0;
int h=0;


void setup() {
  Serial.begin(115200);  //Initialize serial port
  pinMode(05, OUTPUT);
  digitalWrite(05, LOW);
  Serial.println("Starting Arduino web client.");
  boolean connected = false;
 
  while (!connected) {
    if ((gsmAccess.begin() == GSM_READY) &&
      (gprs.attachGPRS(GPRS_APN, GPRS_LOGIN, GPRS_PASSWORD) == GPRS_READY)) {
      connected = true;
      //delay(1000);
    } else {
      Serial.println("Not connected");
      //delay(1000);
    }
  }

    Serial.println("connected");
    // wait 10 seconds for connection:
    delay(1000);
    ThingSpeak.begin(client);  // Initialize ThingSpeak 
}

void loop() 

{
    Serial.println("New Msg");
    float A= analogRead(A5);
    float v1 = A * (3.3/ 1023.0)*1000;
    //Serial.println("v1");
    //Serial.println(v1);

    float B= analogRead(A1);
    float v2 = B * (3.3/ 1023.0)*1000;
    //Serial.println("v2");
    //Serial.println(v2);
    
    float d_v=v1-v2;
    //Serial.println("d_v");
    //Serial.println(d_v);
    
 
    float I=d_v/10.1;
    //Serial.println("I");
    //Serial.println(I);
    
    // Measure Signal Strength
    String d=scannerNetworks.getSignalStrength();

  h=h+1;
  // set the fields with the values
  ThingSpeak.setField(1, d);
  ThingSpeak.setField(2, h);
  ThingSpeak.setField(3, I);

  // write to the ThingSpeak channel
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
 if (h == 3) 
     {
      Serial.println("h");
      digitalWrite(05, HIGH);
      Serial.println("05 Pin High");
      delay(5000);
      } 
 
 Serial.println("Waiting for Next Message");
 int j=0;
  for (int i=0;i<=duration*10;i++)
  {
    float p= analogRead(A2);
    voltage = p * (3.3/ 1023.0);
    Serial.println("voltage");
    Serial.println(voltage);
    delay(100);

    if (h == 2 && voltage < 2.8) 
    {
      j=j+1;
      if (j>2)
      {
      Serial.println("j");
      digitalWrite(05, HIGH);
      Serial.println("05 Pin High");
      delay(5000);
      }
    }  
    else 
    {
    digitalWrite(05, LOW);
    }
  }
  // thingspeak needs minimum 15 sec delay between updates  
  
}
