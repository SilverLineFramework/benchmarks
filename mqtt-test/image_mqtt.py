import os
import paho.mqtt.client as mqtt
import time
from pathlib import Path

client = mqtt.Client("my-client")
client.connect("localhost")

# Benchmarks directory is the root for runtime execution
os.chdir('..')
root = Path("data/images")
for child in root.iterdir():
    if child.is_file():
        string = "5,2,first-arg," + child.as_posix() + '\0';
        client.publish("in/1", string)
        time.sleep(0.3)

