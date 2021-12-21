"""Main benchmark dispatcher."""

import channels
import os


def block_identity(buf):
    """Identity block."""
    print("[Block] Identity -> {}...".format(hex(buf[0])))
    return buf


def block_not(buf):
    """Simple bitwise not block for testing."""
    res = bytes([(~x & 0xff) for x in buf])
    print("[Block] Bitwise Not -> {}...".format(hex(res[0])))
    return res


processing_blocks = [block_identity, block_not]

ch_in = channels.ch_open("ch/in/test", channels.O_RDONLY, 0)
ch_out = channels.ch_open("ch/out", channels.O_WRONLY, 0)

block_order = [int(i) for i in os.environ["ARGV"].split(" ")]

while True:
    n = channels.ch_poll([ch_in], 10000)
    if (n > 0):
        buf = channels.ch_read_msg(ch_in)
        print("[Benchmark] Received: {}... ({})".format(hex(buf[0]), len(buf)))
        for b in block_order:
            try:
                buf = processing_blocks[b](buf)
            except IndexError:
                print("[Block] Invalid block index: %d".format(b))
        channels.ch_write_msg(ch_out, buf)
