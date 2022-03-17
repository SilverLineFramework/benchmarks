"""Stop all runtimes by sending a DELETE_RUNTIME request."""

from manager import SilverLine, parse, parse_args


def _arg(parser):
    g = parser.add_argument_group("Stop Runtime")
    g.add_argument(
        "--runtime", nargs="+",
        help="Runtimes to stop; if empty, stops all runtimes.", default=[])


args = parse_args(parse.mqtt, parse.arts, _arg)
arts = SilverLine.from_args(args)
runtimes = arts.get_runtimes()
if len(args.runtime) > 0:
    for rt in args.runtime:
        try:
            print("Stopping runtime {} [{}]".format(rt, runtimes[rt]))
            arts.delete_runtime(runtimes[rt], name=rt)
        except KeyError:
            print("Runtime not found: {}".format(rt))
else:
    for rt, rt_id in runtimes.items():
        print("Stopping runtime {} [{}]".format(rt, rt_id))
        arts.delete_runtime(rt_id, name=rt)

arts.loop_stop()
