"""Run and test runtime.

To use local:
```shell
python run-py.py --kwargs host=localhost:1883 --bypass-arts True \
    --host localhost --port 1883 --script=arenatest.py
```
"""

import time
import numpy as np

import manager


def _create_module(args):
    """Create single module, calling different methods for PY and WA."""
    if args.type == 'PY':
        return runtime.create_module_py(
            filename=args.script, aot=args.aot, name=args.script,
            scene=args.scene, namespace=args.namespace,
            argv=args.argv.split(","))
    else:
        return runtime.create_module_wasm(
            filename=args.path, name=args.path, args=args.argv.split(","))


def create_modules(args, sleep=0):
    """Create modules from args and return UUIDs."""
    uuids = []
    for _ in range(args.num):
        if sleep > 0:
            time.sleep(sleep)
        uuids.append(_create_module(args))
    return uuids


if __name__ == '__main__':

    args, kw = manager.parse()
    runtime = manager.RuntimeManager(
        mqtt_host=args.host, mqtt_port=args.port, use_arts=args.arts, **kw)
    input()

    if args.mode == "delete":
        for i in range(10):
            uuids = create_modules(args, sleep=0.5)
            for d in uuids:
                time.sleep(0.5)
                runtime.delete_module(d)
        runtime.mqtt.loop_forever()
    elif args.mode == "profile_active":
        uuids = create_modules(args, sleep=0)
        topics = ["ch/in/{}".format(u) for u in uuids]
        print("[Data] topics: ", topics)
        while True:
            for t in topics:
                data = bytes(
                    np.random.uniform(size=args.size // 4).astype(np.float32))
                runtime.mqtt.publish(t, data)
                runtime.mqtt.loop()
            time.sleep(1)
    elif args.mode == "profile":
        _ = create_modules(args, sleep=0)
        runtime.mqtt.loop_forever()
