# NaverCloud_esp32
Let's make a weather data center using NAVER CLOUD server and esp32 board.

# materials
- esp32
- Hosting server and domain name;
- php script to insert data into SQL and display it on screen
- SQL DB to store data values

# The overall conceptual diagram is as follows.
![ESP32-ESP8266-Gauge-weather-station-project-overview](https://user-images.githubusercontent.com/32832715/120095548-8eff0c00-c161-11eb-9f4c-c899b9f02b3c.png)

1. After reading the sensor data, esp32 makes an HTTP POST to the domain through the router.
2. The server has a php script that can save data to a SQL database.
3. The php script displays a web page with information.
4. Access your own domain name to visualize your readings from anywhere.
