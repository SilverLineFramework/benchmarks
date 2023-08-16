import os
import json
import jsbeautifier

args = []
for p in sorted(os.listdir("results")):
    with open(os.path.join("results", p)) as f:
        contents = f.readline()
    if not contents.startswith("process exited"):
        args.append(["data/python/tests/{}".format(p)])

with open("tests.json", 'w') as f:
    out = json.dumps(args)
    out = jsbeautifier.beautify(out, jsbeautifier.default_options())
    f.write(out)
