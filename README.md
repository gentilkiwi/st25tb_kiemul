# st25tb_kiemul

ST25TB / SRx NFC Emulator / Initiator based on TI TRF7970A with MSP430

This is the support project for `ST25TB series NFC tags for fun in French public transports` - [ST25TB_transport.pdf](https://raw.githubusercontent.com/gentilkiwi/st25tb_kiemul/main/ST25TB_transport.pdf)

> **Note:** This project now supports `st25tb_kiemul` (including the `LP-MSP430FR2476`), `st25tb_kameleon` and `st25tb_kiwi` boards


## Project

`st25tb_kiemul` project is ready for Texas Instruments Code Composer Studio (CCS) IDE 12+, https://www.ti.com/tool/CCSTUDIO. You can use the local IDE or the online one (CCS Cloud). As TI is switching from Eclipse-based IDE to Theia, it has been also tested with CCS 20.4.


## Supported configurations

### Initial
- `LP-MSP430FR2476` + `DLP-7970ABP` with configuration `st25tb_kiemul` - MSP @ 16 MHz, CR2032 battery compatible!
- `*MSP430*` + `DLP-7970ABP` with new configuration to create (feel free to adapt :))

Do **NOT** underestimate this basic configuration. Despite the lack of led indicators: `MSP430FR2476` has a _lot_ of FRAM memory, the integrated `eZ-FET lite` provides the same CLI as the most recent boards.

### Boards

To practice, for POCs, and for the lulz, I finally made boards to play with:
- The initial one, `st25tb_kiemul`, was made to be 100% compatible with the launchpad + daughter board firmware (no CLI support)  
  \> https://oshwlab.com/gentilkiwi/st25tb_kiemul
- The second one, `st25tb_kameleon`, supports LIR2032 battery, USB power and battery charging  
  \> https://oshwlab.com/gentilkiwi/st25tb_kameleon
- The third (and last) one, `st25tb_kiwi`, supports LIR2032, LP401730 & LP402535 batteries, USB-C power and battery charging, CLI  
  \> https://oshwlab.com/gentilkiwi/st25tb_kiwi


## Flash

You can program your board from the IDE itself, but `.hex` files produced/downloaded can also be used with `MSP430Flasher` (https://www.ti.com/tool/MSP430-FLASHER) or `UniFlash` (https://www.ti.com/tool/UNIFLASH).

No `MSP-FET` required when using LaunchPad boards, as they embed an `eZ-FET lite` emulator. On other configurations you may need [`MSP-FET`](https://www.ti.com/tool/MSP-FET) to flash the board, but you can also use the embedded `eZ-FET lite` from another Launchpad board you already have :)

### Examples:

- `MSP430Flasher -i TIUSB -n MSP430FR2476 -z [VCC,RESET] -e ERASE_ALL -v -w st25tb_kiemul-MSP430FR2476.hex`

#### Notes:
- replace `-i TIUSB` by `-i COM<number>` when dealing with multiple boards connected at the same time ;
- do not hesitate to press the reset button again after flashing.


## How to use it?

Wiki: https://github.com/gentilkiwi/st25tb_kiemul/wiki


## Remarks

- Yep, I recreated ~1% of a `Chameleon` like stuff :')
- Yep, I'm happy with it: I did it for myself to learn (& for fun)
- No, I'm not confident to be able to help to add 14B(') to https://github.com/emsec/ChameleonMini/tree/master/Firmware/Chameleon-Mini/Codec
  - otherwise I would have done it
- ~~No, I will not create a single board with battery from available schematics of MSP430 LaunchPad & TRF7970A BoosterPack~~
  - ~~well, maybe?~~
  - well, I did (and learned a lot)
- Yes, you can use other (better) MCU with the `TRF7970A`, even with the original `DLP-7970ABP` board
  - think about STM32, Raspberry PI Pico or your prefered one with `SPI` support, **really**


## Hardware references

- `LP-MSP430FR2476` - https://www.mouser.com/ProductDetail/595-LP-MSP430FR2476
  - Board: https://www.ti.com/tool/LP-MSP430FR2476
  - Chip: https://www.ti.com/product/MSP430FR2476
- `DLP-7970ABP` - https://www.mouser.com/ProductDetail/595-DLP-7970ABP
  - Board: https://www.ti.com/tool/DLP-7970ABP
  - Chip: https://www.ti.com/product/TRF7970A
- `st25tb_kiemul`
  - Board: https://oshwlab.com/gentilkiwi/st25tb_kiemul
  - Chip: https://www.ti.com/product/MSP430FR2476
- `st25tb_kameleon`
  - Board: https://oshwlab.com/gentilkiwi/st25tb_kameleon
  - Chip: https://www.ti.com/product/MSP430FR2673
- `st25tb_kiwi`
  - Board: https://oshwlab.com/gentilkiwi/st25tb_kiwi
  - Chip: https://www.ti.com/product/MSP430FR2676


## Authors

Benjamin DELPY 🥝 gentilkiwi, you can contact me on Twitter ( @gentilkiwi ) or by mail ( benjamin [at] gentilkiwi.com )  
Tear off part is 99% the (crazy) work of @SecLabz, see his repository https://github.com/SecLabz/near-field-chaos for more information, and functionalities! ❤️

This is a personal development, please respect its philosophy and don't use it for bad things!


## License

CC BY 4.0 licence - https://creativecommons.org/licenses/by/4.0/