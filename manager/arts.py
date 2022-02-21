"""ARTS messages."""

import json
import uuid
import requests
import paho.mqtt.client as mqtt


class ARTSInterface(mqtt.Client):
    """ARTS Interface.

    Keyword Args
    ------------
    host : str
        MQTT host server address.
    port : int
        MQTT host server port.
    semaphore : threading.Semaphore
        Notification on connection.
    """

    def __init__(self, host="localhost", port=1883, semaphore=None):

        with open("mqtt_pwd.txt", 'r') as f:
            passwd = f.read()
        user = "cli"

        self.callbacks = {}
        self.host = host
        self.semaphore = semaphore
        self.semaphore.acquire()

        super().__init__("Benchmarking")
        self.username_pw_set(user, passwd)
        self.connect(host, port, 60)

    def on_connect(self, mqttc, obj, flags, rc):
        """On connect callback."""
        print("[Setup] Connected: rc={}".format(rc))
        if self.semaphore is not None:
            self.semaphore.release()

    def _create_module(self, data, target):
        """Create Module helper function."""
        payload = json.dumps({
            "object_id": str(uuid.uuid4()),
            "action": "create",
            "type": "arts_req",
            "data": {
                "type": "module",
                "parent": {"uuid": target},
                **data
            }
        })
        print("[ARTS] Creating module:\n{}".format(payload))
        self.publish("realm/proc/control", payload)

    def create_module_wasm(
            self, target, name="module",
            path="wasm/apps/helloworld.wasm", argv=[]):
        """Create WASM module."""
        module_uuid = str(uuid.uuid4())
        self._create_module({
            "uuid": module_uuid,
            "name": name,
            "filename": path,
            "filetype": "WA",
            "args": [path] + argv,
            "env": [],
        }, target)
        return module_uuid

    def create_module_py(
            self, target, name="module", aot=False, path="python/pinata.py",
            argv=[], scene="test", namespace="test"):
        """Create python module."""
        python = "wasm/rustpython.{}".format("aot" if aot else "wasm")
        module_uuid = str(uuid.uuid4())
        self._create_module({
            "uuid": module_uuid,
            "name": name,
            "filename": python,
            "filetype": "PY",
            "args": [python, "python-apps/{}".format(path)],
            "env": [
                "MQTTH={}".format(self.host), "REALM=realm",
                "SCENE={}".format(scene), "NAMESPACE={}".format(namespace),
                "ARGV={}".format(" ".join(argv))
            ]
        }, target)
        return module_uuid

    def delete_module(self, target):
        """Delete module."""
        msg = {
            "object_id": str(uuid.uuid4()),
            "action": "delete",
            "type": "arts_req",
            "data": {"type": "module", "uuid": target}
        }
        print("[ARTS] Deleting module: {}".format(target))
        self.mqtt.publish(self.control_topic, json.dumps(msg))

    def register_callback(self, topic, callback):
        """Subscribe to topic and register callback for that topic."""
        self.subscribe(topic)
        self.callbacks[topic] = callback

    def on_message(self, client, userdata, message):
        """Subscribed message handler."""
        topic = str(message.topic)
        try:
            self.callbacks[topic](message.payload)
        except KeyError:
            print("[Warning] topic without handler: {}".format(topic))

    def get_runtimes(self):
        """Get runtimes from REST API."""
        r = requests.get(
            "http://{}:8000/arts-api/v1/runtimes/".format(self.host))
        res = json.loads(r.text)

        return {rt['name']: rt['uuid'] for rt in res}
