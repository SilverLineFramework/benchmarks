"""Randomly resize images for benchmark input data."""

import os
from PIL import Image
import numpy as np
from argparse import ArgumentParser
from tqdm import tqdm


_desc = "Randomly resize images for benchmark input data."


def _parse(p):
    p.add_argument("-s", "--src", default="inputs", help="Source folder.")
    p.add_argument(
        "-d", "--dst", default="data/images", help="Destination folder.")
    p.add_argument("-k", "--key", default=42, help="Random seed.", type=int)
    return p


def _main(args):
    files = os.listdir(args.src)
    os.makedirs(args.dst, exist_ok=True)
    scale_factor = np.exp(
        np.random.default_rng(args.key).uniform(-2, 2, size=len(files)))
    for f, s in zip(tqdm(files), scale_factor):
        img = Image.open(os.path.join("inputs", f))
        img.resize((round(img.size[0] * s), round(img.size[1] * s)))
        img.save(os.path.join(args.dst, f))


if __name__ == '__main__':

    args = _parse(ArgumentParser(description=_desc)).parse_args()
    _main(args)
