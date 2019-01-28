void weathercheck() {
  Serial.println("In weathercheck");
  const size_t bufferSize = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + 410;
  DynamicJsonBuffer jsonBuffer(bufferSize);  
  String payload;
  // Check weather symbol
  HTTPClient http;

  char httpaddr[100];
  strcpy (httpaddr, "http://192.168.1.190:8123/api/states/sensor.weather_symbol?api_password=");
  strcat (httpaddr, hasspass);  // Add password from file
  
  http.begin(httpaddr);  //Specify request destination

  int httpCode = http.GET();                                                                  //Send the request
  if (httpCode > 0) { //Check the returning code
        payload = http.getString();   //Get the request response payload
        //Serial.println(payload);                     //Print the response payload
  }
  http.end();   //Close connection 

  JsonObject& root = jsonBuffer.parseObject(payload);
  JsonObject& attributes = root["attributes"];
  const char* state = root["state"]; // "4"
  Serial.println(state);
}
