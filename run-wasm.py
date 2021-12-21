"""Run and test runtime."""

import numpy as np
import time

import manager


if __name__ == '__main__':

    parser = manager.parser_common()
    parser.add_argument(
        "--path", help="File name", default="helloworld.wasm")
    args = parser.parse_args()

    kw = {"dir": ".", "appdir": "."}
    kw.update(args.kwargs)

    mqtt = manager.MQTTClient()
    runtime = manager.RuntimeManager(mqtt, **kw)

    uuids = []
    for _ in range(args.num):
        input()
        uuids.append(
            runtime.create_module_wasm(
                filename=args.path, name=args.path, args=args.argv.split(" ")))

    topic = "ch/in/{}".format(uuids[0])
    print("[Data] topic: ", topic)
    while True:
        mqtt.client.loop()
        mqtt.client.publish(topic, np.random.bytes(1024))
        time.sleep(0.2)
