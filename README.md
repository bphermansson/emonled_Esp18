emonled_Esp18

This is a project for showing data on two displays. The first display is a four digit led which shows the time. It's a module based on the TM1637 IC. 
The second is a TFT based on ILI9341. This shows outdoor temp, humidity, wind speed and -direction. 
<br>
Data is fetched from a Home Assistant installation. The device also has local sensors for  temp, humidity and air quality. The temp and humidity is shown on the TFT, all values are published via MQTT. This can look like this:
<br>
```
emonled_Esp/values {"intemp":"25.9","inhumidity":"43","eCO2":426,"TVOC":3}
```

The values sent to the MQTT-broker are the temp and humidity read from the local sensor. We also see "eCO2" and TVOC, values for air quality. See the tables at https://www.element14.com/community/roadTestReviews/2771/l/sensirion-environmental-sensor-shield-review for more information. 

<br>
The device is based on a Wemos Mini D1 but can be built with other ESP8266-based cards too. 

![Alt text](IMG_20190509_124258.jpg?raw=true "emonled_Esp18")
