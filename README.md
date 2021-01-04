# Sailing Wind Sensor

This project contains the code and designed for a long arm sailing wind sensor. Standard wind sensors are fine for most sails but they fail to acurately measure wind angle down wind where they are in the flow of the air from the mainsail. This is partically bad where the mainsail has a large flat top. (Class40, Pogo1250, etc). The solution is to put the windsensor on a 1m-1.8m carbon mast above the masthead. Commercially these sensors start at 1K GBP and for 1.8m sensors expect to pay 4K GBP. Hence this project attempts to create a wind sensor using opensource components.

Construction
The housing is 3D printed in ABS. The mast is laminated in carbon fibre. 

Communications
Raymarine uses a 2 axis hall device generating sin/cos voltages and a pulse for speed. The circuit is complex, large and suceptable to errors in the voltages due to the length of wire run and poor connections. For that reason, although I currently have a Raymarine wind sensor I decided not to duplicate.

The device will communicates with RF using a Beken BK2491 chipset configured in the form a a JDY-40 runing at 2Mb/s bursting a serial stream at 9600 baud.

https://www.mikrocontroller.net/attachment/381910/BT-WiFi-52rf5541.pdf
https://www.electrodragon.com/w/images/0/05/EY-40_English_manual.pdf

The data sent over RF has 2 forms running at between 5-10Hz, both comma seperated values with a CRC16 checksum.


The protocol is proprietary and compact. A single line of csv readings without interpretation including the reading from the possition sensor 12bit representing 0-360 and the number of nano seconds for half a revolution (64bit).

* Masthead micro controller - Ardiono Pro Mini (18mmx33mm, 8MHz, 3.3v), consuming 30mA @5v
* Angular sensor - AS5600 12bit i2C device sensing a diametrically magnatised magnet
* Speed sensor - 3144 Hall switch sensing 2 magnets on a shaft triggering interrupts.
* JDY-40 - 2.4GHz RF module running at 9600 baud bursting over a 2Mb/s wifi channel.



Measurements.

The measurements including writing to the serial take 4ms to complete. Resolution of the AS5600 is 0.1 degrees. The code measures the pulse period directly since at low speed counting pulses is inacurage. Slowest speed is 1 revolution every 64s which is 0.01Kn. Highest is probably limimited mechanically but is well over 100kn (tested with a drill driving the shaft)

Calibration Curve for AS5600, depends completly on the hardware setup.

        0,709,69,2070
        10,822,69,2078
        20,939,69,2083
        30,1049,69,2086
        40,1167,69,2090
        50,1283,69,2092
        60,1396,69,2098
        70,1512,69,2104
        80,1625,69,2110
        90,1736,69,2117
        100,1853,69,2117
        110,1964,69,2113
        120,2082,69,2112
        130,2196,69,2126
        140,2308,69,2122
        150,2423,69,2117
        160,2536,69,2120
        170,2649,69,2122
        180,2762,69,2119
        190,2874,69,2112
        200,2987,67,2106
        210,3103,67,2096
        220,3216,67,2087
        230,3326,67,2081
        240,3438.67.2086
        250,3549,67,2079
        260,3661,67,2062
        270,3776,67,2057
        280,2883,67,2054
        290,3997,69,2077
        300,14,69,2075
        290,4000,69,2081
        295,4054,69,2078
        298,5092,69,2076
        300,18,69,2078
        310,127,69,2063
        320,244,69,2054
        330,358,69,2053
        340,475,69,2056
        350,590,69,2061
        0,702,69,2070
        64,1439,,
        334,406,,
        253,3586,,
        93,1778,,
        301,57,,
        127,2188,,
        32,1097,,
        287,3982,,

Conversion to degrees is 360*(m-offset)/4096. Average error is 0.3 degrees,
There appears to be a sinusoidal error associated with magnet offset, although this is not large enough to be
of concern or to both fixing. Just as likely to be a measurement error.

Conversion and linearisation will be done in the base station, not in the masthead sensor.

Problems encountered

FLoating dir pin on the AS5600 causes erratic readings.
AGC of 50-70 and Flux magnitude of 2000+ gives very stable readings, magnet is a 6mmx4mm Samarium Cobalt Magnet magnet with 0.3kg pull https://www.magnetexpert.com/magnet-materials-standard-assemblies-c150/6mm-dia-x-4mm-thick-diametrically-magnetised-samarium-cobalt-magnet-0-3kg-pull-p3517



The 3144 needs magnets to pass 1mm or less from the surface using 3mmx1mm N35 Neodymium magnet with 0.13kg pull (using 2x)

https://www.magnetexpert.com/magnet-materials-standard-assemblies-c150/3mm-dia-x-1mm-thick-n35-neodymium-magnet-0-13kg-pull-p6201 


Initial attempts to use RS-485 and RS-422 failed due to current consumption runnng the drivers exceeding the output available from the Pro Mini. Also managed to blow multiple Pro Mini's and 1 AS5600 when testing with long wires. the JDY-40 appears to have at least 50m range though walls and metal roofs with minimal data corruption.
