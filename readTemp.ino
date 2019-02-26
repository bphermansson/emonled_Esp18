void readTemp() {
  Serial.print("Read outdoor temp: ");

  const size_t bufferSizeT = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(6) + 280;
  DynamicJsonBuffer jsonBufferT(bufferSize);

  HTTPClient http;
  // All states: http://192.168.1.190:8123/api/states?api_password=

  char httpaddr[100];
  strcpy (httpaddr, "http://192.168.1.190:8123/api/states/sensor.satenas_lufttemperatur?api_password=");
  strcat (httpaddr, hasspass);  // Add password from file
  
  http.begin(httpaddr);
  int httpCode = http.GET();
  String payload = http.getString();
  //Serial.println(payload);
  http.end();

  JsonObject& rootT = jsonBuffer.parseObject(payload);
  outdoortemp = rootT["state"]; 
  const char* last_updated = rootT["last_updated"]; // "2019-01-01T08:21:03.397305+00:00"
  Serial.print("Read outdoortemp: ");  
  Serial.println(outdoortemp);
}
