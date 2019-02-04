void readhtu() {
  htutemp=htudev.readTemperature();
  htuhum=htudev.readHumidity();

  //  Serial.println(htutemp);
  //  Serial.println(htuhum);

  // Convert to one decimal
  sprintf(chtutemp, "%d.%01d", (int)htutemp, (int)(htutemp*10)%10);
  //Serial.println(chtutemp);
  sprintf(chtuhum, "%d.%01d", (int)htuhum, (int)(htuhum*10)%10);
  //Serial.println(chtuhum);
  
}
