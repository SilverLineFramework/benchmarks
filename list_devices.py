"""Helper script to list devices from manifest TSV file."""

import argparse
import pandas as pd

parser = argparse.ArgumentParser()
parser.add_argument(
    "--manifest", help="Device specification .tsv file", default="devices.tsv")
args = parser.parse_args()

t = pd.read_csv(args.manifest, sep='\t')
linux_rt = t[t['Type'] == 'linux']
print('\n'.join(list(linux_rt['Device'])))
