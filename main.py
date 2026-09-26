from ursina import *
from ursina.prefabs.first_person_controller import FirstPersonController
#from dataclasses import dataclass
from panda3d.core import ClockObject
from sys import executable as path

print(f"DEBUG :: {path} :: PATH")

app = Ursina(title = 'TinyCube - Minecraft clone made by SpookScoop93')
app.sky = Sky(color=color.hex('#6EB1FF'), texture=None)
window.vsync = False
globalClock.setMode(ClockObject.MLimited)
globalClock.setFrameRate(30)

break_sound = Audio('block', autoplay=False)
blocks = ['cobblestone', 'grass', 'planks', 'snow', 'bricks']
selected_block = 0
block_selected = 0

class block(Button):
    def __init__(self, position=(0,0,0), texture='grass'):
        super().__init__(parent=scene,
                         position=position,
                         model='cube',
                         origin_y=5,
                         texture=texture,
                         color=color.hsv(0, 0, random.uniform(.9, 1.0)),
                         highlight_color=color.lime,
                         )
        break_sound.play()
    def on_destroy(self):
        break_sound.play()

# World
X_MAX:int = 16
Y_MAX:int = 6
Z_MAX:int = 16

def set_Y_block(y: int):
    global Y_MAX

    if y < Y_MAX-1:
        return 'cobblestone'
    else:
        return 'grass'

for x in range(X_MAX):
    for z in range(Z_MAX):
        for y in range(Y_MAX):
            blok = block(position=(x,y,z),texture=set_Y_block(y))


help_text = Text(text='LMB - place, RMB - destroy, ESC - quit', origin=(0,0), scale=2, y=0.4)
invoke(setattr, help_text, 'enabled', False, delay=20)
copyright_text = Text(text='All assets are property of Mojang.', origin=(-0.5,-0.5), scale=0.5, y=-0.45, x=-0.8)

block_panel = WindowPanel(
        title='Block Select',
        content=[
            Button(text='Cobblestone', on_click=Func(globals().__setitem__, 'block_selected', 0)),
            Button(text='Grass', on_click=Func(globals().__setitem__, 'block_selected', 1)),
            Button(text='Planks', on_click=Func(globals().__setitem__, 'block_selected', 2)),
            Button(text='Snow', on_click=Func(globals().__setitem__, 'block_selected', 3)),
            Button(text='Bricks', on_click=Func(globals().__setitem__, 'block_selected', 4)),
            ],
        enabled=False,
        y=0.1
    )

def input(key):
    global selected_block
    global block_selected

    if key == 'left mouse down':
        hit_info = raycast(camera.world_position, camera.forward, distance=5)
        if hit_info.hit:
            block(position=hit_info.entity.position + hit_info.normal, texture=blocks[selected_block])

    if key ==  'right mouse down' and mouse.hovered_entity:
        if mouse.hovered_entity.parent == scene:
            destroy(mouse.hovered_entity)

    if key == 'escape':
        mouse.locked = not mouse.locked

    if key == 'e':
        block_panel.enabled = not block_panel.enabled

    selected_block = block_selected

player = FirstPersonController()
player.cursor.enabled = False

app.run()
