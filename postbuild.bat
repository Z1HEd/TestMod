@echo off
xcopy /Y "%1" "G:\Programs\steam\steamapps\common\4D Miner Demo\mods\TestMod\"
xcopy /Y "%2info.json5" "G:\Programs\steam\steamapps\common\4D Miner Demo\mods\TestMod\"
xcopy /Y "%2icon.png" "G:\Programs\steam\steamapps\common\4D Miner Demo\mods\TestMod\"
xcopy /E /I /Y /D "%2assets" "G:\Programs\steam\steamapps\common\4D Miner Demo\mods\TestMod\assets\"