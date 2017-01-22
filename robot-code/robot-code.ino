#include <SPI.h>
#include <WiFi.h>
#include <Servo.h>//libraries

Servo motorOne;  //left 
Servo motorTwo;  //right
char ssid[] = "ConUHacks2017";      //  your network SSID (name)
char pass[] = "HackConcordia";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
char c;

int status = WL_IDLE_STATUS;

// Initialize the Wifi client library
WiFiClient client;

// server address:
char server[] = "www.swal.xyz";
//IPAddress server(64,131,82,241);

unsigned long lastConnectionTime = 0;            // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 10L * 1000L; // delay between updates, in milliseconds

void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  motorOne.attach(5);
  motorTwo.attach(3);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the presence of the shield:
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue:
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv != "1.1.0") {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  // you're connected now, so print out the status:
  printWifiStatus();
}

void loop() {
  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
      
  }
  
  while (client.available()) {
    c = client.read();
    
  }
}

// this method makes a HTTP connection to the server:
void httpRequest() {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there's a successful connection:
  if (client.connect(server, 80)) {
    Serial.println("connecting...");
    // send the HTTP PUT request:
    client.println("GET /keyLog.txt HTTP/1.1");
    client.println("Host: www.swal.xyz");
    Serial.println(c);

    if (c == 'd'){//full right
    motorOne.write(1700);//if controls are inverted replace with 1300
    motorTwo.write(1700);
    }
    else if (c == 'a'){//full left
      motorOne.write(1300);//if controls are inverted replace with 1700
      motorTwo.write(1300);
    }
    
    else if (c == 'w'){// full forwards
      motorOne.write(2000);//if controls are inverted switch values
      motorTwo.write(1000);
    }
    else if (c == 's'){// full back
      motorOne.write(1300);//if controls are inverted switch values
      motorTwo.write(1700);
    }
    else if (c == 'e'){//stop
      motorOne.write(1500);
      motorTwo.write(1500);
    }
    
    //client.println("User-Agent: ArduinoWiFi/1.1");
    //client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}


