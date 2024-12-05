//
// Created by oscwa on 11.10.2024.
//

#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <Arduino.h>
#include "USBHost_t36.h"

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
KeyboardController keyboard1(myusb);
KeyboardController keyboard2(myusb);
USBHIDParser hid1(myusb);
USBHIDParser hid2(myusb);
USBHIDParser hid3(myusb);
USBHIDParser hid4(myusb);
USBHIDParser hid5(myusb);
MouseController mouse1(myusb);
JoystickController joystick1(myusb);
int user_axis[64];
uint32_t buttons_prev = 0;
RawHIDController rawhid1(myusb);
RawHIDController rawhid2(myusb, 0xffc90004);

USBDriver *drivers[] = {&hub1, &hub2, &joystick1, &hid1, &hid2, &hid3, &hid4, &hid5};
#define CNT_DEVICES (sizeof(drivers)/sizeof(drivers[0]))
const char *driver_names[CNT_DEVICES] = {"Hub1", "Hub2", "JOY1D", "HID1", "HID2", "HID3", "HID4", "HID5"};
bool driver_active[CNT_DEVICES] = {false, false, false, false};

// Let's also look at HID Input devices
USBHIDInput *hiddrivers[] = {&mouse1, &keyboard1, &keyboard2, &joystick1, &rawhid1, &rawhid2};
#define CNT_HIDDEVICES (sizeof(hiddrivers)/sizeof(hiddrivers[0]))
const char *hid_driver_names[CNT_DEVICES] = {"Mouse1", "KB1", "KB2", "Joystick1", "RawHid1", "RawHid2"};
bool hid_driver_active[CNT_DEVICES] = {false, false};
bool show_changed_only = false;

#define MAX_POINTS 100  // Maximum number of points

// Arrays to store x and y coordinates
int x_[MAX_POINTS];
int y_[MAX_POINTS];

// Variable to track the number of points added
int pointCount = 0;

// Function to add a point to the x and y arrays
void addPoint(const int x, const int y) {
    if (pointCount < MAX_POINTS) {
        x_[pointCount] = x;
        y_[pointCount] = y;
        pointCount++;
    } else {
        Serial.println("Max points reached, cannot add more points.");
    }
}

inline void mouseSetup() {
    myusb.begin(); // Initialize USB host
}

#endif //MOUSE_HPP
