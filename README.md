# st25tb_kiemul

ST25TB / SRx NFC Emulator / Initiator based on TI TRF7970A with MSP430

This is the support project of `ST25TB series NFC tags for fun in French public transports` ([ST25TB_transport.pdf](ST25TB_transport.pdf))

> **Note:** This project is **superseded** by `MSP430` [`st25tb_kameleon`](https://github.com/gentilkiwi/st25tb_kameleon) and its `RP2040` equivalent [`st25tb_kameleon_piko`](https://github.com/gentilkiwi/st25tb_kameleon_piko), both of which are more user-friendly.

## Project

`st25tb_kiemul` project is ready for Texas Intruments Code Composer Studio (CCS) IDE 12+, https://www.ti.com/tool/CCSTUDIO. You can use the local IDE or the online one (CCS Cloud).

You can reduce the code base but, at this time, the full project (emulator/writer/learner with led animations) needs (only) < 6 kilobytes for program and < 700 bytes of memory.


## Supported configurations

- `LP-MSP430FR2476` + `DLP-7970ABP` with configuration `Release - lp-msp430fr2476` - MSP @ 16 MHz, CR2032 battery compatible!
- `*MSP430*` + `DLP-7970ABP` with new configuration to create (feel free to adapt :))

Note: `MSP-EXP430F5529LP` + `DLP-7970ABP` is no longer supported by default. MSP430 devices with FRAM and a 16 MHz system clock are now preferred due to their simplicity and better compatibility.

## Flash

You can program your board from the IDE itself, but `.hex` files produced/downloaded can also be used with `MSP430Flasher` (https://www.ti.com/tool/MSP430-FLASHER) or `UniFlash` (https://www.ti.com/tool/UNIFLASH).

No `MSP-FET` required when using LaunchPad cards, as they embed an `eZ-FET lite` emulator. On other configurations you may need [`MSP-FET`](https://www.ti.com/tool/MSP-FET) to flash the board, but you can also use the embedded `eZ-FET lite` from another Launchpad card you already have :)

### Examples:

- `MSP430Flasher -i TIUSB -n MSP430FR2476 -z [VCC,RESET] -e ERASE_ALL -v -w st25tb_kiemul-MSP430FR2476.hex`

#### Notes:
- replace `-i TIUSB` by `-i COMnumber` when dealing with multiple boards connected at the same time ;
- do not hesitate to make another reset by the button after flashing.


## How to use it?

Wiki: https://github.com/gentilkiwi/st25tb_kiemul/wiki


## Remarks

- Yep, I recreated a ~1% `Chameleon` like stuff :')
- Yep, I'm happy with it: I do it for myself to learn (& for fun)
- No, I'm not confident to be able to help to add 14B(') to https://github.com/emsec/ChameleonMini/tree/master/Firmware/Chameleon-Mini/Codec
  - otherwise I would have done it
- ~~No, I will not create a single board with battery from available schematics of MSP430 LaunchPad & TRF7970A BoosterPack~~
  - ~~well, maybe?~~
  - well, I did: https://oshwlab.com/gentilkiwi/st25tb_kiemul
- Yes, you can use other (better) MCU with the `TRF7970A`, even with the original `DLP-7970ABP` board
  - think aout STM32, Raspberry PI Pico or your prefered one with `SPI` support, **really**


## Hardware references

- `LP-MSP430FR2476` - https://www.mouser.com/ProductDetail/595-LP-MSP430FR2476
  - Board: https://www.ti.com/tool/LP-MSP430FR2476
  - Chip: https://www.ti.com/product/MSP430FR2476
- `DLP-7970ABP` - https://www.mouser.com/ProductDetail/595-DLP-7970ABP
  - Board: https://www.ti.com/tool/DLP-7970ABP
  - Chip: https://www.ti.com/product/TRF7970A


## Kiwi board

To practice, for POC, and for the lulz, a mini-board is also available: https://oshwlab.com/gentilkiwi/st25tb_kiemul


## Authors

Benjamin DELPY 🥝 gentilkiwi, you can contact me on Twitter ( @gentilkiwi ) or by mail ( benjamin [at] gentilkiwi.com )  
Tear off part is 99% the (crazy) work of @SecLabz, see his repository https://github.com/SecLabz/near-field-chaos for more informations, and functionnalities! ❤️

This is a personal development, please respect its philosophy and don't use it for bad things!

## Licence

CC BY 4.0 licence - [https://creativecommons.org/licenses/by/4.0/](https://creativecommons.org/licenses/by/4.0/)