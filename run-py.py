"""Run and test runtime."""

import argparse

from . import manager


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument("--num", help="Number of copies", type=int, default=1)
    parser.add_argument(
        "--script", help="Script name", default="python-apps/pinata.py")
    parser.add_argument(
        "--scene", help="Scene environment variable", default="test")
    parser.add_argument(
        "--namespace", help="Namespace environment variable", default="test")
    args = parser.parse_args()

    mqtt = manager.MQTTClient()
    runtime = manager.RuntimeManager(mqtt)

    for _ in range(args.num):
        input()
        runtime.create_module_py(
            filename=args.script, name=args.script,
            scene=args.scene, namespace=args.namespace)

    mqtt.client.loop_forever()
