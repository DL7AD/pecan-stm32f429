# Software for Pecan Balloon Trackers

This is the software, which runs the [Pecan Pico 7 balloon trackers](https://github.com/DL7AD/pecanpico7). Currently this software if unfinished but basic features can be used:

- Image capturing (just QVGA at the moment) and transmission by SSDV
- Receiving positions (by ublox MAX8 module)
- Measuring Temperature/Airpressure/Temperature (by onboard BME280)
- Measuring external Temperature/Airpressure/Temperature (by external BME280)
- Measuring power consumption (battery charging and discharging)
- Position and telemetry transmissions by 2FSK (or RTTY)
- High altitude mode (up to 50km altitude)
- Debugging (serial connection)
- APRS encoding (AFSK)

What currently doesn't work at the moment (but planned):

- APRS encoding (2GFSK)
- High resolution image capturing (just QVGA at the moment)
- High resolution image transmissions by 9k6 APRS
- Logging and Log transmissions
- Amateur satellite orbit calculations and transmissions
- Power save modes
- Store data on the microSD card
- 9-axsis sensor driver (MPU9250)

Not planned:

- Video capturing (because the hardware doesn't have that much calculation power for compression encoding)

The following part describes in which function parts the software is divided and how they interact which each other.

Modules
=======
The software provides multiple modules, which supply the main functionality of the tracker like transmitting positions or images. Modules are basically threads in the ChibiOS RTOS. Modules can be:

- POSITION - for transmining position and telemetry
- IMAGE - for transmitting images
- LOG - for transmitting logs

There are two more specific modules which are started automatically be the software itself. They are necessary to do input/output jobs.
- TRACKING (or tracking manager) - collects all the data from the peripheral components (BME280, GPS, etc.) and provides them (as struct) to other modules in the software.
- RADIO - provides the two radios which are available. This module receives internal messages by other modules which want to send packets via VHF or UHF.

The following diagram shows how the modules interact with each other.

```
   DRIVER   |                  DATA PROCESSING MODULES                     |     DRIVER
------------+--------------------------------------------------------------+------------------

MPU9250 --+                           +---> SATELLITE ---+
          |                           |                  |
BME280 ---+---> TRACKING Manager -----+---> POSITION ----+------> RADIO ---+---> RADIO1 (2m)
          |                           |                  |                 |
MAX ------+                           +-----> LOG -------+                 +---> RADIO2 (70cm)
                                                         |
OV9655 or ---------------------------------> IMAGE ------+
OV2640
```

Module configuration
--------------------
In order to use these modules, they can be configured operational in the MOULDES() macro in the [configuration file](blob/master/config.h). All modules can be configured except of TRACKING and RADIO. They must not be configured because they are launched by the software automatically. The following example shows how a image module and a position module can be configured.
```
MODULES() { \
    MODULE_IMAGE   (TX_CONTINUOSLY,          SLEEP_WHEN_BATT_BELOW_3V5, CUSTOM_FREQ, 10, PROT_SSDV_2FSK ); \
    MODULE_POSITION(WAIT_FOR_TRACKING_POINT, SLEEP_WHEN_BATT_BELOW_3V0, CUSTOM_FREQ, 10, PROT_UKHAS_2FSK); \
}
```
As you can see, there are some parameters which can be used to configure a specific module:

**Parameter 1** specifies in which cycle the modules shall send it's data. This may be an amount of seconds. It's also allowed to place *TX_CONTINUOSLY* or *WAIT_FOR_TRACKING_POINT* in this field.<br>
*TX_CONTINUOSLY* - Transmit new data once the old it sent completely<br>
*WAIT_FOR_TRACKING_POINT* - Transmit when tracking manager generates a new track point<br>
**Parameter 2** specifies the sleep mode. Note this functionality is currently not implemented. The modules will disregard this field.<br>
**Parameter 3** specifies a frequency method. Currently *CUSTOM_FREQ* or *APRS_REGION_FREQ* can be used. The frequencies are currently static and set in [radio.c](blob/master/radio.c). *CUSTOM_FREQ* is set to 434.500MHz and *APRS_REGION_FREQ* is set to 144.800MHz. It's planned to implement a geofencing algorithm in the future for *APRS_REGION_FREQ* in order to find out the specific APRS region frequency by the actual location.<br>
**Parameter 4** specifies the transmission power in dBm. If the value is set to a point which the radio is unable to do (or damaging the PCB) the actual value may be limited by the RADIO module.<br>
**Parameter 5** specifies the protocol and modulation. While you can use *PROT_UKHAS_2FSK*, *PROT_APRS_AFSK* or *PROT_RAW_CW* for the POSITION module the IMAGE module can only accept *PROT_SSDV_2FSK* at the moment.

Note not all of the parameter call be used for all individual modules because some configurations may not make sense e.g. CW modulation for transmitting images. You can find an exact documentation in the [configuration file](blob/master/config.h) which specific parameters can be applied to the the modules.

Multiple use of modules
-----------------------
Modules can be combined various combination. But modules can be also understand as classes which instances can be used multiple times. So if you want to transmit telemetry and positions by RTTY and APRS at the same time, you may configure modules multiple times. The following example shows, how the position/telemetry is sent on a custon frequency while it's also transmitted by APRS on the regional APRS frequency and CW.
```
MODULES() { \
    MODULE_POSITION (WAIT_FOR_TRACKING_POINT, SLEEP_WHEN_BATT_BELOW_2V5, CUSTOM_FREQ,      10, PROT_UKHAS_2FSK); \
    MODULE_POSITION (WAIT_FOR_TRACKING_POINT, SLEEP_WHEN_BATT_BELOW_2V5, APRS_REGION_FREQ, 10, PROT_APRS_AFSK ); \
    MODULE_POSITION (WAIT_FOR_TRACKING_POINT, SLEEP_WHEN_BATT_BELOW_3V0,CUSTOM_FREQ,       10, PROT_RAW_CW    ); \
}
```

Module TRACKING (or tracking manager)
-------------------------------------
The tracking manager keeps an eye on all peripheral components which provide data. With exception of the camera, the tracking manager collects the data of:
- BME280 (airpressure, humidity, temperature)
- MAX7/8 (GPS/GLONASS receiver)
- PAC1720 (Power consumption tracking)
The data of these components will be collected in a specific cycle time and provided to other modules in a struct [trackPoint_t](blob/master/modules/tracking.h). The most recent sampled data can be accessed by other modules by [getLastTrackPoint()](blob/master/modules/tracking.h).

Module RADIO
------------
The module RADIO handles the two radios which are available on the Pecan Pico 7. It initializes a mailbox in which messages (or data packets) can be written by other functions in order to use the radios. If a module wants to send a packet on HF, it may generate a [radioMSG_t](blob/master/modules/radio.h) struct and pass is over to [transmitOnRadio()](blob/master/modules/radio.h). The radio will determine a suitable radio by the frequency which is set in the struct. Once the radio is not used, the module will send the message. If the radio is already in use, the RADIO module may buffer up to 3 more messages in a message queue. The queue is cleared by the FIFO concept. While only 3 messages can be stored in the queue, the maximum generation-transmission delay is quiet small (<15sec usually). [transmitOnRadio()](blob/master/modules/radio.h) may return *true* if the message is sent to the queue. *False* indicates the queue is full. If a module wants to send the message, it has to try again by calling transmitOnRadio() again. While there is no priority management at the moment, the modules have to try more or less aggressivly to insert its messages to the radio queue. This strategy more a workaround than a solution. Priority management would be better.


Included software
=================
This software includes some other packages which I have used to make this project possible:

[JPEG Ant - JPEG compression for microcontrollers](https://sourceforge.net/projects/jpegant.berlios/)<br>
[ChibiOS - Real time operating system](http://chibios.org) ([Source](https://github.com/ChibiOS/ChibiOS))
