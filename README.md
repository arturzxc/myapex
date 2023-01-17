# MyApex
Simple C++ cheats for Apex Legends (Linux Steam version).

### Sense 
Invisible enemies will be highlighted with Bloodhound Scan.
Visible enemies will be highlighted using Caustic Vision.

### NoRecoil
Adjustable reduction in vertical and horizontal weapon recoil.

### Aimbot
An adjustable aimbot intended for CQC combat. 
Works of enemy posistion rather than bones. 
Only works horizontally.

## Requirements
1. Linux OS with X11
2. g++ compiler (Ubuntu 11.2.0-19ubuntu1) 11.2.0 or higher)
3. Git

### HOW TO SETUP & RUN

1. Open terminal and run the following to download the cheat source code

```
git clone https://github.com/arturzxc/myapex.git
```

2. Go inside the downloaded folder

```
cd myapex
```

3. Compile the code 

```
g++ Main.cpp -lX11
```

4. Go to your Steam and run Apex Legends

5. Run the cheat (requires sudo access for read & write memory)

```
sudo ./a.out
```

If everything went fine then you will see something simmilar to the text below
```
======================== SETTINGS LOADED ========================
FEATURE_AIMBOT_ON               false
FEATURE_NORECOIL_ON             true
FEATURE_SENSE_ON                true
AIMBOT_TRIGGER                  0
AIMBOT_SMOOTHING                100
AIMBOT_ACTIVATION_FOV           20
AIMBOT_MAX_RANGE                50
NORECOIL_PITCH_STRENGTH         0.500000
NORECOIL_YAW_STRENGTH           0.500000
=================================================================

UPDATE[1000] OK. 
UPDATE[0] OK. 
UPDATE[1000] OK. 
UPDATE[0] OK. 
```

# FAQ

### Why nothing is working!
Check your settings and make sure the features you want to use are set to true but if that doesn't work then the offsets might need an update. For any devs out there, please feel free to create pull requests for offset updates.


### Why aimbot is not working!?
Aimbot is disabled by default. If you want it to work then edit myapex.ini and set it to true.

### I am getting "... fatal error: X11/Xlib.h ... "
You are missing X11 library for linux. On ubuntu based distros, you can install it with the command below

```
sudo apt install libx11-dev
```


### Segmentation fault!
Offsets need an update

### "The client is not running the anti-cheating system, bla bla errors..."
This has nothing to do with the cheat but rather linux/steam/apex installation.
Make sure you have the "Proton EasyAntiCheat Runtime" installed on Steam.
There are times that even if you have the above installed, it still has issues. This is due to linux libraries being outdated. I personally suggest you install Steam via Flatpak to avoid any problem with libraries.










