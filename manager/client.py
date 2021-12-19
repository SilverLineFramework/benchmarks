"""MQTT Client."""

import json
import ssl
import paho.mqtt.client as mqtt


class ProfileTrace:
    """Profile logging."""

    def __init__(self):
        self.contents = []

    def log(self, data):
        """Log data (given as json)."""
        self.contents.append(data)
        if(len(self.contents) % 25 == 0):
            with open("data.json", "w") as f:
                json.dump(self.contents, f)
            print("[Profile] Saved profile trace (n={})".format(
                len(self.contents)))


class MQTTClient:
    """MQTT Client."""

    def __init__(self, host="arenaxr.org", port=8883):
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
        print("[Client] MQTT Client connected.")

    def on_connect(self, client, userdata, flags, rc):
        """MQTT connect callback."""
        print("[Client] Connected!")
        client.subscribe("realm/proc/profile")

    def on_disconnect(self, client, userdata, rc):
        """MQTT disconnect callback."""
        print("[Client] Disconnected!")

    def on_publish(self, client, userdata, mid):
        """MQTT publish callback."""
        print("[Client] sent CREATE_MODULE, message id={}".format(mid))

    def on_message(self, client, userdata, msg):
        """MQTT message arrived callback."""
        # print("[Client] Received message on {}".format(msg.topic))
        data = json.loads(msg.payload)
        self.profile.log(data)
