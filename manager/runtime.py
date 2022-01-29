"""Runtime manager container."""

import uuid
import json

import ssl
import paho.mqtt.client as mqtt


class RuntimeManager:
    """Runtime manager.

    Parameters
    ----------
    mqtt : MQTTClient
        MQTT client to send create module request on

    Keyword Args
    ------------
    mqtt_host : str
        MQTT host server address.
    mqtt_port : int
        MQTT host server port.
    path : str
        Path to runtime executable
    use_arts : bool
        If False, skips ARTS and sends the CREATE_MODULE command directly
        to the runtime.
    kwargs : dict
        Additional command line args to send to the runtime, i.e.
        ```verbose=2``` or ```dir=.```
    """

    def __init__(
            self, mqtt_host="arenaxr.org", mqtt_port=8883,
            path="../runtime", use_arts=False, **kwargs):

        with open("mqtt_pwd.txt", 'r') as f:
            passwd = f.read()
        user = "cli"

        self.uuid = str(uuid.uuid4())
        self.mqtt = mqtt.Client("test_client")
        if mqtt_host != 'localhost':
            self.mqtt.tls_set(cert_reqs=ssl.CERT_NONE)
        self.mqtt.username_pw_set(user, passwd)
        self.mqtt.connect(mqtt_host, mqtt_port, 60)
        print("[Client] MQTT Client connected.")

        if use_arts:
            self.control_topic = "realm/proc/control"
        else:
            self.control_topic = "realm/proc/control/{}".format(self.uuid)

        kwargs["uuid"] = self.uuid
        run_cmd = " ".join(
            [path] + ["--{}={}".format(k, v) for k, v in kwargs.items()])
        with open("runtime.sh", "w") as f:
            f.truncate(0)
            f.write(run_cmd)
        print("Run command: ", run_cmd)

    def create_module(self, data):
        """Create module with custom payload."""
        payload = json.dumps({
            "object_id": str(uuid.uuid4()),
            "action": "create",
            "type": "arts_req",
            "data": {
                "type": "module",
                "parent": {"uuid": self.uuid},
                **data
            }
        })
        print("[Runtime] Creating module on topic {}:\n{}".format(
            self.control_topic, payload))
        self.mqtt.publish(self.control_topic, payload)

    def create_module_wasm(
            self, name="module", filename="helloworld.wasm", args=[]):
        """Create WASM module."""
        module_uuid = str(uuid.uuid4())
        self.create_module({
            "uuid": module_uuid,
            "name": name,
            "filename": "wasm-out/{}".format(filename),
            "filetype": "WA",
            "args": [filename] + args,
            "env": [],
        })
        return module_uuid

    def create_module_py(
            self, name="module", aot=False, filename="pinata.py", argv=[],
            mqtth="arena.andrew.cmu.edu", scene="test", namespace="test"):
        """Create python module."""
        python = "rustpython.{}".format("aot" if aot else "wasm")
        module_uuid = str(uuid.uuid4())
        self.create_module({
            "uuid": module_uuid,
            "name": name,
            "filename": python,
            "filetype": "PY",
            "args": [python, "python-apps/{}".format(filename)],
            "env": [
                "MQTTH={}".format(mqtth), "REALM=realm",
                "SCENE={}".format(scene), "NAMESPACE={}".format(namespace),
                "ARGV={}".format(" ".join(argv))
            ]
        })
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
