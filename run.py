"""Run and test runtime."""

import paho.mqtt.client as mqtt
import json
import sys
import ssl
import uuid
import subprocess
import time
import uuid
import argparse


class ProfileTrace:

    def __init__(self):
        self.contents = []

    def log(self, data):
        self.contents.append(data)
        if(len(self.contents) % 10 == 0):
            with open("data.json", "w") as f:
                json.dump(self.contents, f)


class MQTTClient:

    def __init__(self, host, port):
        self.client = mqtt.Client("test_client")
        self.profile = ProfileTrace()

        self.client.on_connect = self.on_connect
        self.client.on_disconnect = self.on_disconnect
        self.client.on_publish = self.on_publish
        self.client.on_message = self.on_message

        with open("mqtt_pwd.txt", 'r') as f:
            passwd = f.read()
        user = "cli"

        self.client.tls_set(cert_reqs=ssl.CERT_NONE)
        self.client.username_pw_set(user, passwd)
        self.client.connect(host, port, 60)
        print("[Tester] MQTT Client connected.")

    def on_connect(self, client, userdata, flags, rc):
        print("[Tester] Connected!")
        client.subscribe("realm/proc/profile")

    def on_disconnect(self, client, userdata, rc):
        print("[Tester] Disconnected!")

    def on_publish(self, client, userdata, mid):
        print("[Tester] sent CREATE_MODULE, message id={}".format(mid))

    def on_message(self, client, userdata, msg):
        print("[Tester] Received message on {}".format(msg.topic))
        data = json.loads(msg.payload)
        self.profile.log(data)


def get_uuid():
    res = str(uuid.uuid4())
    out = (
        "../arena-runtime-linux/runtime/out/runtime --appdir=. "
        "--dir=./python-apps --verbose=1 --uuid={}").format(res)
    with open("runtime.sh", 'w') as f:
        f.truncate(0)
        f.write(out)
    return res


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument("--host", help="MQTT host", default="arenaxr.org")
    parser.add_argument("--port", help="MQTT port", type=int, default=8883)
    parser.add_argument("--num", help="Number of copies", type=int, default=1)
    parser.add_argument(
        "--script", help="Script name", default="python-apps/pinata.py")
    args = parser.parse_args()

    mqtt = MQTTClient(args.host, args.port)
    runtime_id = get_uuid()

    print("[Tester] Message to send:")
    topic = "realm/proc/control/" + runtime_id
    with open('base.json', 'r') as f:
        json_str = json.load(f)
    json_str['data']['parent']['uuid'] = runtime_id
    # json_str['data']['args'][1] = args.script
    print(json_str)

    for _ in range(args.num):
        input()
        json_str["data"]["uuid"] = str(uuid.uuid4())
        mqtt.client.publish(topic, json.dumps(json_str))

    mqtt.client.loop_forever()
