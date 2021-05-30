# NaverCloud_esp32
Let's make a weather data center using NAVER CLOUD server and esp32 board.

# materials
- esp32 or esp8266
- Hosting server and domain name;
- php script to insert data into SQL and display it on screen
- SQL DB to store data values

# The overall conceptual diagram is as follows.
![ESP32-ESP8266-Gauge-weather-station-project-overview](https://user-images.githubusercontent.com/32832715/120095548-8eff0c00-c161-11eb-9f4c-c899b9f02b3c.png)

1. After reading the sensor data, esp32 makes an HTTP POST to the domain through the router.
2. The server has a php script that can save data to a SQL database.
3. The php script displays a web page with information.
4. Access your own domain name to visualize your readings from anywhere.

# 1. Prepare NAVER CLOUD SERVER
A public IP is required.
Please refer to this article and follow along
https://blog.naver.com/wizzle1/222359884972

# 2. Prepare MariaDB (MySQL doesn't matter)
- Create a user and password in MariaDB. Then connect to phpmyadmin and create a database.
- Let's make a new database "example_esp_data". The database name and sort method can be changed as desired.
![2](https://user-images.githubusercontent.com/32832715/120095616-d4233e00-c161-11eb-92ab-85aa44e3a60a.png)

## Paste the code in the SQL query field and create it.
```
CREATE TABLE Sensor (
     id INT(6) UNSIGNED AUTO_INCREMENT PRIMARY KEY,
     value1 VARCHAR(10),
     value2 VARCHAR(10),
     value3 VARCHAR(10),
     reading_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
)
```
![3](https://user-images.githubusercontent.com/32832715/120095634-eb622b80-c161-11eb-93a5-d82534f2565b.png)
## ▼Click Run to create the database.
![555](https://user-images.githubusercontent.com/32832715/120095993-0a61bd00-c164-11eb-9ba0-94ddf1a23635.png)

# 3. Upload HTTP POST php script
Upload the php script to the server.

## ▼ Refer to NAVER CLOUD SFTP Connection for how to connect to the server
https://www.ncloud.com/support/faq/all/2494
