// MQTT publisher
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
const char* pub_topic = "mytopic123"; // MQTT topic to publish messages
long counter = 0; // A counter variable to publish

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

    // Generate a unique client ID
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    // Try to connect to MQTT server
    if(client.connect(clientId.c_str())) {
      Serial.println("connected"); // If connected, print a success message
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // If connection failed, wait for 5 seconds before retrying
      delay(5000);      
    }
}

void loop() {
  // Publish the counter value to the defined MQTT topic every 5 seconds
  client.publish(pub_topic, String(counter++).c_str());
  delay(5000);
}
