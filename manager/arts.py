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
    """

    def __init__(self, host="localhost", port=1883):

        with open("mqtt_pwd.txt", 'r') as f:
            passwd = f.read()
        user = "cli"

        self.host = host

        super().__init__("Benchmarking")
        self.username_pw_set(user, passwd)
        self.connect(host, port, 60)

    def on_connect(self, mqttc, obj, flags, rc):
        """On connect callback."""
        print("[Client] Connected: rc={}".format(rc))

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
        print("[Runtime] Creating module on topic {}:\n{}".format(
            "realm/proc/control", payload))
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
        print("[Runtime] Deleting module: {}".format(target))
        self.mqtt.publish(self.control_topic, json.dumps(msg))

    def get_runtimes(self):
        """Get runtimes from REST API."""
        r = requests.get(
            "http://{}:8000/arts-api/v1/runtimes/".format(self.host))
        res = json.loads(r.text)

        return {rt['name']: rt['uuid'] for rt in res}
