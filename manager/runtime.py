"""Runtime manager container."""

import uuid
import json


class RuntimeManager:
    """Runtime manager.

    Parameters
    ----------
    mqtt : MQTTClient
        MQTT client to send create module request on

    Keyword Args
    ------------
    path : str
        Path to runtime executable
    kwargs : dict
        Additional command line args to send to the runtime, i.e.
        ```verbose=2``` or ```dir=.```
    """

    def __init__(
            self, mqtt,
            path="../arena-runtime-linux/runtime/out/runtime", **kwargs):

        self.mqtt = mqtt
        self.uuid = str(uuid.uuid4())
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
        print("[Runtime] Creating module:")
        print(json.dumps(data))
        self.mqtt.client.publish(self.control_topic, json.dumps(data))

    def create_module_wasm(self, name="module", filename="helloworld.wasm"):
        """Create WASM module."""
        msg = {
            "object_id": str(uuid.uuid4()),
            "action": "create",
            "type": "arts_req",
            "data": {
                "type": "module",
                "uuid": str(uuid.uuid4()),
                "name": name,
                "parent": {"uuid": self.uuid},
                "filename": "wasm-out/{}".format(filename),
                "fileid": "na",
                "filetype": "WASM",
                "apis": [],
                "args": [filename],
                "channels": [],
                "peripherals": []
            }
        }
        self.create_module(msg)

    def create_module_py(
            self, name="module", filename="pinata.py",
            mqtth="arena.andrew.cmu.edu", scene="test", namespace="test"):
        """Create python module."""
        msg = {
            "object_id": str(uuid.uuid4()),
            "action": "create",
            "type": "arts_req",
            "data": {
                "type": "module",
                "uuid": str(uuid.uuid4()),
                "name": name,
                "parent": {"uuid": self.uuid},
                "filename": "rustpython.wasm",
                "fileid": "na",
                "filetype": "PY",
                "apis": ["python:python3"],
                "args": ["rustpython.wasm", "python-apps/{}".format(filename)],
                "env": [
                    "MQTTH={}".format(mqtth), "REALM=realm",
                    "SCENE={}".format(scene), "NAMESPACE={}".format(namespace)
                ],
                "channels": [],
                "peripherals": [],
                "resources": {
                    "runtime": 10000000,
                    "period": 40000000,
                    "affinity": 2
                }
            }
        }
        self.create_module(msg)
