# Copyright (c) 2024 Fundacion Sadosky, info@fundacionsadosky.org.ar
# Copyright (c) 2024 INVAP, open@invap.com.ar
# SPDX-License-Identifier: AGPL-3.0-or-later OR Fundacion-Sadosky-Commercial

import inspect

from rt_monitor.errors.component_errors import FunctionNotImplementedError
from rt_monitor.framework.components.component import Component


class adc(Component):
    def __init__(self):
        super().__init__()
        # self._adc_read = NoValue
        # statistics variables
        self.__total_values_read = 0
        self.__current_value = 0

    def state(self):
        # state = {"adc_read": ("Int", self._adc_read)}
        return {}  # state

    def adc_init(self):
        pass

    def sample(self):  #, read: np.uint16):
        # self._adc_read = read
        self.__total_values_read += 1
        #self.__current_value = read

    def get_status(self):
        return [self.__total_values_read, self.__current_value]

    # component exported methods
    exported_functions = {"adc_init": adc_init, "sample": sample}

    def stop(self):
        pass
