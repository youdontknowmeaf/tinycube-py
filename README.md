# tinycube-py
A small minecraft-like game inspired by Minecraft RD-XXXX, made in python3 with Ursina.

# features
Blocks:
- Grass
- Cobblestone
World:
- Flat with simple render (grass on first 2 layers, then cobblestone)

# how to run (not from release)
**Linux**
```sh
python3 -m venv venv
source venv/bin/activate
pip install ursina # or pip3
python3 main.py
```
**ShitDOS** (Windows)
cmd:
```cmd
python -m venv venv
venv\Scripts\activate.bat
python -m pip install ursina
python main.py
```
PowerShell (w/o venv)
```ps
python -m pip install ursina
python main.py
```

if you want to build a executable then after making sure the game works with just python3 run one of the scripts for your platform (without leaving venv if you are in one):
For WinDOS
```ps
release.bat
```
For Linux
```sh
sh release.sh
# or
chmod +x release.sh
./release.sh
```

Important - make sure the textures are called by their original name. And that they are in the same folder as the game or in a subfolder called "textures" (same for audio).
You may use custom textures by just changing the .png files.
