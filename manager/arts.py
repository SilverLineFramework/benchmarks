"""ARTS messages."""

import json
import uuid
import requests
import ssl

from threading import Semaphore
import paho.mqtt.client as mqtt


def arts_args(parser):
    """Add arguments to argparse."""
    g = parser.add_argument_group('MQTT Options')
    g.add_argument("--host", help="Host address", default="localhost")
    g.add_argument("--port", help="Host port", default=1883, type=int)
    g.add_argument("--username", help="Username", default="cli")
    g.add_argument("--pwd", help="Password file", default="mqtt_pwd.txt")
    g.add_argument(
        "--use_ssl", help="Use SSL (mqtt-secure)", action='store_true')

    g = parser.add_argument_group('ARTS Options')
    g.add_argument("--arts", help="ARTS host", default="localhost")
    g.add_argument("--arts_port", help="ARTS port", default=8000)
    g.set_defaults(ssl=False)
    return parser


class ARTSInterface(mqtt.Client):
    """ARTS Interface.

    Keyword Args
    ------------
    host : str
        MQTT host server address.
    port : int
        MQTT host server port.
    arts : str
        ARTS HTTP server address.
    arts_port : int
        ARTS HTTP server port.
    pwd : str
        MQTT password file
    username : str
        MQTT username
    ssl : bool
        Whether to use SSL.
    connect : bool
        If False, don't connect to MQTT.
    """

    def __init__(
            self, host="localhost", port=1883, pwd="mqtt_pwd.txt",
            username="cli", use_ssl=False, arts="localhost", arts_port=8000,
            connect=True):

        self.callbacks = {}
        self.host = host
        self.arts_api = "http://{}:{}/arts-api/v1".format(arts, arts_port)

        super().__init__("Benchmarking")

        if connect:
            self.semaphore = Semaphore()
            self.semaphore.acquire()

            with open(pwd, 'r') as f:
                passwd = f.read()
            if passwd[-1] == '\n':
                passwd = passwd[:-1]
            self.username_pw_set(username, passwd)
            if use_ssl:
                self.tls_set(cert_reqs=ssl.CERT_NONE)
            self.connect(host, port, 60)

            # Waiting for on_connect to release
            self.loop_start()
            self.semaphore.acquire()

    @classmethod
    def from_args(cls, args, connect=True):
        """Construct from argparse.ArgumentParser."""
        return cls(
            host=args.host, port=args.port, pwd=args.pwd,
            username=args.username, use_ssl=args.use_ssl, arts=args.arts,
            arts_port=args.arts_port, connect=connect)

    def on_connect(self, mqttc, obj, flags, rc):
        """On connect callback."""
        print("[Setup] Connected: rc={} ({})".format(
            rc, mqtt.connack_string(rc)))
        if self.semaphore is not None:
            self.semaphore.release()

    def on_disconnect(self, client, userdata, rc):
        """Disconnection callback."""
        print("[Error] Disconnected: rc={} ({})".format(
            rc, mqtt.connack_string(rc)))

    def delete_runtime(self, target, name="test"):
        """Instruct runtime to exit."""
        payload = json.dumps({
            "object_id": str(uuid.uuid4()),
            "action": "delete",
            "type": "arts_req",
            "data": {
                "type": "runtime",
                "uuid": target,
                "name": name
            }
        })
        self.publish("realm/proc/control/{}".format(target), payload)

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
            "args": [python, "python-apps/{}".format(path)] + argv,
            "env": [
                "MQTTH={}".format(self.host), "REALM=realm",
                "SCENE={}".format(scene), "NAMESPACE={}".format(namespace),
                "ARGV={}".format(" ".join(argv))
            ]
        }, target)
        return module_uuid

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
        r = requests.get("{}/runtimes/".format(self.arts_api))
        try:
            res = json.loads(r.text)
        except Exception as e:
            print(r.text)
            raise e

        return {rt['name']: rt['uuid'] for rt in res}
