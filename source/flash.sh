pio run -t upload -d esp-programmer
sleep 3
pio run -e clean -t erase -d esp
sleep 10
pio run -e whid  -t upload -d esp
pio run -t upload -d 32u4
