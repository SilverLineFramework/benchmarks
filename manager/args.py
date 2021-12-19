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


def parser_common():
    """Common flags."""
    parser = argparse.ArgumentParser()
    parser.add_argument("--num", help="Number of copies", type=int, default=1)
    parser.add_argument(
        "--kwargs", help="Runtime passthrough args",
        nargs="*", action=ArgKeyValue, default={})

    return parser
