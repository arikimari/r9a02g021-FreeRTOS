# FreeRTOS for R9A02G021

This repository provides a port of [FreeRTOS](https://www.freertos.org/index.html)
for the Renesas R9A02G021 RISC-V Processor. It implements a simple
demo derived from the FreeRTOS "blinky" demo applications.


## Features

* Full FreeRTOS port
* Minimal boot code
* Own BSP (no dependencies for Renesas BSP)
* Support for both vectored and trap interrupt handling
* Support for UART trace
* Support for assert
* Support for exceptions


## How To Build

1. Clone this repository recursively (to include the submodules):

```bash
$ git clone --recurse-submodules https://github.com/akimari
```

2. Install Renesas RISC-V toolchain:

	https://llvm-gcc-renesas.com/riscv/riscv-download-toolchains/

3. Compile blinker application:

```bash
$ make
```

## Porting Details

The processor-specific FreeRTOS parts are configured by two files:

* `FreeRTOSConfig.h` (customize according to your needs)
* `freertos_risc_v_chip_specific_extensions.h`

