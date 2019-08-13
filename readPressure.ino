void readPressure() {
  Serial.print("Read air pressure: ");

const size_t capacity = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(6) + 300;
DynamicJsonBuffer jsonBuffer(capacity);

  HTTPClient http;
  // All states: http://192.168.1.190:8123/api/states?api_password=

  char httpaddr[100];
  strcpy (httpaddr, "http://192.168.1.190:8123/api/states/sensor.satenas_lufttryck?api_password=");
  strcat (httpaddr, hasspass);  // Add password from file
       
  http.begin(httpaddr);
  int httpCode = http.GET();
  String payload = http.getString();
  Serial.println(payload);
  http.end();

  JsonObject& rootT = jsonBuffer.parseObject(payload);
  airpressure = rootT["state"]; 
  const char* wind_last_updated = rootT["last_updated"]; // "2019-01-01T08:21:03.397305+00:00"  
  Serial.print("airpressure: ");
  Serial.println(airpressure);
}

