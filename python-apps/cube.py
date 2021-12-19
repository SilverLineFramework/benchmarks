import os
import random
import inspect
import math

try:
    from arena import *
except ImportError:
    from arena_flat import *

os.environ["MQTTH"] = "arena.andrew.cmu.edu"
os.environ["REALM"] = "realm"

# ./build/iwasm --dir=. -v=5 --heap-size=1024 --env="NAMESPACE=jameszha" --e rustpython.aot arenatest.py

color_index = 0
colors = ["FFFFFF", "FF0000", "FF0066", "FF00FF", "0000FF", "00FF00", "66FF00", "000000"]
counter = 0

# setup library
scene = Scene()


box = Box(object_id="my_box", position=Position(0,4,-2), scale=Scale(3,3,3), rotation=Rotation(0, 0, 0), color=colors[color_index], clickable=True)
scene.add_object(box)

def mouse_handler(scene, evt, msg):
    global color_index
    if evt.type == "mousedown":
        print("MOUSEDOWN")
        color_index = (color_index + 1) % len(colors)

# add click_listener
scene.update_object(box, click_listener=True, evt_handler=mouse_handler)

@scene.run_forever(interval_ms=50)
def move():
    global counter
    counter += 1

    position = Position(0,4+math.cos(counter/10),-2)
    rotation = Rotation(0, counter, 0)
    color = colors[color_index]

    box.update_attributes(position=position, rotation=rotation, color=color)

    scene.update_object(box)

# start tasks
scene.run_tasks()
