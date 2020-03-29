# Coronavirus_Tracker
## Arduino code that tracks the spread of the Coronavirus and displays it on an OLED display

![Coronavirus Tracker](/project.jpeg "Coronavirus Tracker")

### What does this do?
When run on an ESP8266 microcontroller, this code does the following:
1. Connects to the configured 2.4GHz WiFi network
2. Sends an HTTP GET request to two endpoints and retreives:
   * Updated Coronavirus data for the whole world
   * Updated Coronavirus data for a specific countrt
3. Parses the JSON response and extracts:
   * Number of cases
   * Number of deaths
4. Displays the extracted information on the OLED display
5. Sleeps for 10 minutes
6. Goto 2

### Data Source
The data displayed originates from two endpoints:
1. `https://corona.lmao.ninja/all` - returns a JSON object with updated Coronavirus data for the whole world
2. `https://corona.lmao.ninja/countries/COUNTRY_NAME` - returns a JSON object with updated Coronavirus data for the country name after the last slash

### Code Configuration
The following code changes need to be made prior to compiling and uploading to the ESP8266:
1. Line 34 - enter the required WiFi network name (the ESP8266 can connect only to 2.4GHz networks, not 5GHz ones)
2. Line 35 - enter the required WiFi network password
3. Line 37 - enter the required country name
4. Line 98 - enter the required country name

### Hardware Components
1. ESP8266 - a low-cost WiFi microchip, with a full TCP/IP stack and microcontroller capability. Basically, the brains of this project
2. SSD1306 - a monochrome 0.96" 128x64 IIC OLED graphic display

### Schematic
![Schematic](/Schematic_Coronavirus_Tracker.png "Schematic")


### Notes
1. Changing the sleep time requires updating the value passed to the delay function on line 105
2. Parsing a different parameter from the JSON response requires updating the name of the key in either line 60, 61, 73 or 74 (in order to see the possible keys, you can open the URL in your browser and review the response)
3. Replacing the provided endpoints with different ones requires updating the URL values in lines 37 and 38
