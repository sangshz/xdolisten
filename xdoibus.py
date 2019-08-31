#!/usr/bin/python
import warnings
warnings.filterwarnings("ignore")
#from gi import require_version as gi_require_version
#gi_require_version('IBus', '1.0')

from gi.repository.IBus import Bus
print Bus().current_input_context()
