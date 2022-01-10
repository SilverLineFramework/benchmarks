"""Base argparse args."""

import argparse


class ArgKeyValue(argparse.Action):
    """Argparse class for key-value pairs."""

    def __call__(self, parser, namespace, values, option_string=None):
        """Call override."""
        setattr(namespace, self.dest, dict())

        for value in values:
            key, value = value.split('=')
            getattr(namespace, self.dest)[key] = value


def _create_parser(py=True):
    """Create parser."""
    parser = argparse.ArgumentParser()

    parser.add_argument("--type", help="PY or WA", default="PY")

    parser.add_argument("--num", help="Number of copies", type=int, default=1)
    parser.add_argument(
        "--kwargs", help="Runtime passthrough args",
        nargs="*", action=ArgKeyValue, default={})
    parser.add_argument(
        "--argv", help="Module argv passthrough", default="")
    parser.add_argument(
        "--arts", help="Use ARTS", default=False, type=bool)
    parser.add_argument("--host", help="MQTT Host", default="arenaxr.org")
    parser.add_argument("--port", help="MQTT Port", default=8883, type=int)

    parser.add_argument(
        "--mode", help="Testing mode (profile, profile_active, or delete)",
        default="profile")

    parser.add_argument(
        "--script", help="Script name", default="pinata.py")
    parser.add_argument(
        "--scene", help="Scene environment variable", default="test")
    parser.add_argument(
        "--namespace", help="Namespace environment variable",
        default="test")
    parser.add_argument(
        "--aot", help="Use AOT python", default=False, type=bool)

    parser.add_argument(
        "--path", help="File name", default="helloworld.wasm")
    return parser


def parse(py=True):
    """Parse arguments."""
    args = _create_parser(py=py).parse_args()

    kw = {"dir": ".", "appdir": "."}
    kw.update(args.kwargs)

    return args, kw
