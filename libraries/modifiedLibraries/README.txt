CHANGES PERFORMED:

*** Ethernet library ***
------------------------

- Modified function Ethernet.begin(mac) to be able to setup also the DHCP timeout and the response timeout. Now, when the IP is obtained via DHCP, you can call the function using some of these three ways:

  Ethernet.begin(mac); // In this case, the DHCP timeout will be 60000 milliseconds, and the response timeout, 4000 milliseconds (default values).
  Ethernet.begin(mac, timeout); //DHCP timeout will be the specified, the response timeout, 4000 milliseconds.
  Ethernet.begin(mac, timeout, responseTimeout); //DHCP timeout and response timeout will be the specified ones.

- Files affected:

  Ethernet/Ethernet.h
  Ethernet/Ethernet.cpp

- As it can be seen, the changes are completely backward compatible.

USED ARDUINO VERSION: 1.0.5.

=======================================================================================================================================================

Performed by Luis David López-Roberts Luzón (Luisda_LR in Arduino Forums). Should you have any doubt, do not hesitate contacting me via private message in the Arduino Forums or via email. My email addresses are these:

- ld1984ster@gmail.com
- luisdavid.lopezroberts.luzon@gmail.com


