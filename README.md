# GD32VF103 Bare-Metal "Hello, World"

This is a handful of template bare-metal programs for the GD32VF103CB RISC-V microcontroller. These look like fun chips because their peripherals are very similar to those found on the well-understood STM32F103 workhorse, but they have a shiny new RISC-V CPU core which is 50% faster and apparently more power efficient. So while RISC-V is a fairly young architecture, there is still plenty of example code demonstrating how to work with these peripherals, which should make it easier to get started.

They are written for a "Longan Nano" board, which you can buy from Seeed Studios for a little less than $5 each at the time of writing:

[Seeed Studio's Longan Nano Page](https://www.seeedstudio.com/Sipeed-Longan-Nano-RISC-V-GD32VF103CBT6-Development-Board-p-4205.html)

These boards include a common-anode RGB LED, with the cathodes connected to pins `C13` (Red), `A1` (Green), and `A2` (Blue). Since the pins are connected to the cathodes instead of the anodes, writing a `0` turns an LED on and writing a `1` turns it off. You can find more information about how the board is wired in its schematic:

[Longan Nano Schematics](http://dl.sipeed.com/LONGAN/Nano/HDK/Longan%20Nano%202663/Longan%20nano%202663(Schematic).pdf)

They also have a 160x80-pixel `ST7735` TFT display wired to one of its `SPI` peripherals, which is a nice little extra. It seems to use the same sort of command set as `ILI9341` and `ILI9361C` displays.

# Compiler Toolchain

The GD32VF1 family of chips have a 32-bit RISC-V CPU core with integer multiplication instructions, but no floating-point unit. This is conceptually similar to the ARM Cortex-M3 CPU core which is found in the STM32F1 microcontrollers which...inspired...these chips.

So to build this project, you'll need to build an appropriate GCC toolchain. You can use the RISC-V GCC port configured for an `rv32im` architecture:

[RISC-V GNU toolchain](https://github.com/riscv/riscv-gnu-toolchain)

A basic set of build commands would look something like this:

```
git clone --recursive https://github.com/riscv/riscv-gnu-toolchain
cd riscv-gnu-toolchain
mkdir build
cd build
../configure --with-arch=rv32im --prefix=[install directory]
make
```

You might need to install a few dependencies such as the `bison`, `flex`, and `texinfo` packages. If you're missing any, the `make` or `configure` commands will print out errors telling you what to install. There's also a list under the 'Prerequisites' section of the toolchain's Readme.

Also, the `--prefix` argument is optional; it lets you specity an install directory, like `/opt/riscv-gcc` or `/home/user/riscv-gcc`. This makes it easier to uninstall later, but it also means that you'll need to add `[install directory]/bin` to your `PATH` environment variable in order to run programs like `riscv32-unknown-elf-gcc`.

Finally, this build process will probably take a little bit of time, and it requires a little more than 10GB of free disk space. The `make` command will both build and install the toolchain, so depending on where you want to install it, you might be prompted to run `sudo make`. Once everything is done, you might need to run `sudo ldconfig` or restart your machine before you can run the installed programs normally, but you should be able to delete the build files under your `riscv-gnu-toolchain/build` directory if you need to free up disk space afterwards.

# Project Organization

The `common/` directory contains code that is shared by all of the projects, and the `hello_blah` directories contain the actual application code and a Makefile for each example.

* `hello_riscv` is a minimal example to test whether your build / program / debug toolchain is working.

* `hello_led` toggles the board's RGB LEDs.

* `hello_systick` toggles the board's RGB LEDs every second, using the CPU's timer interrupt as a source of time.

* `hello_display` configures the chip's SPI and DMA peripherals to draw to the board's display, and cycles through a few different patterns.

The `common/gd32vf103xb_boot.S` file contains the interrupt vector table and the `reset_handler` assembly function. I've been trying to put all of my code into `.c` files lately, but the `CLIC` interrupt system which these chips use might not be built into the universal RISC-V toolchain yet. So while the `csrw CSR_MTVT a0` assembly command is valid, the `__asm__( "csrw CSR_MTVT a0" );` line of C code causes an 'unrecognized CSR' compiler error. Weird.

The `common/device_headers/gd32vf103.h` file is hand-written with a few peripheral memory definitions taken from the GD32VF1 reference manual, but it is not comprehensive. I named the definitions to match those found in STM32F1 device header files; the peripherals are very similar, so I'm hoping to start putting together a header file which allows identical driver code to be used for STM32F103 and GD32VF103 chips wherever possible. But it might also be a little bit confusing, because the GD32 peripherals are 0-indexed while the STM32 ones are 1-indexed. So what I call `SPI1` is called `SPI0` in the GD32 reference material. Life isn't perfect.

Some configuration files, such as the OpenOCD files and the RISC-V equivalent of CMSIS headers, are from the GD32VF103 Firmware Library which you can find here:

[GD32VF103 Firmware Library](https://github.com/riscv-mcu/GD32VF103_Firmware_Library)

You can run `openocd -f openocd/openocd_ft2232.cfg` to open a debugging connection using the ["Sipeed" USB/JTAG dongles which Seeed Studio sells alongside these boards](https://www.seeedstudio.com/Sipeed-USB-JTAG-TTL-RISC-V-Debugger-p-2910.html), but I had to comment out the `ftdi_device_desc` setting to get OpenOCD to recognize mine. You'll also need to use a patched version of OpenOCD which can connect to and flash GD32VF103 chips:

[GD32VF103-compatible RISC-V OpenOCD Fork](https://github.com/riscv-mcu/riscv-openocd)

# Interrupts

The `GD32VF103` has two options for handling interrupts: "vectored" and "non-vectored". The "vectored" option looks up an interrupt's memory address in the vector table and jumps directly to it, while the "non-vectored" option causes all interrupts to trigger a common "trap handler" which calls the appropriate interrupt handler function.

The standard firmware library uses the "non-vectored" option, probably because the RISC-V CPU doesn't have hardware to automatically save and restore the CPU's context when interrupts are triggered and exited.

But I'm more familiar with vectored interrupts, so for this first example, I decided to use that option. The `__attribute__( ( interrupt ) )` function annotation causes the compiler to automatically add logic which saves and restores the CPU context, but you have to add even more logic if you want higher-priority interrupts to be able to pre-empt lower-priority ones. See the "Vector processing mode" section of the ["Bumblebee core datasheet"](http://dl.sipeed.com/LONGAN/Nano/DOC/Bumblebee%20core%20datasheet_en.pdf) for more information - it's section 5.13.2 in the version that I'm looking at.
