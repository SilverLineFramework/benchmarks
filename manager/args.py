"""Base argparse args."""

import argparse


def parse():
    """Arguments for benchmark spawning."""
    parser = argparse.ArgumentParser()

    # MQTT
    parser.add_argument("--host", help="MQTT host", default="localhost")
    parser.add_argument("--port", help="MQTT port", default=1883, type=int)

    # Target
    parser.add_argument("--type", help="PY or WA", default="PY")
    parser.add_argument(
        "--path", help="File name", default="wasm/apps/helloworld.wasm")
    parser.add_argument("--argv", help="Module argv passthrough", default="")
    parser.add_argument("--runtime", help="Target name", default="test")

    # Python only args
    parser.add_argument(
        "--scene", help="Scene environment variable", default="test")
    parser.add_argument(
        "--namespace", help="Namespace environment variable",
        default="test")
    parser.add_argument(
        "--aot", help="Use AOT python", dest='aot', action='store_true')
    parser.set_defaults(aot=False)

    # Profiling
    parser.add_argument(
        "--active", help="Use active profiling", dest='active',
        action='store_true')
    parser.set_defaults(active=False)
    parser.add_argument(
        "--mean_size", default=1000, type=float,
        help="Prior mean message size (used as input to dirichlet process)")

    return parser.parse_args()
