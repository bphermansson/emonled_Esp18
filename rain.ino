void readRain() {
  Serial.print("Check rain sensor: ");

  const size_t bufferSizeT = JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(6) + 280;
  DynamicJsonBuffer jsonBufferT(bufferSize);

  HTTPClient http;

  char httpaddr[100];
  strcpy (httpaddr, "http://192.168.1.190:8123/api/states/binary_sensor.noderedrain?api_password=");
  strcat (httpaddr, hasspass);  // Add password from file
  
  http.begin(httpaddr);
  int httpCode = http.GET();
  String payload = http.getString();
  http.end();

  JsonObject& rootT = jsonBuffer.parseObject(payload);
  rain = rootT["state"]; 
  Serial.println(rain);
}
