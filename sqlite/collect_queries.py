import os
import json
import jsbeautifier


def _load(db):
    args = []
    for p in os.listdir(db):
        with open(os.path.join(db, p)) as f:
            query = f.read()
        args.append(["data/sqlite/{}.db".format(db), query.replace("\n", " ")])
    return args


args = _load("chinook") + _load("northwind")
with open("tests.json", 'w') as f:
    out = json.dumps(args)
    out = jsbeautifier.beautify(out, jsbeautifier.default_options())
    f.write(out)
