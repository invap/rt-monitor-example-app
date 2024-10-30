# Example application for the Runtime Monitor

This project provides a simple C application serving as example for the use of the [Runtime Reporter](https://github.com/invap/rt-reporter.git "The Runtime Reporter") and the [Runtime Monitor](https://github.com/invap/rt-monitor.git "The Runtime Monitoring") in the runtime verification of a software system. The application implements the software layer of the hardware-software system shown in [Figure 1](#hardware-software-system).

<figure id="hardware-software-system" style="text-align: center;">
  <img src="./README_images/hardware-software-system.png" width="600" alt="A hardware-software system for displaying the magnitude of an analog signal.">
  <figcaption style="font-style: italic;"><b>Figure 1</b>: A hardware-software system for displaying the magnitude of an analog signal.
  </figcaption>
</figure>

The rationale of the system is that of a control loop (**Main control loop** in [Figure 1](#hardware-software-system)) that performs the following tasks:
1. reads digital data from an analog-digital converter (*ADC*) (from now on referred to as sample),
2. converts it to a floating point number (from now on, referred to as engineering value), and
3. displays it as a bar in an LCD akin the SSD1963 from Solomon Systech Limited (*LCD*).

The runtime verification attained with the runtime monitor is done at the software layer of the system in order to check the correctness[^correctness] of the software implementation with respect to an abstract specification of the process (see Section [Structured Sequential Processes](https://github.com/invap/rt-monitor/blob/main/README.md#structured-sequential-processes "Structured Sequential Processes") for a detailed presentation of the lenguage for describing structured sequential processes, the abstract labuage used for specifying software artifacts). 

The ADC and the LCD are operated through high level libraries (**ADC API** and **LCD API** in [Figure 1](#hardware-software-system), respectively, for reference) that are discussed in detail in Section [ADC implementation and operation](#adc-implementation-and-operation) and Section [LCD implementation and operation](#display-implementation-and-operation).

The project provides four implementations of the software level of the system (we will describe them in detail in Section [Implementations of the app](#implementations-of-the-app)), all sharing the same rationale and source code structure. Two of them use an implementation of the ADC with self logging capabilities, while the other two rely on the main program for logging the ADC behaviour.


## The software layer of the system as a structured sequential process
In this section we formalise the intended behaviour of the software layer of the system shown in [Figure 1](#hardware-software-system). [Figure 2](#ssp-software) provides a graphical depiction of the expected behaviour of the software layer of the hardware-software system shown in Figure 1 as a structured sequential process (SSP).

<figure id="ssp-software" style="text-align: center;">
  <img src="./README_images/ssp-software.png" width="600" alt="Specification of the software layer of the 
hardware-software system shown in Figure 1 as a structured sequential process.">
  <figcaption style="font-style: italic;"><b>Figure 2</b>: Specification of the software layer of the hardware-software system shown in Figure 1 as a structured sequential process.
  </figcaption>
</figure>

The intuition behind the SSP shown above is that after an initial task (*init*) that performs the initialization of the process, the artifact enters an infinite loop which performs a filtering task (*filtering*), which has an local checkpoint (*filtering_chk*), that computes a stable sample by taking the average of 16 individual samples, then the process goes through a conversion task (*conversion*) that produces the engineering value corresponding to that sample according to the interpretation of the analog signal being sampled, and, finally, there is a global checkpoint (*display_chk*) for checking the coherence of the data shown in the LCD with respect to the engineering value computed in the task *conversion*.

Below there is a list of the properties involved in the formal specification of [Figure 2](#ssp-software). We omit the information about the solver that will be used for checking each individual property but it can be seen as a label in fron of each of them in the structured sequential process of [Figure 2](#ssp-software). For a detailed presentation of the syntax the reader is pointed to Section [Specification language for describing the analysis framework](https://github.com/invap/rt-monitor/blob/main/README.md#specification-language "Specification language for describing the analysis framework").

- `init_vars`: asserts that the variable storing the previous sample is initialised with 0
```
(main_realvalue_old:State Int)
(= main_realvalue_old 0)
```
- `init_fondo_display`: asserts that the invariant part of the image shown in the display has been correctly written. **Important note**: this is a dummy property because it is too cumbersome and does not add much to the purpose of this example; we will complete this in the future with a proper formula
```
None
(= 1 1)
```
- `init_time_bound`: establishes a bound to the time required to perform the task *init*, between 10 and 1000 miliseconds
```
(init_clk:Clock Int)
((10 <= init_clk) & (init_clk < 1000))
```
- `filtering_pre`: states the precondition of the task *filtering* asserting that the variable in which the process computes the addition of the 16 samples has been assigned 0
```
(main_addition:State Int)
(= main_addition 0)
```
- `filtering_post`: states that the value reported as the result of computing the addition of 16 sampled datum and then deviding by 16 is indeed the average of those values
```
(main_addition:State Int),(main_realvalue:State Int),(main_value_0:State Int),(main_value_1:State Int),(main_value_2:State Int),(main_value_3:State Int),(main_value_4:State Int),(main_value_5:State Int),(main_value_6:State Int),(main_value_7:State Int),(main_value_8:State Int),(main_value_9:State Int),(main_value_10:State Int),(main_value_11:State Int),(main_value_12:State Int),(main_value_13:State Int),(main_value_14:State Int),(main_value_15:State Int)
(and
    (and
        (and (<= 0 main_value_0) (< main_value_0 4096))
        (and (<= 0 main_value_1) (< main_value_1 4096))
        (and (<= 0 main_value_2) (< main_value_2 4096))
        (and (<= 0 main_value_3) (< main_value_3 4096))
        (and (<= 0 main_value_4) (< main_value_4 4096))
        (and (<= 0 main_value_5) (< main_value_5 4096))
        (and (<= 0 main_value_6) (< main_value_6 4096))
        (and (<= 0 main_value_7) (< main_value_7 4096))
        (and (<= 0 main_value_8) (< main_value_8 4096))
        (and (<= 0 main_value_9) (< main_value_9 4096))
        (and (<= 0 main_value_10) (< main_value_10 4096))
        (and (<= 0 main_value_11) (< main_value_11 4096))
        (and (<= 0 main_value_12) (< main_value_12 4096))
        (and (<= 0 main_value_13) (< main_value_13 4096))
        (and (<= 0 main_value_14) (< main_value_14 4096))
        (and (<= 0 main_value_15) (< main_value_15 4096))
    )
    (= main_addition (+ main_value_0 main_value_1 main_value_2 main_value_3 main_value_4 main_value_5 main_value_6 main_value_7 main_value_8 main_value_9 main_value_10 main_value_11 main_value_12 main_value_13 main_value_14 main_value_15))
    (= main_realvalue (div main_addition 16))
)
```
- `filtering_time_bound`: establishes a bound to the time required to compute the the final sample as the average of 16 sampled datum from the ADC, between 100 and 500 miliseconds
```
(filtering_clk:Clock Int)
((100 <= filtering_clk) and (filtering_clk < 500))
```
- `12bitsreading`: asserts that the value read from the ADC is bound to an unsigned integers in the range [0, 4096), which is the integers that can be represented with 12 bits 
```
(adc_read:Component Int)
((0 <= adc_read) & (adc_read < 4096))
```
- `additionbound`: asserts that the partial addition performed until the moment in which this property is checked is necessarilly in hte range [0, 16*4096)
```
(main_addition:State Int)
((0 <= main_addition) and (main_addition < 16 * 4096))
```
- `conversion_pre`: asserts that the sample computed by task *filtering* is an unsigned integer value in the range [0, 4095)
```
(main_realvalue:State Int)
(and (<= 0 main_realvalue) (< main_realvalue 4096))
```
- `conversion_post`: asserts that the engineering value computed, as a floating point value, by task *conversion* correspond (upto a rounding error not representable in a single presition floating point) to the theoretical value resulting from the mathematical interpretation of the sample with respecto to the analog signal
```
(measurement_dato_ing:State Real),(main_realvalue:State Int),(measurement_dato_ing2:State Real)
(exists (
            (real_measurement_dato_ing Real)
            (real_measurement_dato_ing2 Real)
        )
        (and
            (let (
                    (abs_diff
                    (ite (< measurement_dato_ing real_measurement_dato_ing)
                         (- real_measurement_dato_ing measurement_dato_ing)
                         (- measurement_dato_ing real_measurement_dato_ing))
                    )
                 )
                 (< abs_diff (* real_measurement_dato_ing 0.00001))
            )
            (let (
                    (abs_diff
                    (ite (< measurement_dato_ing2 real_measurement_dato_ing2)
                         (- real_measurement_dato_ing2 measurement_dato_ing2)
                         (- measurement_dato_ing2 real_measurement_dato_ing2))
                    )
                 )
                 (< abs_diff (* real_measurement_dato_ing2 0.00001))
            )
            (= real_measurement_dato_ing (* 0.00524590164 main_realvalue))
            (= real_measurement_dato_ing2 (* (^ 1 -13) (^ 2.71828 (* 1.1231 measurement_dato_ing))))
        )
)

```
- `barpointiscorrect`: asserts that the topmost row of the bar that is colured in green (referred to as `bar_point') corresponds to the engineering value computed by task *conversion*, also establishing a hard upper and lower bound for that row
```
(bar_dato_ing:State Real),(bar_point:State Int)
(exists ((real_value Real))
        (let (
                (abs_diff
                (ite (< bar_dato_ing real_value)
                    (- real_value bar_dato_ing)
                    (- bar_dato_ing real_value))
                )
             )
             (and
                (< abs_diff (* real_value 0.00001))
                (=
                    bar_point
                    (ite (<= (- (* 24 real_value) 96) 0)
                        0
                        (ite (<= 383 (- (* 24 real_value) 96))
                            383
                            (to_int (- (* 24 real_value) 96))
                        )
                    )
                )
             )
        )
)
```
- `bariscorrect`: establishes that the rows of the bar that fall below or equal to the `bar_point` are coloured in green, and those that fall above are black
```
(bar_point:State Int),(pixels:Component (Array Int (Array Int (Array Int Int))))
(forall ((y Int) (x Int))
        (=>
            (and (>= y 155) (<= y 190))
            (and
                (=>
                    (and (<= x 413) (> x  (- 413 bar_point)))
                    (and
                        (= (select (select (select pixels x) y) 0) 0)
                        (= (select (select (select pixels x) y) 1) 255)
                        (= (select (select (select pixels x) y) 2) 0)
                    )
                )
                (=>
                    (and (>= x 2) (<= x (- 413 bar_point)))
                    (and
                        (= (select (select (select pixels x) y) 0) 0)
                        (= (select (select (select pixels x) y) 1) 0)
                        (= (select (select (select pixels x) y) 2) 0)
                    )
                )
            )
        )
)
```

Another aspect that has to be declared in the specification of the analysis framework is the components that will play a role for analysing the system. In this specific case study we analyse the behaviour of the system by considering that the implementation of the ADC and the LCD are is not monitored internally but only through the invocation of the functions in their interface. This requires us to declare which are the Python clases that providing implementations of the digital twins for both the [ADC](https://github.com/invap/rt-monitor/blob/main/framework/components/rt_monitor_example_app/ex_adc.py) and the [LCD](https://github.com/invap/rt-monitor/blob/main/framework/components/rt_monitor_example_app/ex_display.py). 

The complete specification of the analysis framework is provided as a [TOML file](https://github.com/invap/rt-monitor-example-app/blob/main/framework-working-copy/spec_gr.toml). For a complete explanation of the syntax se Section [Specification language for describing the analysis framework](https://github.com/invap/rt-monitor/blob/main/README.md#specification-language "Specification language for describing the analysis framework").


## ADC implementation and operation
In a proper implementation of the system, the software layer of the system shown in [Figure 1](#hardware-software-system) should implement the access to the register in which the ADC stores the sample after its computation but, as we mentioned in the introduction, this application constitutes only a case-study for exemplifying the use of the [Runtime Reporter](https://github.com/invap/rt-reporter.git "The Runtime Reporter") and the [Runtime Monitor](https://github.com/invap/rt-monitor.git "The Runtime Monitoring") for the runtime verification of a software artifact. Verification with hardware in the loop can be attained and is discussed in Section [Runtime verification with hardware in the loop](https://github.com/invap/rt-monitor/blob/main/README.md#runtime-verification-with-hardware-in-the-loop "Runtime verification with hardware in the loop") for a detailed description of the event language. In other words, we restrict ourselves to the analysis of the objects appearing in the upper-right quadrant delimited by red dotted lines of [Figure 1](#hardware-software-system) (i.e., the Software-Digital corner of the world). From this point of view, the analog digital converter is just the implementation of the machinary capable of generating 12 bits integer numbers. We provide two methods to accomplish this task:
1. data is generated by sampling a pseudo-random unsigned integer variable whose outcome is bounded to the range [0, 4096); successive samples do not differ in more than around 0.4%, obtained adding an integer, also resulting from sampling the pseudo-random unsigned integer variable whose outcome is shifted by 4 bits (i.e., adding an integer in the range (-16, 16)), and
2. data is read from a fixed file as one integer per line; the file has to be named "adc_info.csv" and placed in the working directory from where the reporting process is launched.

The generation method is chosen automatically depending on whether the file "adc_info.csv" is found in the working directory or not.

The project provides two implementations of the software library simulating the operation of the ADC:
1. [one providing self-logging capabilities](./data-source%20self%20loggable) which emits a file named "adc_log.csv". The "adc" part of the name is set as the second parameter passed to the instruction reporting a "self_loggable_component_log_init_event" event in the instruction: `report(self_loggable_component_log_init_event,"adc")` (the function `report` is implemented by the [C reporting API](https://github.com/invap/c-reporter-api.git)) and the part "_log.csv" of the name is added by the [Runtime Reporter](https://github.com/invap/rt-reporter.git "The Runtime Reporter") when it decodes the event type from the package received, and
2. [another](./data-source) that does not implement this capability and rely on the program using the component, for logging the ADC activity by resorting to *component function calls* (see Section [Event language](https://github.com/invap/rt-monitor/blob/main/README.md#event-language "Event language") for a detailed description of this type of events).

Both implementations have the same interface (see file "[ex_adc.h](https://github.com/invap/rt-monitor-example-app/blob/main/data-source/ex_adc.h)" or, equivalently, "[ex_adc.h](https://github.com/invap/rt-monitor-example-app/blob/main/data-source%20self%20loggable/ex_adc.h)"):
```
#ifndef ADC_H
#define ADC_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

// To discriminate whether adc data is read from file or generated
bool adc_info_present;
// For when adc data is read from file
FILE *file;
// For when adc data is generated
uint16_t previous_sample;

void adc_init (void);
int sample (void);

#endif
```
containing only two functions:
1. `adc_init`: initialises the data generation strategy by determining whether the file "adc_info.csv", containing data samples, is present in the working directory, or not. If the file is present: **a.** it is opened and the handler is stored in the file pointer variable `file`, and **b.** the boolean variable `adc_info_present` is set to `true`; if the file is not present, the pseudo-random number generator is initialised and the boolean variable `adc_info_present` is set to `false`, and 
2. `sample`: produces a sample as a 16 bits integer by, either reading it from the file handler stored in the file pointer variable `file`, whenever the booblean variable `adc_info_present` is set to `true`, or by generating a pseudo-random unsigned 16 bits integer value which is bound to be in the range [0, 4096). If the generation of data samples is done by reading from `file` and `EOF` is reached, then the process aborts exiting with error code `-1`.


## LCD implementation and operation
As we mentioned in Section [ADC implementation and operation](#adc-implementation-and-operation), a proper implementation of the system should implement the access the LCD by writing the appropriate data in memory locations where the communication bus is mapped. Once again, as we are only interested in the runtime verification of the software layer (shown in the upper-right quadrant delimited by red dotted lines of [Figure 1](#hardware-software-system)) and, as we are not concerned by the effect resulting from the invocation of the functions, we only provide a stub implementation of the interface "[ex_display.h](https://github.com/invap/rt-monitor-example-app/blob/main/data-display/ex_display.h)" shown below:
```
/*
 * This is a dummy implementation of a display
 * Its purpose is for the main application to compile and run.
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#include "rgb.h"

void display_rect(uint32_t HEIGHT, uint32_t WIDTH, uint32_t w, uint32_t h, const rgb* color);
void display_box(uint32_t HEIGHT, uint32_t WIDTH, uint32_t w, uint32_t h, const rgb* color);

void display_set_text_color(rgb color);
void display_set_text_bgcolor(rgb color);
void display_set_text_scale(uint8_t scale);
void display_set_text_pos(uint16_t HEIGHT, uint16_t WIDTH);
void display_set_text_pos2(uint16_t HEIGHT, uint16_t WIDTH);
void display_set_text_origin_position(uint16_t HEIGHT);
void display_write_text(const char* text);

void display_Show_RGB(unsigned char dat1,unsigned char dat2,unsigned char dat3, unsigned int HEIGHT0, unsigned int HEIGHT1, unsigned int WIDTH0, unsigned int WIDTH1);

#endif
``` 
The reader should note that the example proposes an interface providing high level capabilities for operating with the LCD. If we consider the hardware-software system proposed in [Figure 1](#hardware-software-system), in general, the low-level interface of the LCD hardware devices do not provide any capability for inspecting the state of the hardware component. This characteristic, shared with many other hardware components, is a key argument behind the addition of an event type for *component function calls* (see Section [Event language](https://github.com/invap/rt-monitor/blob/main/README.md#event-language "Event language") for further details), as it provides an effective connection between the operation of the component, part of the software under test and whose internal behaviour is not being verified, and a digital twin, used by the monitor for checking the properties of interest. In the case of the LCD of the present application, it is implemented in "[ex_display.py](https://github.com/invap/rt-monitor/blob/main/framework/components/rt_monitor_example_app/ex_display.py)"). For a more detailed explanation regarding the (black box) runtime verification of components see Section [Monitoring components](https://github.com/invap/rt-monitor/blob/main/README.md#monitoring-components).


## Implementations of the application
[Figure 3](#class-diagram) shows the architectural view of the implementation of the software layer implementation of the system shown in [Figure 1](#hardware-software-system).

<figure id="class-diagram" style="text-align: center;">
  <img src="./README_images/class-diagram.png" width="600" alt="The architectural view of the software layer implementation of the system shown in Figure 1.">
  <figcaption style="font-style: italic;"><b>Figure 3</b>: The architectural view of the software layer implementation of the system of in Figure 1.
  </figcaption>
</figure>

From a general point of view, the component `main` implements the infinite control loop (through function `main`) which, after taking some initial actions like initialising some variables, painting the background of the LCD (functions `background` of component `ex_display`), and initializing the ADC (function `adc_init` of component `ex_adc`), proceeds to subsequently compute the average of 16 samples, read from the ADC (through function `sample` of component `ex_adc`) and then write the engineering value corresponding to that computation in numbers in the lower section of the screen (through `measure` of component `ex_display`) and as a vertical bar (akin to a VU meter) in the central part of the LCD (through `bat` of component `ex_display`).

Below we provide an explanation of the different implementaions contained in this project. Notice that, as in the case of testing, the notion of *buggy* for the implementation experiencing bugs, and *patched* for the implementaion correcting them is relative to the formal properties we stated in the specification of the system we gave in Section [The software layer of the system as a structured sequential process](#the-software-layer-of-the-system-as-a-structured-sequential-process).

There are four different implementations of the application sketched above:
1. *buggy app*: contains an implementation experiencing a bug in the function `bar`, which displays the engineering value as a vertical bar. The bug is located in [line 136](https://github.com/invap/rt-monitor-example-app/blob/main/buggy%20app/functions.c#L136) where the instruction `for(signed int i = h+66 ; i > g+66 ; i--)` turns pixels off whenever the current engineering value is smaller than the previous one. There, it should iterate until `i >= g+66` in order to satisfy that the last row of pixels of the vertical bar that are painted in green, is the one corresponding to the current engineering value. 
Aditionally, the implementaion relies on implicitly enforcing an upper bound (code fragment from [line 106](https://github.com/invap/rt-monitor-example-app/blob/main/buggy%20app/functions.c#L106) to [line 134](https://github.com/invap/rt-monitor-example-app/blob/main/buggy%20app/functions.c#L134)) and a lower bound (code fragment from [line 136](https://github.com/invap/rt-monitor-example-app/blob/main/buggy%20app/functions.c#L136) to [line 145](https://github.com/invap/rt-monitor-example-app/blob/main/buggy%20app/functions.c#L145)) for the rows on the geometry of the bar, disregarding the conversion of the engineering value to a specific row in the geometry of the bar (i.e., [the value computed for the variable `g`](https://github.com/invap/rt-monitor-example-app/blob/main/buggy%20app/functions.c#L98)). Notice that even when this last observation does not manifest as a bug, checking the correctness of the implementation according to the behaviour prescribed by the specification requires to predicate about the appropriateness of the value computed for `g` with respecto to the engineering value, and the shape of the bar which would fail the value of `g` is not explicitly boung the the intende geometry of the bar.
2. *patched app*: contains an implementation correcting both problems explained above. See code fragment from [line 142](https://github.com/invap/rt-monitor-example-app/blob/main/buggy%20app/functions.c#L142) to [line 145](https://github.com/invap/rt-monitor-example-app/blob/main/buggy%20app/functions.c#L145) and [line 98](https://github.com/invap/rt-monitor-example-app/blob/main/buggy%20app/functions.c#L98) to [line 105](https://github.com/invap/rt-monitor-example-app/blob/main/buggy%20app/functions.c#L105).


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

---

[^correctness]: In this context, the word correctness is used in a colloquial way and must not be mistaken with its metalogical meaning used to characterise logical systems.

