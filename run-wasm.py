"""Run and test runtime."""

import argparse
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

    for _ in range(args.num):
        input()
        runtime.create_module_wasm(filename=args.path, name=args.path)

    mqtt.client.loop_forever()
