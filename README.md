# st25tb_kiemul

ST25TB / SRx NFC Emulator / Initiator based on TI TRF7970A with MSP430

This is the support project of `ST25TB series NFC tags for fun in French public transports` ([ST25TB_transport.pdf](ST25TB_transport.pdf))


## Project

`st25tb_kiemul` project is ready for Texas Intruments Code Composer Studio IDE 12+, https://www.ti.com/tool/CCSTUDIO (IDE or online)

You can reduce functions needed, but the full project (emulator/writer/learner with led animations) needs < 6 kilobytes for program and < 300 bytes of memory.


## Supported configurations

- `MSP-EXP430F5529LP` + `DLP-7970ABP` with configuration `Release - lp-msp430f5529` - MSP @ 25 MHz, external battery needed
- `LP-MSP430FR2476` + `DLP-7970ABP` with configuration `Release - lp-msp430fr2476` - MSP @ 16 MHz, CR2032 battery compatible!
- `*MSP430*` + `DLP-7970ABP` with new configuration to create (feel free to adapt :))


## Flash

You can program your board from the IDE itself, but `.hex` files produced/downloaded can also be used with `MSP430Flasher` (https://www.ti.com/tool/MSP430-FLASHER) or `UniFlash` (https://www.ti.com/tool/UNIFLASH).

No `MSP-FET` required when using LaunchPad cards, as they embed an `eZ-FET lite` emulator.

### Examples:

- `MSP430Flasher -i TIUSB -n MSP430FR2476 -z [VCC,RESET] -e ERASE_ALL -v -w st25tb_kiemul-MSP430FR2476.hex`
- `MSP430Flasher -i TIUSB -n MSP430F5529 -z [VCC,RESET] -e ERASE_ALL -v -w st25tb_kiemul-MSP430F5529.hex`

#### Notes:
- replace `-i TIUSB` by `-i COMnumber` when dealing with multiple boards connected at the same time ;
- do not hesitate to make another reset by the button after flashing.


## How to use it?

At startup/reset, the content of the emulator card is loaded from the flash memory. If no cards were previously learned, a default one with the UID: `d00233aabbccddee` is loaded.

Left and Right buttons are used to cycle between modes (Emulator -> Writer -> Learn)

### 🟢 ⚫ Emulator mode - _(default)_

In this mode, it reacts like a normal ST25TB-AT cards, with few differences:
- Sectors `0x05` and `0x06` are not limited to decrement ;
- Sector `0xff` (system area) is not used to lock sectors/OTP ;
- Sectors `0x7e` and `0x7f` can be used to read **and write** UID ;
- Any writing operation to sector `0x60` will write current emulated card into flash memory.

_basically, it reacts like a memory card without limitation_

### ⚫ 🔴 Writer mode

_TODO_

### 🟢 🔴 Learn mode - _dangerous!_

_TODO_


## Hardware references

- `MSP-EXP430F5529LP` - https://www.mouser.com/ProductDetail/595-MSPEXP430F5529LP
- `LP-MSP430FR2476` - https://www.mouser.com/ProductDetail/595-LP-MSP430FR2476
- `DLP-7970ABP` - https://www.mouser.com/ProductDetail/595-DLP-7970ABP