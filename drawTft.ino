void drawTft() { 
  tft.fillScreen(ST7735_BLACK);

  tft.drawRect( 0, 0, tft.width(), tft.height(), ST7735_WHITE );
  
  tft.setCursor(7,5); // x,y    
  tft.setTextSize(2);
  tft.setTextColor(ST7735_YELLOW);
  tft.print("Ute");

  int humlen = strlen(outdoorhum);
  Serial.print("humlen: ");
  Serial.println(humlen);
  //char coutdoorhum[humlen];
  char coutdoorhum[3];
  // strncpy(dst, src, dst_size)
  //strncpy(coutdoorhum, outdoorhum, 2);
  strcpy(coutdoorhum, outdoorhum);
  strcat(coutdoorhum, "% ");
  Serial.println(coutdoorhum);
  int len = strlen(coutdoorhum);
  Serial.println(len);

  //strcat(outdoorhumWind, outdoorwind);

  tft.setCursor(65,5); // x,y
  //tft.setFont(&FreeMonoBoldOblique9pt7b);
  tft.print(coutdoorhum);

  tft.setTextSize(1);
  tft.setTextColor(ST7735_WHITE);
  tft.setCursor(10,52); // x,y
  tft.setFont(&FreeSansBold24pt7b);
  tft.print(outdoortemp);

  tft.setTextColor(ST7735_GREEN);
  tft.setFont();  // Standard font
  tft.setTextSize(1);
  tft.setFont();  // Standard font

  char coutdoorwind[15];
  //strcpy(coutdoorwind, outdoorwind);

//  itoa(wd, outdoorwind, 10 );  
  //strcat(coutdoorwind, "m/s ");    String test;

  //strcat( coutdoorwind, winddirs[wd].c_str() );

  tft.setTextSize(3);
  tft.setCursor(7,67); // x,y
  tft.print(outdoorwind);

  int16_t  x1, y1;
  uint16_t w, h;
  tft.getTextBounds(String(outdoorwind), 7, 67, &x1, &y1, &w, &h);
  // The wind level written on the tft is w pixels wide. Use this value 
  // to place the "m/s"-symbol.
  //Serial.print("windwidth: ");
  //Serial.println(w);
  // "m/s" symbol
  tft.drawBitmap(7+w+5,67+4, mssymbol, 33,21, ST7735_WHITE );
  tft.setCursor(7+w+5+40,67); // Place winddir after m/s-symbol
  tft.print(winddirs[wd].c_str());

  tft.drawLine(0, 100, tft.width(), 100, ST7735_WHITE);

  tft.setCursor(4,105); // x,y    
  tft.setTextSize(2);
  tft.setTextColor(ST7735_YELLOW);
  tft.print("Inne");
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(3);
  tft.setCursor(10,130); // x,y    
  tft.print(chtutemp);
  Serial.print("indoortemp: ");  
  Serial.println(indoortemp);

  tft.setTextSize(2);
  tft.setCursor(85,105); // x,y    
  char indoorhumpercent[10];
  strcpy(indoorhumpercent, chtuhum);
  strcat(indoorhumpercent, "%");
  
  tft.print(int(indoorhumpercent));
  Serial.print("indoorhumpercent: ");  
  Serial.println(indoorhumpercent);

}
