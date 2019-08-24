# cctetris
Very simple tetris game I made over the last couple days in c++ as OOP practice  
It's quite limited since I don't know all that much about X11 (Event-driven, can't make it run without user input)  
But it has scoring, detects lines and lets you move pieces as you would expect in tetris  
Only tested in linux on WSL, can't guarantee functionality on anything else

Credit to jfdoming on GitHub for Makefile

# controls
W - Rotate
A - Move left
D - Move right
S - Move down
Q - Quit
Any - Progress game
# graphcs guide
To setup:
1. Install Xserver (I use XMing)
2. Run command ``export Display=:0``
3. Cd into folder with game from terminal
4. run ``./tetris`` command in terminal (run ``make`` if executable isn't there)
