pio run -t upload -d esp-programmer
ping -n 3 127.0.0.1
pio run -e clean -t erase -d esp
ping -n 10 127.0.0.1
pio run -e whid  -t upload -d esp
pio run -t upload -d 32u4
