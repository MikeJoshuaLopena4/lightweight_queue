# UDP Queueing System

A lightweight **queueing system** written in **C** for Debian Linux.  
It uses **UDP sockets** for communication, **local storage** for data, and a **html frontend** for display.  
Designed for simplicity and kiosk environments.


## 📂 Project Structure
```
/backend
├── queue.tgz              # Contains server, client, websocketd, and /etc/shp/queue
├── printer                # Print handler (copy to /usr/local/bin/)
├── start-shp.sh           # Startup script for autorun
├── shp.service            # Systemd service for autorun

/frontend
└── queue.html             # Display screen for queue numbers

/firmware
├── cashier.ino            # ESP8266 firmware for cashier buttons
└── customer.ino           # ESP8266 firmware for customer buttons
```

## 🖥️ Kiosk Mode
```
wget https://raw.githubusercontent.com/MikeJoshuaLopena4/MJL_Debian-kiosk/main/deb-kiosk.sh
chmod +x deb-kiosk.sh
./deb-kiosk.sh
```

## ⚡Backend Setup

1. Extract backend files:
   ```bash
   sudo tar -xvzf queue.tgz -C /
2. Copy printer script:
   ```bash
   sudo cp printer /usr/local/bin/printer
2. Make all binaries executables:
   ```bash
   sudo chmod +x /usr/local/bin/server
   sudo chmod +x /usr/local/bin/client
   sudo chmod +x /usr/local/bin/websocketd
   sudo chmod +x /usr/local/etc/shp/queue
   sudo chmod +x /usr/local/bin/printer

## 🌐 Frontend Setup

1. Edit queue.html to point to your server’s IP address for example (192.168.10.101):
   ```bash
   QConnect('ws://localhost:81/queue');
   fetch("http://localhost:8080/print");
2. move the queue.html
   ```bash
   sudo mv queue.html /home/kiosk/queue.html
   
3. To test you can open in browser other pc that has same network (optional)
   ```bash
   file:///home/kiosk/queue.html

## 🔘 ESP8266 Firmware
1. cashier.ino → Upload to ESP8266 used by cashier to call next customer.
2. customer.ino → Upload to ESP8266 with two buttons (Regular / Priority).

## 🔄 Autorun Service
1. Move startup script
   ```bash
   sudo mv start-shp.sh /usr/local/bin/start-shp.sh
   sudo chmod +x /usr/local/bin/start-shp.sh
2. Move systemd service
   ```bash
   sudo mv shp.service /etc/systemd/system/shp.service
3. Enable & start service
   ```bash
   sudo systemctl daemon-reload
   sudo systemctl enable shp.service
   sudo systemctl start shp.service
3. Check status
   ```bash
   systemctl status shp.service

3. (Done)⚡
   ```bash
   reboot





   

