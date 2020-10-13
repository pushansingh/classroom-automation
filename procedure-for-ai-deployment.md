**Procedure for AI Deployment setup**

For the deployment of AI, First we install an OS on our Device. Raspbian is the official supported OS for pi and we installed that on our Raspberry Pi. We downloaded The ISO image from the Pi Foundation website and flashed the ISO image using “Raspberry Pi Imager” which is the official flasher for the raspberry pi on our SD card then we proceeded to install the OS on our Raspberry Pi
.

We then started configuring the OS using the connected mouse and keyboard but we thought what if we can control the device and can configure it from our desktop. So we then proceed with remotely controlling the device
Virtual Network Computing(VNC) is a GUI desktop sharing application that allows us to remotely control the desktop interface of one OS from another OS and from one computer to another computer or smartphone. So we proceeded with installing VNC Server on our PI so that we can do work from our Primary Computer. VNC was not installed on the Raspbian image which we flashed so had to install the VNC Server.

And then by going to Interfacing Options and enabling VNC From there.We then got the ip of our pi using the “ifconfig” command and then we used that ip and downloaded vnc viewer on our windows laptop and used that ip to connect to pi.
After configuring Rasbian and Vnc we started using it remotely from our laptop and we now proceed to our next step of installing Magic Mirror on our PI.
MagicMirror is a smart mirror platform that is open source. We followed the following procedure to install it

We Then Started configuring Magic Mirror to be suitable for education level. We edited the weather and then we changed the compliments message like the batch and room number. We then wanted our device to be smart so we installed Alexa and google assistant to our Pi.
We installed “Mmm Awesome Alexa” as it is open source and it is a hands free Alexa module for our Magic Mirror powered Pi. 

To Install Alexa on our device we followed 3 steps
Dependency installation
Module installation
Module configuration



