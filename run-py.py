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
    parser.add_argument(
        "--mode", help="Testing mode", default="profile")
    args = parser.parse_args()

    kw = {"dir": ".", "appdir": "."}
    kw.update(args.kwargs)

    mqtt = manager.MQTTClient()
    runtime = manager.RuntimeManager(mqtt, **kw)

    input()

    if args.mode == "delete":
        for i in range(10):
            uuids = []
            for _ in range(args.num):
                time.sleep(0.5)
                uuids.append(
                    runtime.create_module_py(
                        filename=args.script, aot=args.aot, name=args.script,
                        scene=args.scene, namespace=args.namespace,
                        argv=args.argv.split(" ")))
            for d in uuids:
                time.sleep(0.5)
                runtime.delete_module(d)
    elif args.mode == "profile":
        uuids = []
        for _ in range(args.num):
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
