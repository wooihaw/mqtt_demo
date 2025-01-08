import paho.mqtt.client as paho
from time import sleep
from random import randint


def on_publish(client, userdata, result):  # callback function for publish
    global temp
    print(f"Data published: {temp}")


broker = "test.mosquitto.org"
port = 1883
topic = "ESD2/temperature"

client1 = paho.Client("pub1")  # create client object
client1.on_publish = on_publish  # assign callback function
client1.connect(broker, port)  # establish connection

while True:
    temp = randint(20, 30)
    ret = client1.publish(topic, temp)  # publish
    sleep(5)
