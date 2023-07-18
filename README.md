# Qt5-OpenCV-Raspberry-Pi
Native build of Qt5 creator on Raspberry Pi 4 or Jetson Nano with OpenCV support
## A live camera C++ example on a Raspberry Pi 4 / Jetson Nano with Qt5 GUI using OpenCV <br/> 
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)<br/><br/>
see [Qt5](https://qengineering.eu/install-qt5-with-opencv-on-raspberry-pi-4.html) where this example is explored. 
## Dependencies.
To run the application, you have to:
- Qt5 installed [Install Qt5](https://qengineering.eu/install-qt5-with-opencv-on-raspberry-pi-4.html)<br/>
- OpenCV installed [Install OpenCV 32-bit OS](https://qengineering.eu/install-opencv-on-raspberry-pi-4.html)  ,  [Install OpenCV 64-bit OS](https://qengineering.eu/install-opencv-on-raspberry-64-os.html) or [Install OpenCV on Jetson Nano](https://qengineering.eu/install-opencv-on-jetson-nano.html) <br/>

------------

## Running the app.
To run the application load the project file Viewer.pro in the Qt5 Creators.<br><br>
Select the OS you are using in myvideocapture.cpp at line 30.<br><br>
Bullseye
```cpp
    //  Raspberry Pi Bullseye
    mVideoCap.open(pipeline, cv::CAP_GSTREAMER);
```
Buster
```cpp
    //  Raspberry Pi Buster or Jetson Nano
    mVideoCap.open( ID_CAMERA );
```

<br><br>
[![paypal](https://qengineering.eu/images/TipJarSmall4.png)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=CPZTM5BB3FCYL) 
