# Cloud-Communication-MKR1400
Uploading data to ThingSpeak Cloud using 3G network.

## Description ##
Writes value to a channel on ThingSpeak every 20 seconds. Captures underground signal strenght, measures current from the soil cell and no. of messages sent.  

**Hardware:** 
Arduino MKR GSM 1400
  
**!!! IMPORTANT - Modify the secrets.h file for this project with your network connection and ThingSpeak channel details. !!!**
  
Note:
  - Requires MKRGSM library.
  - Reqires GSM access (SIM card or credentials).
  
  ThingSpeak ( https://www.thingspeak.com ) is an analytic IoT platform service that allows you to aggregate, visualize, and 
  analyze live data streams in the cloud.
  
  For Live Thingspeak Channel update https://thingspeak.com/channels/865820
