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
git clone git@github.com:arturzxc/myapex.git
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













