"""Run and test runtime."""

import time
import numpy as np

import manager


if __name__ == '__main__':

    parser = manager.parser_common()
    parser.add_argument(
        "--script", help="Script name", default="pinata.py")
    parser.add_argument(
        "--scene", help="Scene environment variable", default="test")
    parser.add_argument(
        "--namespace", help="Namespace environment variable", default="test")
    parser.add_argument(
        "--aot", help="Use AOT python", default=False, type=bool)
    args = parser.parse_args()

    kw = {"dir": ".", "appdir": "."}
    kw.update(args.kwargs)

    mqtt = manager.MQTTClient()
    runtime = manager.RuntimeManager(mqtt, **kw)

    uuids = []
    for _ in range(args.num):
        input()
        uuids.append(
            runtime.create_module_py(
                filename=args.script, aot=args.aot, name=args.script,
                scene=args.scene, namespace=args.namespace,
                argv=args.argv.split(" ")))

    topic = "ch/in/test"
    print("[Data] topic: ", topic)
    while True:
        mqtt.client.loop()
        mqtt.client.publish(topic, np.random.bytes(1024))
        time.sleep(0.2)
