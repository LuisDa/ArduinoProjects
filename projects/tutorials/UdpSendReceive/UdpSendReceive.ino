/*
  UDPSendReceive.pde:
 This sketch receives UDP message strings, prints them to the serial port
 and sends an "acknowledge" string back to the sender
 
 A Processing sketch is included at the end of file that can be used to send 
 and received messages for testing with a computer.
 
 created 21 Aug 2010
 by Michael Margolis
 
 Modified 10 Jan 2014 
 by Luis David Lopez-Roberts
 
 This code is in the public domain.
 */


#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
  
byte mac[] = {0x90, 0xA2, 0xDA, 0x0D, 0x6F, 0xA8 }; //Put MAC address of your Ethernet Board
IPAddress ip(192, 168, 1, 56); //This IP Address will be assigned if DHCP fails (IMPORTANT, you must put an IP within your network's range)
unsigned int localPort = 8888;      // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

/*This function cleans the receiver buffer*/
void cleanRxBuffer() {
 for (int i = 0; i < UDP_TX_PACKET_MAX_SIZE; i++) {
  packetBuffer[i]=0x00;
 } 
}


/*This function shows, via Serial Monitor, the local IP Address*/
void printLocalIp() {  
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
}

void setLocalIp() {
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP; assigning fixed IP");
    Ethernet.begin(mac,ip);
    // no point in carrying on, so do nothing forevermore:
    for(;;)
      ;
  } 
}

void setup() {
  // start the Ethernet and UDP:
  //Ethernet.begin(mac,ip);
  // start the Ethernet connection:
  setLocalIp();
  
  Udp.begin(localPort);

  Serial.begin(115200);
}

void loop() {
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();  
  
  if(packetSize)
  {
    // We show, via Serial Monitor, the remote IP and UDP port
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i =0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Serial.print("Contents: \"");
    Serial.print(packetBuffer);
    Serial.println("\""); 
    cleanRxBuffer();

    // send a reply, to the IP address and port that sent us the packet we received
    //delay(500); //If needed, put a small delay before sending reply
    
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
  
  // We show periodically, via Serial Monitor, the local IP Address (each 2 seconds).
  printLocalIp();
  delay(2000);

}
