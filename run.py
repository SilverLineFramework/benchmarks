"""Run and test runtime."""

import numpy as np
from tqdm import tqdm
import time
import manager
import threading


def _create_module(args, arts, rt, argv):
    if args.type == 'PY':
        return arts.create_module_py(
            rt, name="test", aot=args.aot, path=args.path,
            argv=argv, scene=args.scene, namespace=args.namespace)
    else:
        return arts.create_module_wasm(
            rt, name="test", path=args.path, argv=argv)


def _get_runtime(rt_list, rt):
    try:
        return rt_list[rt]
    except KeyError:
        raise ValueError("Runtime not found: {}".format(rt))


def create_modules(args, arts):
    """Create module, calling different methods for PY and WA.

    If args.runtime is a comma-separated list, creates multiple modules.
    """
    rt_list = arts.get_runtimes()
    argv = args.argv.split(',')

    return {
        rt: _create_module(args, arts, _get_runtime(rt_list, rt), argv)
        for rt in args.runtime.split(",")
    }


if __name__ == '__main__':

    args = manager.parse()
    arts = manager.ARTSInterface(
        host=args.host, port=args.port, semaphore=threading.Semaphore())
    arts.loop_start()
    arts.semaphore.acquire()

    modules = create_modules(args, arts)

    if args.active:

        print("[Profiling] Beginning active profiling for {} runtimes.".format(
            len(modules)))

        pbar_global = tqdm(total=len(modules), position=0, desc="Completed")

        profilers = [
            manager.ActiveProfiler(
                manager.DirichletProcess(
                    lambda: np.random.geometric(1 / args.mean_size),
                    alpha=args.alpha),
                arts, mod, n=args.n, delay=args.delay, pbar=i + 1,
                desc=name, semaphore=threading.Semaphore(),
                pbar_global=pbar_global)
            for i, (name, mod) in enumerate(modules.items())
        ]

        # Join on all "threads"; can't use thread.join() since MQTT is not
        # guaranteed to actually have real threads for each callback
        for p in profilers:
            p.semaphore.acquire()

    arts.loop_stop()
