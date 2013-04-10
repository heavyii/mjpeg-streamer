#/bin/sh

export LD_LIBRARY_PATH="$(pwd)"
./mjpg_streamer -i "./input_uvc.so -r 1024x786 -f 15" -o "./output_udp.so -I 192.168.14.90 -p 32000"
