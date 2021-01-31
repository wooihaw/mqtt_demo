import paho.mqtt.client as paho


def on_connect(self, client, userdata, rc):  # callback function for connect
    print(f"Connected with result code: {str(rc)}")


def on_subscribe(client, userdata, mid, granted_qos):  # callback function for subscribe
    print(f"Subscribed with QOS: {granted_qos}")


def on_message(client, userdata, msg):  # callback function for message
    print(f"Topic:  {msg.topic}", f"Message: {str(msg.payload)}", sep="\n")


broker = "test.mosquitto.org"
port = 1883
topic = "ESD2/temperature"

client1 = paho.Client("sub1")  # create client object
client1.on_connect = on_connect  # assign callback function for connect
client1.on_subscribe = on_subscribe  # assign callback function for subscribe
client1.on_message = on_message  # assign callback function for message
client1.connect(broker, port)  # establish connection
client1.subscribe(topic, 0)  # subscribe
client1.loop_forever()  # wait for message
