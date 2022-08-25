import paho.mqtt.client as mqtt
import time
from pathlib import Path

client = mqtt.Client("my-client")
client.connect("localhost")
client.publish("benchmark/exit/all", '1')
