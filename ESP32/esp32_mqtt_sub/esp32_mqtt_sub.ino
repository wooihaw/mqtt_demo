// MQTT subscriber
#include <WiFi.h> // Includes the WiFi library to connect the ESP32 to a WiFi network
#include <PubSubClient.h> // Includes the PubSubClient library to enable MQTT communication

WiFiClient espClient; // Create a WiFiClient object
PubSubClient client(espClient); // Initialize the MQTT client with the WiFi client

// Declare and initialize the WiFi network credentials
const char* ssid     = "your ssid"; // WiFi network SSID
const char* password = "your password"; // WiFi network password

// MQTT server details
const char* mqtt_server = "test.mosquitto.org"; // MQTT broker URL
const int mqtt_port = 1883; // Default MQTT port

const char* sub_topic = "mytopic456"; // MQTT topic to subscribe to

// Callback function to handle incoming MQTT messages
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived: "); // Print a prefix to the serial monitor
  Serial.println(topic); // Print the topic of the received message
  
  // Loop through all bytes of the payload
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]); // Print each byte of the payload
  }
  Serial.println(); // Print a newline to the serial monitor
}

void setup() {
    Serial.begin(115200); // Start the serial communication with the baud rate of 115200
    delay(10);

    // We start by connecting to a WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password); // Connect to the WiFi network

    // Check the WiFi connection status
    while (WiFi.status() != WL_CONNECTED) {
        delay(500); // If not connected, wait for 0.5 seconds before checking again
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected"); // Confirm that the WiFi is connected
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP()); // Display the IP address assigned to ESP32

    // Set the MQTT server to connect to
    client.setServer(mqtt_server, mqtt_port);
    // Set the callback function to handle incoming MQTT messages
    client.setCallback(callback);
}

// Function to reconnect to the MQTT server if the connection is lost
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Create a random client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    // Try to connect to the MQTT server
    if(client.connect(clientId.c_str())) {
      Serial.println("connected");

      // Subscribe to the topic
      bool sub = client.subscribe(sub_topic);
      if (sub) {
        Serial.println("Subscribed"); // Confirm that subscription was successful
      } else {
        Serial.println("Not subscribed"); // Indicate that subscription failed
      }
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // If connection failed, wait for 5 seconds before retrying
      delay(5000);      
    }
  }
}

void loop() {
  // If the MQTT client is not connected, try to reconnect
  if (!client.connected()) {
    reconnect();
  }
  client.loop(); // Call the PubSubClient loop function to maintain connection and handle incoming messages

  // Dosomething else here
  // This is where you'd add code for the main functionality of your sketch
}