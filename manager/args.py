"""Base argparse args."""


def benchmark_args(parser):
    """Arguments for benchmark spawning."""
    # Target
    parser.add_argument("--type", help="PY or WA", default="PY")
    parser.add_argument(
        "--path", nargs="+", help="File path(s) to execute",
        default=["wasm/test/helloworld.wasm"])
    parser.add_argument(
        "--argv", nargs="+", help="Module argv passthrough", default=[])
    parser.add_argument(
        "--runtime", nargs='+', help="Target runtimes", default=["test"])

    # Python only args
    parser.add_argument(
        "--env", nargs='+', help="Module environment variables", default=[])
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
    parser.add_argument(
        "--alpha", default=1, type=float,
        help="Dirichlet Process 'new table' parameter alpha.")
    parser.add_argument(
        "--n", default=100, type=int,
        help="Number of iterations to test")
    parser.add_argument(
        "--delay", default=0.1, type=float, help="Delay between iterations")

    return parser
