"""Run and test runtime."""

import numpy as np
import time
import manager


def create_module(args, arts):
    """Create module, calling different methods for PY and WA."""
    try:
        runtime = arts.get_runtimes()[args.runtime]
    except KeyError as e:
        print("Runtime not found: {}".format(args.runtime))
        raise e

    argv = args.argv.split(',')
    if args.type == 'PY':
        return arts.create_module_py(
            runtime, name="test", aot=args.aot, path=args.path,
            argv=argv, scene=args.scene, namespace=args.namespace)
    else:
        return arts.create_module_wasm(
            runtime, name="test", path=args.path, argv=argv)


if __name__ == '__main__':

    args = manager.parse()
    arts = manager.ARTSInterface(host=args.host, port=args.port)

    mod = create_module(args, arts)

    if args.active:
        time.sleep(1)

        arts.subscribe("benchmark/out/{}".format(mod))
        dp = manager.DirichletProcess(
            lambda: np.random.geometric(1 / args.mean_size))

        def trigger(mqttc, obj, msg):
            print("Received")
            arts.publish("benchmark/in/{}".format(mod))

        arts.on_message = trigger
        trigger(None, None, None)

        arts.loop_forever()
