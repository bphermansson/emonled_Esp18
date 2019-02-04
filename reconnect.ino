void mqttreconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(appname, MQTT_USERNAME, MQTT_PASSWORD)) {
      #ifdef DEBUG
        snprintf (msg, 150, "Connected to Mqtt broker as %s", appname);
        Serial.print("Publish message: ");
        Serial.println(msg);
        client.publish(mqtt_value_topic, msg);
        
      #endif
      client.subscribe(mqtt_tempin_topic);
      client.subscribe(mqtt_time_topic);
      int con = client.subscribe(mqtt_indoorsensor_topic);
      //Serial.println(con);  // 1 if connection is succesfull
      //client.subscribe(mqtt_ha_topic);
      #ifdef DEBUG
        Serial.print("Subscribed to: ");
        Serial.print(mqtt_tempin_topic);
        Serial.print(",  ");        
        Serial.println(mqtt_time_topic);
        Serial.println(mqtt_indoorsensor_topic);
        //Serial.println(mqtt_ha_topic);        
      #endif
      
      
    } else {
      Serial.print("Mqtt connection failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
