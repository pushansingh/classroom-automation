# classroom-automation
This project is made to construct a “School Automation System” using [Raspberry Pi](https://www.raspberrypi.org/) and [Arduino](https://www.arduino.cc/) modules.
Our main objective for this project was to develop a home/class automation system using an [Arduino](https://www.arduino.cc/) compatible board for Educational Institutes and for Smart Homes. As technology is advancing so our education System needs to get smarter too. A number of technologies that we are using currently in smart homes can be used to meet a number of requirements. By making these innovations in homes and classrooms can remove the need for care and award autonomy to the individuals who may be more focused on giving out productivity. This paper aims to discuss home automation systems for School and University Level by using AI and device control with IOT systems.
This project is made to construct a “School Automation System” using [Raspberry Pi](https://www.raspberrypi.org/) and [Arduino](https://www.arduino.cc/) modules. [Raspberry Pi](https://www.raspberrypi.org/) is a computer on a board. [Raspberry Pi](https://www.raspberrypi.org/) uses a large number of peripherals. It enables the simultaneous monitoring of the number of home appliances. Local server on [Raspberry Pi](https://www.raspberrypi.org/) is made to achieve this. Users can use a variety of mobile devices, such as smartphones, laptops and tablets to use a user interface on the web. Our target is to make a system where the user isn't required any touch feedback to do this thing so that even a blind person or a dumb person can use it. He can simply do this by telling the system what to do and this small device does the required thing.

**Proposed Product**
We have proposed a product for classroom automation both in Universities and Schools and Homes. To do this we have divided our model into two parts i.e. Base control and AI deployment part. By combining these two parts we can have a seamless integration of our system in classrooms and in homes without disrupting the normal workflow or the existing hardware.

The two parts of our project can be explained as follows:-

**Base Control**
In this part we use an IOT device to control an array of relay switches which turn on and off the existing switches in a given room this device is also used to turn on and of certain devices that may be crucial to the working of a classroom such as projector and AC etc we can also use this for television etc in an home scenario. In our proposed model we are using an ESP8266 wifi module commonly known as a NODEMCU device. This is an IOT device which can interact with wifi and take commands wirelessly. We pair this with a 4 bit relay array board with Octocoupler to control the AC appliances. Both of these combined make our Base control module. In the code we have also provided provisions for temperature control and we can also set this up with a number of sensors to provide “real time data” of the rooms “temperature and humidity”. More on the underlying technology can be found in the apparatus part.


**AI Deployment**
In this part we have used an arm board computer to run and install a linux distribution to make our own GUI to use along with two of the most popular and advanced AI assistants which are the Amazon Alexa and Google Assistant. By default these assistants do not come with a GUI but we can build one with the help of open source repositories for linux. We also customized this GUI to show valuable information such as class time and duration. Google calendar integration to give updates and reminders about upcoming lectures. We have also used an open source weather API to show real time weather. To do all this we used a [Raspberry Pi](https://www.raspberrypi.org/) model B+ board as our arm computer. With a USB microphone and a speaker for interaction with the AI assistant we also used a 7 inch TFT panel to display the GUI. We used this platform for prototyping but we can also use a [Raspberry Pi](https://www.raspberrypi.org/) zero which is a cheaper alternative but it can meet our needs with no compromise. For the OS we chose Raspbian GUI because it is the least resource consuming OS giving us the headroom to build on it. To build a custom GUI we used an open source repository on linux named MagicMirror2 after trying similar repositories. After the setup of this we had our AI deployment program complete. More on the underlying technology can be found in the AI Deployment part.


SYSTEM DESIGN

[**1. Raspberry Pi**](https://www.raspberrypi.org/)
The “[Raspberry Pi](https://www.raspberrypi.org/)” is a small computer developed in the UK by the “[Raspberry Pi](https://www.raspberrypi.org/) Foundation” with the intention of promoting the teaching of basic computer science in education institutes They develop free resources to help people learn about computing and how to make things with computers. [Raspberry Pi](https://www.raspberrypi.org/) began in 2006. It is affordable and used in many IoT Projects





[Raspberry Pi](https://www.raspberrypi.org/) Specifications (b) [Raspberry Pi](https://www.raspberrypi.org/) 3B+ Diagram (c) Working of [Raspberry Pi](https://www.raspberrypi.org/) (d) [Raspberry Pi](https://www.raspberrypi.org/) 3B+

 2. Relay
Relay is an electromagnetic switch. Relay permits one circuit to switch another circuit while they are separated. Relay is used when we have a device that requires a high voltage to function and we have a low voltage circuit.. For example, 5V relay connection supply to power the bulb on 230V AC power is sufficient. Relays can be used in different operating voltage configurations such as 6V, 9V, 12V or 24V, etc.. The relay consists of two parts, one of which is the input and another is the output. The input side of the relay is a magnetic field  when it receives a small voltage. Relays have three contactors: normally open (NC) and common (COM). Electrical appliances may turn on or off using the correct combinations of contactors.. 


3. NodeMCU
“NodeMCU” is an open source IoT platform. The name "NodeMCU" combines "node" and "MCU" (micro-controller unit). It runs on the “ESP8266” Wi-Fi SoC and hardware which was based on the “ESP-12” module Both the firmware and prototyping board designs are open source. It costs just 5$ making it an optimal choice for a low cost automation system. NodeMCU provides access to the GPIO 

  
NodeMCU
ESP8266
The “ESP8266” is a cheap “Wi-Fi” microchip, with a full stack TCP/IP. It Features a microcontroller capability, produced by “Espressif Systems” in Shanghai. This small module allows microcontrollers to connect to a Wi-Fi network and make simple TCP/IP connections using “Hayes-style” commands. This Microchip is very cheap and it has 16 GPIO pins. This microchip packs “IEEE 802.11 b/g/n Wi-Fi”. It supports WEP, WPA/WPA2 authentication and open networks
