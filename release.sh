pyinstaller --onefile --noconsole --collect-all ursina --collect-all panda3d main.py
rm -r build main.spec
cp *.png dist/
