void readhtu() {
  Serial.println("Read HTU21D");

  htutemp=htudev.readTemperature();
  htuhum=htudev.readHumidity();

  //  Serial.println(htutemp);
  //  Serial.println(htuhum);

  // Convert to one decimal
  sprintf(chtutemp, "%d.%01d", (int)htutemp, (int)(htutemp*10)%10);
  //Serial.println(chtutemp);
  sprintf(chtuhum, "%d", (int)htuhum);
  Serial.println(chtutemp);
  Serial.println(chtuhum);

  //Serial.println("Done");
}
