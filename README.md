# st25tb_kiemul

ST25TB / SRx NFC Emulator / Initiator based on TI TRF7970A with MSP430

This is the support project of `ST25TB series NFC tags for fun in French public transports` ([ST25TB_transport.pdf](ST25TB_transport.pdf))


## Project

`st25tb_kiemul` project is ready for Texas Intruments Code Composer Studio (CCS) IDE 12+, https://www.ti.com/tool/CCSTUDIO

You can use the local IDE or the online one (CCS Cloud). When using online IDE, do not forget to delete additionnal `.cmd` at the root of the project after the initial import ; they are conflicting with **specific** embeded ones in the project.

You can reduce the code base but, at this time, the full project (emulator/writer/learner with led animations) needs (only) < 6 kilobytes for program and < 700 bytes of memory.


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
_basics_

At startup/reset, the content of the emulator card is loaded from the flash memory. If no cards were previously learned, a default one with the UID: `d00233aabbccddee` is loaded.

Left and Right buttons are used to cycle between modes (Emulator -> Writer -> Learn)

### 🟢 ⚫ Emulator mode - _(default)_
_GREEN led only_

In this mode, it reacts like a normal ST25TB-AT cards, with few differences:
- Sectors `0x05` and `0x06` are not limited to decrement ;
- Sector `0xff` (system area / internal is `0x80`) is not used to lock sectors/OTP ;
- Sectors `0x81` and `0x82` can be used to read **and write** UID ;
- Any writing operation to sector `0xfe` will write current emulated card into flash memory.

_basically, it reacts like a memory card without limitation_

### ⚫ 🔴 Writer mode
_RED led only_

In this mode, it will try to write the emulator content back to the original card.

Leds on the `DLP-7970ABP` board are used for status:
- 🔵 & 🟢 Card successfully writed (and confirmed) 
- 🔴 An error occured (not the good UID or write then read error)


### 🟢 🔴 Learn mode - _dangerous!_
_GREEN & RED led_

In this mode, it will read an original card into emulator, then save it to the flash memory.

Leds on the `DLP-7970ABP` board are used for status:
- 🔵 Card successfully readed (and confirmed) 
- 🔴 An error occured (try to move the card, no need to stick it to the antenna)
- 🟢 Card successfully writed to the flash memory


## Remarks

- Yep, I recreated a ~1% `Chameleon` like stuff :')
- Yep, I'm happy with it: I do it for myself to learn (& for fun)
- No, I'm not confident to be able to help to add 14B(') to https://github.com/emsec/ChameleonMini/tree/master/Firmware/Chameleon-Mini/Codec
  - otherwise I would have done it
- No, I will not create a single board with battery from available schematics of MSP430 LaunchPad & TRF7970A BoosterPack
- Yes, you can use other (better) MCU with the `TRF7970A`, even with the original `DLP-7970ABP` board
  - think aout STM32, Raspberry PI Pico or your prefered one with `SPI` support, **really**


## Hardware references

- `MSP-EXP430F5529LP` - https://www.mouser.com/ProductDetail/595-MSPEXP430F5529LP
  - Board: https://www.ti.com/tool/MSP-EXP430F5529LP
  - Chip: https://www.ti.com/product/MSP430F5529
- `LP-MSP430FR2476` - https://www.mouser.com/ProductDetail/595-LP-MSP430FR2476
  - Board: https://www.ti.com/tool/LP-MSP430FR2476
  - Chip: https://www.ti.com/product/MSP430FR2476
- `DLP-7970ABP` - https://www.mouser.com/ProductDetail/595-DLP-7970ABP
  - Board: https://www.ti.com/tool/DLP-7970ABP
  - Chip: https://www.ti.com/product/TRF7970A


## Author

Benjamin DELPY `gentilkiwi`, you can contact me on Twitter ( @gentilkiwi ) or by mail ( benjamin [at] gentilkiwi.com )

This is a personal development, please respect its philosophy and don't use it for bad things!

## Licence

CC BY 4.0 licence - [https://creativecommons.org/licenses/by/4.0/](https://creativecommons.org/licenses/by/4.0/)