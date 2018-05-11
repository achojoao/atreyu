#atreyu

<b>A</b>pplescript <b>TRE</b>llis ke<b>Y</b>board b<b>U</b>ddy

##What is it?

It's not a dragon, but it's white and it's your mate too.

It's a programmable 16 button keypad that helps you with common tasks in your day a day with your Mac.

##What is it made of?

###Hardware

- [Wemos D1 Mini](https://wiki.wemos.cc/products:d1:d1_mini) (The brain)
- [Trellis](https://learn.adafruit.com/adafruit-trellis-diy-open-source-led-keypad/overview) (The arms and legs)
- [3D printed case](https://www.thingiverse.com/thing:2630135) (The body)
- USB - Micro USB cable (The heart)

###Software

- [Mosquitto](https://mosquitto.org/)

##How it works?

###Running the mosquitto server


###Start atreyu

After configuring and starting mosquitto in your Mac, plug atreyu to any available USB port.

It tries to connect to your WiFi (you must set SSID and password previously in the arduino script) and then to the mosquitto server. The IP of your Mac must be setted in the arduino script too, but if it's dynamic, no problem, you can configure the last 4 cipher of it. Just press the last button when the connecting error animation displays, and it'll show a numpad where you can select the numbers of the IP of your Mac (i.e. 192.168.<b>2</b>.<b>134</b>).

###Pages

There are four available pages, selected by the four upper buttons. 

The other 12 buttons sends a message to the mosquitto server with its number depending the page selected (0 to 47).

After 60 seconds of idle, atreyu starts to play alone a random pattern. Press any button to wake it up.

When changin between apps in your mac, atreyu automatic changes the page assigned to it. You will notice this as a scrolling animaton in atreyu.

###Functionality

The below table shows the current configuration that the atreyu provides right out of the box. When a button is pressed, its value is published to the mosquitto server. The script, which is a subscriber of the same topic, executes the AppleScript correspondent to the button value. Usually, it's some key presses.


|  Button | Page0 | Page1 | Page2 | Page3 |
|---|---|---|---|---|
| 1 |   |   |   |   |
| 2 |   |   |   |   |
| 3 |   |   |   |   |
| 4 |   |   |   |   |
| 5 |   |   |   |   |
| 6 |   |   |   |   |
| 7 |   |   |   |   |
| 8 |   |   |   |   |
| 9 |   |   |   |   |
| 10 |   |   |   |   |
| 11 |   |   |   |   |
| 12 |   |   |   |   |

##Want a custom configuration?

If you have some knowledge in AppleScript, it's very easy to adapt the functionality. You just have to modify atreyu.sh to your requirements. All buttons are commented in the code. Here there are a couple of links that may be interesting:

- [AppleScript - The Language of Automation](https://macosxautomation.com/applescript/learn.html)
- [AppleScritp Key Codes](https://eastmanreference.com/complete-list-of-applescript-key-codes)
