"""Run and test runtime."""

import numpy as np
from tqdm import tqdm
import manager
import threading


def _create_module(args, arts, rt, path):
    if args.type == 'PY':
        return arts.create_module_py(
            rt, name="test", aot=args.aot, path=path,
            argv=args.argv, scene=args.scene, namespace=args.namespace)
    else:
        return arts.create_module_wasm(
            rt, name="test", path=path, argv=args.argv)


def _get_runtime(rt_list, rt):
    try:
        return rt_list[rt]
    except KeyError:
        raise ValueError("Runtime not found: {}".format(rt))


def create_modules(args, arts, path):
    """Create modules with given executable path."""
    rt_list = arts.get_runtimes()
    return {
        rt: _create_module(args, arts, _get_runtime(rt_list, rt), path)
        for rt in args.runtime
    }


def profiling_round(args, arts, path):
    """Single round of active profiling."""
    modules = create_modules(args, arts, path)

    profilers = [
        manager.ActiveProfiler(
            manager.DirichletProcess(
                lambda: np.random.geometric(1 / args.mean_size),
                alpha=args.alpha),
            arts, mod, n=args.n, delay=args.delay, pbar=i,
            desc=name, semaphore=threading.Semaphore())
        for i, (name, mod) in enumerate(modules.items())
    ]

    # Join on all "threads"; can't use thread.join() since MQTT is not
    # guaranteed to actually have real threads for each callback
    for p in profilers:
        p.semaphore.acquire()


if __name__ == '__main__':

    args = manager.parse()
    arts = manager.ARTSInterface(host=args.host, port=args.port)

    tqdm.write("[Profiling] Runtimes: {}".format(args.runtime))

    if args.active:
        for i, path in enumerate(args.path):
            tqdm.write("[Profiling] Active Profiling Round {}/{}: {}".format(
                i + 1, len(args.path), path))
            profiling_round(args, arts, path)
    else:
        for path in args.path:
            create_modules(args, arts, path)

    arts.loop_stop()
