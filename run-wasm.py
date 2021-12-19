"""Run and test runtime."""

import argparse

from . import manager


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument("--num", help="Number of copies", type=int, default=1)
    parser.add_argument(
        "--path", help="File name", default="python-apps/pinata.py")
    args = parser.parse_args()

    mqtt = manager.MQTTClient()
    runtime = manager.RuntimeManager(mqtt)

    for _ in range(args.num):
        input()
        runtime.create_module_wasm(filename=args.path, name=args.path)

    mqtt.client.loop_forever()
