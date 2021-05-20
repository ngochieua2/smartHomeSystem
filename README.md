# smartHomeSystem

Smart Home System is a software allowing a controller can send queries and commands to various devices such as an light switch, thermostat and sprinkler system.
Controller can get information of devices as well as controll them. It is developed by Qt throught C++ language and use OOP and some design pattern.

## Design pattern:

* **Abstract Factory:** is use to create device objects depending device types such as: light switch, thermostat and sprinkler system
* **Proxy:** controller or devices will interact to proxy before proxy will update into real items. So, it makes system become simple.

## Class diagram:

![uml](https://res.cloudinary.com/ngochieua2/image/upload/v1621433338/github/UML_diagram-1_ojqvgn.png)

## Features:

### Controller:

Controller need to connect with any allowed devices throught their name, type and URL before controling them.
It allows users can find and select any registered devices and use their features.
Controller can also unregister with connected devices if unnecessary.

### Devices:

Afer select registered device in controller menu, it will move to specific device menu, so user can control it remotely.

#### Light switch:

User can turn on, turn off, reduce the brightness level, increase the brightness level and see the current information of that device.

#### Thermostat

With thermostat, user can get current temperature or 5 most recent temperature and control room's temperature become warmer or cooler

#### Sprinkler system

Sprinkler system can be turned on, turned off and scheduled by user to turn off automatically after a period time. Moreovers, it can measure water usage at a time and lifetime
of a sprinkler

## Extra information:

Exchanged information in system is a object named measurements. Depending on device types, measurements will story different information to interact between controller and devices. However, it will not interact directly between controller and devices. Instead, it controller will talk with device proxies, then they will update on real devices. Similerly, real devices will interact with controller proxy before controller proxy sends data to the real controller. Those processes can be present clearly in class diagram above
