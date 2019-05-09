void drawTft() { 
  Serial.println("Draw TFT");

  tft.fillScreen(ILI9341_BLACK);

 // tft.drawRect( 0, 0, tft.width(), tft.height(), ILI9341_WHITE );

  Serial.println("Values on TFT");
  
  tft.setCursor(5,22); // x,y    bxh
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setFont(&FreeSans12pt7b);
  tft.print("Ute");
  
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setFont(&FreeSans24pt7b);
  //outdoortemp = "-24.5";

  // Check if temp is below zero
  long ltemp = atol( outdoortemp );
  Serial.println(ltemp);

  if (ltemp < 0) {
      Serial.println("Temp below zero");
      tft.setCursor(30,70); // x,y
  }
  else {
      tft.setCursor(53,70); // x,y
  }
  tft.print(outdoortemp);

  tft.setFont(&FreeSans12pt7b);
  tft.setTextSize(2);
  int humlen = strlen(outdoorhum);
  Serial.print("humlen: ");
  Serial.println(humlen);
  char coutdoorhum[3];
  strcpy(coutdoorhum, outdoorhum);
  strcat(coutdoorhum, "% ");
  Serial.println(coutdoorhum);
  tft.setCursor(85,175); // x,y
  //tft.print("H:");
  tft.print(coutdoorhum);

// Wind
  //tft.setTextColor(ILI9341_GREEN);
  //tft.setTextSize(1);
  tft.setCursor(30,124); // left,top
  //tft.setFont(&FreeSans24pt7b);
  //tft.print("W:");
  //outdoorwind=23;
  tft.print(outdoorwind);
  tft.print(" m/s ");
  
  //int16_t  x1, y1;
  //uint16_t w, h;
  //tft.getTextBounds(String(outdoorwind), 7, 67, &x1, &y1, &w, &h);
  // The wind level written on the tft is w pixels wide. Use this value 
  // to place the "m/s"-symbol.
  //Serial.print("windwidth: ");
  //Serial.println(w);
  // "m/s" symbolhttps://github.com/greiman/SdFat/blob/master/src/SdFat.h
  //tft.drawBitmap(7+w+5,67+4, mssymbol, 33,21, ILI9341_WHITE );
  //tft.drawBitmap(199,150, mssymbol, 33,21, ILI9341_WHITE );
  //tft.setCursor(7+w+5+40,67); // Place winddir below m/s-symbol
  //tft.setCursor(195,130); 
  tft.print(winddirs[wd].c_str());

  tft.drawLine(0, 200, tft.width(), 200, ILI9341_WHITE);

  tft.setFont(&FreeSans12pt7b);

  tft.setCursor(8,232); // x,y    
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.print("Inne");
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(3);
  tft.setCursor(75,263); // x,y    
  tft.print(chtutemp);
  Serial.print("indoortemp: ");  
  Serial.println(indoortemp);

  tft.setTextSize(2);
  tft.setCursor(85,315); // x,y    
  char indoorhumpercent[10];
  strcpy(indoorhumpercent, chtuhum);
  strcat(indoorhumpercent, "%");  
  tft.print(indoorhumpercent);
  Serial.print("indoorhumpercent: ");  
  Serial.println(indoorhumpercent);
  

}
void drawTftHor() { 
  Serial.println("Draw TFT horizontal");
  tft.setRotation(1);

  tft.fillScreen(ILI9341_BLACK);

//  tft.drawRect( 0, 0, tft.width(), tft.height(), ILI9341_WHITE );

  Serial.println("Values on TFT");
  
  tft.setCursor(7,17); // x,y    
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.setFont(&FreeSans12pt7b);
  tft.print("Ute");
  
  tft.setTextSize(2);
  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(55,80); // x,y
  tft.setFont(&FreeSans24pt7b);
  outdoortemp = "22.4";
  tft.print(outdoortemp);

  tft.setFont(&FreeSans12pt7b);
  tft.setTextSize(2);
  int humlen = strlen(outdoorhum);
  Serial.print("humlen: ");
  Serial.println(humlen);
  char coutdoorhum[3];
  strcpy(coutdoorhum, outdoorhum);
  strcat(coutdoorhum, "% ");
  Serial.println(coutdoorhum);
  tft.setCursor(205,150); // x,y
  tft.print(coutdoorhum);

// Wind
  tft.setTextColor(ILI9341_GREEN);
  tft.setFont(&FreeSans12pt7b);
  tft.setTextSize(2);
  tft.setCursor(10,150); // x,y
  tft.print(outdoorwind);
  tft.setTextSize(1);
  tft.print("m/s");
  

  int16_t  x1, y1;
  uint16_t w, h;
  tft.getTextBounds(String(outdoorwind), 7, 67, &x1, &y1, &w, &h);
  // The wind level written on the tft is w pixels wide. Use this value 
  // to place the "m/s"-symbol.
  //Serial.print("windwidth: ");
  //Serial.println(w);
  // "m/s" symbolhttps://github.com/greiman/SdFat/blob/master/src/SdFat.h
  //tft.drawBitmap(7+w+5,67+4, mssymbol, 33,21, ILI9341_WHITE );
  //tft.drawBitmap(210,130, mssymbol, 33,21, ILI9341_WHITE );
  //tft.setCursor(7+w+5+40,67); // Place winddir below m/s-symbol
  //tft.setCursor(235,120); 
  tft.setTextSize(2);
  tft.print(winddirs[wd].c_str());

  tft.drawLine(0, 200, tft.width(), 200, ILI9341_WHITE);

  tft.setFont(&FreeSans12pt7b);

/*
  tft.setCursor(8,174); // x,y    
  tft.setTextSize(1);
  tft.setTextColor(ILI9341_YELLOW);
  tft.print("Inne");
*/
  tft.setTextColor(ILI9341_GREEN);
  tft.setTextSize(2);
  tft.setCursor(60,223); // x,y    
  strcat(chtutemp, " ");  
  tft.print(chtutemp);
  Serial.print("indoortemp: ");  
  Serial.println(indoortemp);

  tft.setFont(&FreeSans18pt7b);
  tft.setTextSize(1);
  if (htuhum<40) {
      tft.setTextColor(ILI9341_RED);
  }
  else {
      tft.setTextColor(ILI9341_GREEN);
  }
  
  char indoorhumpercent[10];
  strcpy(indoorhumpercent, chtuhum);
  strcat(indoorhumpercent, "%");  
  tft.print(indoorhumpercent);
  Serial.print("indoorhumpercent: ");  
  Serial.println(indoorhumpercent);

}
