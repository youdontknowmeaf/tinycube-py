sleep 1 && printf "\033[1;34m===== [ Building ] =======================\033[0m\n"
pyinstaller --onefile --noconsole --collect-all ursina --collect-all panda3d main.py
sleep 1 && printf "\033[1;34m===== [ Cleaning up work directory ] =====\033[0m\n"
rm -r build main.spec
sleep 1 && printf "\033[1;34m===== [ Copying assets ] =================\033[0m\n"
cp -r textures audio dist/
sleep 1 && printf "\033[1;34m===== [ Making a tarball ] ===============\033[0m\n"
tar -czvf TinyCube_full.tar.gz -C dist .
sleep 1 && printf "\033[1;34m===== [ Build finished ] =================\033[0m\n"
