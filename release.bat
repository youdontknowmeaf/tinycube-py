REM this file is vibecoded.

Start-Sleep -Seconds 1; Write-Host "===== [ Building ] =======================" -ForegroundColor Blue
pyinstaller --onefile --noconsole --collect-all ursina --collect-all panda3d main.py

Start-Sleep -Seconds 1; Write-Host "===== [ Cleaning up work directory ] =====" -ForegroundColor Blue
Remove-Item -Recurse -Force build, main.spec -ErrorAction SilentlyContinue

Start-Sleep -Seconds 1; Write-Host "===== [ Copying assets ] =================" -ForegroundColor Blue
Copy-Item textures, audio dist/ -Recurse -Force

Start-Sleep -Seconds 1; Write-Host "===== [ Zipping output ] ===================" -ForegroundColor Blue
Compress-Archive -Path "dist/*" -DestinationPath "TinyCube_full.zip" -Force

Start-Sleep -Seconds 1; Write-Host "===== [ Build finished ] =================" -ForegroundColor Blue
