# UDP Queueing System

A lightweight **queueing system** written in **C** for Debian Linux.  
It uses **UDP sockets** for communication, **local storage** for data, and a **web frontend** for display.  
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

## ⚡ Installation (Backend)

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





