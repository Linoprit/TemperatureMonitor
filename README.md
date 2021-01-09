# TemperatureMonitor

What it does:
Several slaves measure temperature with DS18B20 and send results to a master-station, via NRF24 modules. The master-station is connected to a Raspi, which hosts a database and a PHP-Server (LAMP-Config). With a browser, you can graphically see the temperature-profile of the last 24h. In the database every measurement is stored in 5 minute intervals.
