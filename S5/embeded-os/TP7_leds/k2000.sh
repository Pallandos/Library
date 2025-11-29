#!/usr/bin/env bash

LED1="heartbeat"
LED2="usr2"
LED3="usr3"
LED4="mmc0"

led_on(){
    echo 1 > beaglebone:green:"$1"/brightness
}

led_off(){
    echo 0 > beaglebone:green:"$1"/brightness
}

clicgnote(){
    local delay="${1:-0.5}" #delay in s

    led_on "$LED1"
    sleep "$delay"
    led_on "$LED2"
    sleep "$delay"
    led_off "$LED1"
    sleep "$delay"
    led_on "$LED3"
    sleep "$delay"
    led_off "$LED2"
    sleep "$delay"
    led_on "$LED4"
    sleep "$delay"
    led_off "$LED3"
    sleep "$delay"
    led_off "$LED4"
}

main(){
    # entry point

    while true; do
        clicgnote "$1"
    done
}

main "$@"