# st25tb_kameleon_stm32

ST25TB / SRx NFC Emulator / Initiator - kameleon - based on Hyrabus with kameleon hat

## Hydrabus & HydraNFC

From Benjamin VERNOUX ( @bvernoux )

- https://hydrabus.com/hydrabus-1-0-specifications/
- https://hydrabus.com/hydranfc-1-0-specifications/


## Build

This firmware is using `STM32CubeIDE`, compatible with `STM32CubeMX` - project supports code regeneration without altering the ST25TB part.

## Flash

You can flash the firmware from the IDE itself, but you can also use `STM32CubeProgrammer`, the GUI or the CLI.

By example for DFU mode in CLI: `STM32_Programmer_CLI --connect port=usb1 --download build\Release\st25tb_kiwi_stm32_hydrabus.hex --verify --go`

```
      -------------------------------------------------------------------
                       STM32CubeProgrammer v2.22.0
      -------------------------------------------------------------------



USB speed   : Full Speed (12MBit/s)
Manuf. ID   : STMicroelectronics
Product ID  : STM32  BOOTLOADER
SN          : 207036B25853
DFU protocol: 1.1
Board       : --
Device ID   : 0x413
Device name : STM32F405xx/F407xx/F415xx/F417xx
NVM size  : 1 MBytes (default)
Device type : MCU
Revision ID : --
Device CPU  : Cortex-M4


Opening and parsing file: st25tb_kiwi_stm32_hydrabus.hex


Memory Programming ...
  File          : st25tb_kiwi_stm32_hydrabus.hex
  Size          : 81.78 KB
  Address       : 0x08000000


Erasing memory corresponding to segment 0:
Erasing internal memory sector 0
Erasing memory corresponding to segment 1:
Erasing internal memory sector 1
Erasing memory corresponding to segment 2:
Erasing internal memory sectors [2 4]
Download in Progress:
██████████████████████████████████████████████████ 100%

File download complete
Time elapsed during download operation: 00:00:04.123



Verifying...


Read progress:
██████████████████████████████████████████████████ 100%

Time elapsed during verifying operation: 00:00:00.152


Download verified successfully



RUNNING Program ...
  Address:      : 0x8000000
Start operation achieved successfully
```

### Notes

- `--erase all` can be added before `--download`
- `port=usb1` is not mandatory, you can also add a `sn=___`
  - use `STM32_Programmer_CLI --list` to be sure before...

## References

- `Hydrabus`
  - https://hydrabus.com/hydrabus-1-0-specifications/
  - https://github.com/hydrabus/hydrabus
  - https://github.com/hydrabus/hydrafw
  
- `HydraNFC`
  - https://hydrabus.com/hydranfc-1-0-specifications/
  - https://github.com/hydrabus/hydranfc
  - https://github.com/hydrabus/hydrafw (included in original firmware)

- `HydraNFC v2` - _not compatible with this firmware_
  - https://hydrabus.com/hydranfc-shield-v2-specifications/ 
  - https://github.com/hydrabus/hydrafw_hydranfc_shield_v2

- `STM32F405RG` - https://www.st.com/en/microcontrollers-microprocessors/stm32f405rg.html

- `TRF7970A` - https://www.ti.com/product/TRF7970A


## Question & Answers

### 1. Can I buy one?

Yes, maybe, Benjamin VERNOUX ( @bvernoux ) mades them, if you're lucky on https://hydrabus.com/shop/ or maybe you can still find them:
- Hydrabus : https://www.digikey.fr/en/products/detail/benjamin-vernoux/HYDRABUS-V1/15652912
- HydraNFC : https://lab401.com/fr/products/hydranfc
  
  ... but Benjamin is now more focus on HydraNFC v2 - https://hydrabus.com/hydranfc-shield-v2-specifications/ - with a better NFC chip : `ST25R3916(B)`

## Author

Benjamin DELPY 🥝 `gentilkiwi`, you can contact me on Twitter ( @gentilkiwi ) or by mail ( benjamin [at] gentilkiwi.com )

This is a personal development, please respect its philosophy and don't use it for bad things!

Benjamin VERNOUX (@bvernoux) is the author of Hydrabus hardware, HydraNFC hardware and their original firmwares


## Licence

CC BY 4.0 licence - [https://creativecommons.org/licenses/by/4.0/](https://creativecommons.org/licenses/by/4.0/)
