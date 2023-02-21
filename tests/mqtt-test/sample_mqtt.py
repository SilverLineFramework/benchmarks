import paho.mqtt.client as mqtt
import time
from pathlib import Path

client = mqtt.Client("my-client")
client.connect("localhost")

string = "0";
client.publish("in/1", string)
time.sleep(0.1)

