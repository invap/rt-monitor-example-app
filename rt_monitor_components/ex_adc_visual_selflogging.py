# Copyright (c) 2024 Fundacion Sadosky, info@fundacionsadosky.org.ar
# Copyright (c) 2024 INVAP, open@invap.com.ar
# SPDX-License-Identifier: AGPL-3.0-or-later OR Fundacion-Sadosky-Commercial

from rt_monitor.framework.components.component import SelfLoggingComponent
from rt_monitor.framework.components.new_rt_monitor_example_app.ex_adcVisual import adcVisual


class adc(SelfLoggingComponent):
    def __init__(self):
        super().__init__()
        # statistics variables
        self.__total_values_read = 0
        self.__current_value = 0
        # Initializes the visual feature of the class
        self.__visual = adcVisual(self)

    def state(self):
        return {}  # state

    def adc_init(self):
        pass

    def sample(self):
        self.__total_values_read += 1

    def get_status(self):
        return [self.__total_values_read, self.__current_value]

    # component exported methods
    exported_functions = {"adc_init": adc_init, "sample": sample}

    def process_log(self, log_file, mark):
        current_pos = log_file.tell()
        line = log_file.readline()
        while line:
            split_line = line.strip().split(",")
            if mark <= int(split_line[0]):
                break
            self._process_event(split_line[1:])
            current_pos = log_file.tell()
            line = log_file.readline()
        log_file.seek(current_pos)

    def _process_event(self, event):
        self.__total_values_read += 1
        self.__current_value = int(event[0])
