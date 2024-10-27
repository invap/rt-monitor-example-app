# Example application for the Runtime Monitor

## Description of the contents of the project
This project provides a simple application serving as example for the 
[Runtime Monitor](https://github.com/invap/rt-monitor.git "A Runtime Monitoring tool"). The rationale of the app 
is that it implements the software layer of the hardware-software system for displaying the magnitude of an analog 
signal read from a sensor, shown below:
<figure 
  style="text-align: center;">
  <img 
    src="./README_images/hardware-software-system.png" 
    alt="A hardware-software system for displaying the magnitude of an analog signal."
  >
  <figcaption 
     style="font-style: italic;">*Figure 1: A hardware-software system for displaying the magnitude of an analog 
signal.*
  </figcaption>
</figure>

The rationale of the system is that of a control loop that performs the following tasks:
1. reads a digital data from a simulated analog-digital converter (*ADC*) (from now on referred to as sample),
2. converts the sample to a floating point number (from now on, referred to as engineering value), and
3. displays that engineering value as a bar in a dummy LCD akin the SSD1963 from Solomon Systech Limited (*LCD*).

The *ADC* is used through a library (ADC API in ) containing only two functions, *adc_init* for initialising the 
data generation strategy, and *sample* for acquiring a sample as a 16 bits integer (go to the 
[ADC section](#ADC implementation and operation) for more details). The *LCD* is operated through a high level 
interface providing more specific capabilities for setting writing positions, writing text, drawing rectangles or 
painting pixels with a specific color (go to the [LCD section](#LCD implementation and operation) for more details). 

There are four implementation of the application (we will describe them in detail in 
[Implementations section](#Implementations of the app)), all sharing the same rationale, structure and mission. 
From a general point of view, the main program implements the infinite control loop which, after taking some 
initial actions like initialising some variables, painting the background of the display, and initializing the ADC, 
proceeds to subsequently compute the average of 16 samples, read from the ADC and then write the engineering value 
corresponding to that computation in numbers (lower section of the screen) and as a vertical bar (akin to a VU 
meter) in the central part of the LCD.

## ADC implementation and operation
In a proper implementation of the system, these functions would access the hardware through a register mapped to a specific memory position.

## Display implementation and operation

## Implementations of the app
There are four different implementations of the application sketched in the previous section:
1. *buggy app*: contains an implementation experiencing a bug in the function that displays the engineering value by colouring the bits of the bar to cover the difference between the current engineering value and the previous one, if the current engineering value is greater that the previous one, or turning black the excess of coloured bits if the current engineering value is smaller than the previous one.
2. *patched app*:


## License

Copyright (c) 2024 INVAP

Copyright (c) 2024 Fundacion Sadosky

This software is licensed under the Affero General Public License (AGPL) v3. If you use this software in a non-profit context, you can use the AGPL v3 license.

If you want to include this software in a paid product or service, you must negotiate a commercial license with us.

### Benefits of dual licensing:

It allows organizations to use the software for free for non-commercial purposes.

It provides a commercial option for organizations that want to include the software in a paid product or service.

It ensures that the software remains open source and available to everyone.

### Differences between the licenses:

The AGPL v3 license requires that any modifications or derivative works be released under the same license.

The commercial license does not require that modifications or derivative works be released under the same license, but it may include additional terms and conditions.

### How to access and use the licenses:

The AGPL v3 license is available for free on our website.

The commercial license can be obtained by contacting us at info@fundacionsadosky.org.ar

### How to contribute to the free open source version:

Contributions to the free version can be submitted through GitHub.
You shall sign a DCO (Developer Certificate of Origin) for each submission from all the members of your organization. The OCD will be an option during submission at GitHub.

### How to purchase the proprietary version:

The proprietary version can be purchased by contacting us at info@fundacionsadosky.org.ar
