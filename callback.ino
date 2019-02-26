void callback(char* topic, byte* payload, unsigned int length) {
  String stringPayload = "";
  const int offset = 1;   // Central European Time

  Serial.print("Message arrived with topic ");
  Serial.println(topic);
  Serial.println("Message: ");
  
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
    stringPayload += (char)payload[i];
  }
  Serial.println();

  // Timestamp
  if (strcmp(topic,mqtt_time_topic)==0) {
    stringPayload = stringPayload.substring(0,10);  // Convert from timestamp in millis to ts i seconds
    
    t = stringPayload.toInt();
    setTime(t); 
    adjustTime(offset * SECS_PER_HOUR);

    Serial.print("Got time via Mqtt: ");
    String totalTime;
    if (minute()<10) {
      //Serial.println("Less than 10");
      String zeromin = "0";     // Add trailing zero
      zeromin.concat(String(minute()));
      totalTime = String(hour()) + zeromin;      
    }
    else {
      totalTime = String(hour()) + String(minute());  
    }
    Serial.println(totalTime);
    display.showNumberDecEx(totalTime.toInt(), 0b01000000, true, 4, 0);

  }
  // Temperature
  // https://arduinojson.org/v5/assistant/

  // The temp received here is wrong, do not use.
  if (strcmp(topic,mqtt_tempin_topic)==0) {
    JsonObject& root = jsonBuffer.parseObject(stringPayload);
    outdoortemp = root["temp"];
    outdoorhum = root["hum"];
    winddir = root["winddir"];
    wd = root["winddir"];
    //Serial.println(wd);
    
    /* H = winddirection (0 = north, 4 = east, 8 = south 12 = west)
     north, northeast,east, southeast, south, southwest, west, sorthwest
     N NE E SE S SW W SW
     N NNO NO ONO Ö OSO SO SSO S SSV SV VSV V VNV NV NNV
    */
    Serial.print("winddir: ");
    Serial.println(winddirs[wd]);
    Serial.println(outdoorwind);
    Serial.println(outdoorhum);
    

    //Serial.print("Temp from mqtt: ");
    //Serial.println(outdoortemp);
    //Serial.print("Humidity from mqtt: ");
    //Serial.println(outdoorhum);
  }
  
  //indoorSensor
  if (strcmp(topic,mqtt_indoorsensor_topic)==0) {
    Serial.println(topic);
    JsonObject& root = jsonBuffer.parseObject(stringPayload);
    indoortemp = root["temp"];
    indoorhumidity = root["hum"];

    Serial.print("Indoor temp: ");
    Serial.println(indoortemp);
    Serial.print("Indoor humidity: ");    
    Serial.println(indoorhumidity);

    
  }

  
/*
 * const char* count = root["count"]; // "49"
const char* bat = root["bat"]; // "OK"
int tz = root["tz"]; // 2
const char* temp = root["temp"]; // "62.3"
const char* hum = root["hum"]; // "71"
long ts = root["ts"]; // 1546270985
const char* rain = root["rain"]; // "350d"
const char* wings = root["wings"]; // "0000"
const char* winddir = root["winddir"]; // "0008"
const char* winsp = root["winsp"]; // "0000"
const char* device = root["device"]; // "DKW2012"
const char* id = root["id"]; // "0022"
*/
}
