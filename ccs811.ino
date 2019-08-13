// Ref: https://learn.sparkfun.com/tutorials/ccs811-air-quality-breakout-hookup-guide


void readCCS() {
  if(ccs.available()){
    Serial.println("Read CCS811");
    ccs.setEnvironmentalData(htuhum, htutemp);

    //float temp = ccs.calculateTemperature();
    if(!ccs.readData()){
      eCO2=ccs.geteCO2();
      TVOC=ccs.getTVOC();
      Serial.print("CO2: ");
      Serial.print(eCO2);
      Serial.print("ppm, TVOC: ");
      Serial.print(TVOC);
      Serial.print("ppb   Temp:");
      Serial.println(htutemp);
    }
    else{
      Serial.println("ERROR!");
      while(1);
    }
  }
}
/*
/* From readhtu: 
 * htutemp=htudev.readTemperature();
 * htuhum=htudev.readHumidity();
 */
/*
    myCCS811.setEnvironmentalData(htuhum, htutemp);
    Serial.println("Environmental data applied!");
    myCCS811.readAlgorithmResults(); //Dump a reading and wait
    delay(1000);
    //Print data points
    for( int i = 0; i < 10; i++)
    {
        if (myCCS811.dataAvailable())
        {
            //Calling readAlgorithmResults() function updates the global tVOC and CO2 variables
            myCCS811.readAlgorithmResults();

            Serial.print("CO2[");
            Serial.print(myCCS811.getCO2());
            Serial.print("] tVOC[");
            Serial.print(myCCS811.getTVOC());
            Serial.print("] millis[");
            Serial.print(millis());
            Serial.print("]");
            Serial.println();
        }
        else if (myCCS811.checkForStatusError())
        {
            //If the CCS811 found an internal error, print it.
            printSensorError();
        }
        //delay(1000); //Wait for next reading
    }
}
//printDriverError decodes the CCS811Core::status type and prints the
//type of error to the serial terminal.
//
//Save the return value of any function of type CCS811Core::status, then pass
//to this function to see what the output was.
void printDriverError( CCS811Core::status errorCode )
{
    switch( errorCode )
    {
    case CCS811Core::SENSOR_SUCCESS:
        Serial.print("SUCCESS");
        break;
    case CCS811Core::SENSOR_ID_ERROR:
        Serial.print("ID_ERROR");
        break;
    case CCS811Core::SENSOR_I2C_ERROR:
        Serial.print("I2C_ERROR");
        break;
    case CCS811Core::SENSOR_INTERNAL_ERROR:
        Serial.print("INTERNAL_ERROR");
        break;
    case CCS811Core::SENSOR_GENERIC_ERROR:
        Serial.print("GENERIC_ERROR");
        break;
    default:
        Serial.print("Unspecified error.");
    }
}

//printSensorError gets, clears, then prints the errors
//saved within the error register.
void printSensorError()
{
    uint8_t error = myCCS811.getErrorRegister();

    if( error == 0xFF )//comm error
    {
        Serial.println("Failed to get ERROR_ID register.");
    }
    else
    {
        Serial.print("Error: ");
        if (error & 1 << 5) Serial.print("HeaterSupply");
        if (error & 1 << 4) Serial.print("HeaterFault");
        if (error & 1 << 3) Serial.print("MaxResistance");
        if (error & 1 << 2) Serial.print("MeasModeInvalid");
        if (error & 1 << 1) Serial.print("ReadRegInvalid");
        if (error & 1 << 0) Serial.print("MsgInvalid");
        Serial.println();
    }
}
*/
