## LCD1602 related documentation

 1. **LCD_Interfacing_Learn_Arduino-V1-B.pdf**,
    - HandsOnTechnology, good schematics (breadboard).
 2. **LCD_wiring.pdf**,
    - someone's STM32 wiring from a forum, he connected backlight to GPIO (risky).
 3. **Liquid_Crystal_Lib_Doc.pdf**,
    - developer documentation of Arduino LiquidCrystal library.
 4. **QAPASS_5V_1602a.pdf**,
    - shattered google-translate chinese->english LCD module documentation, with
     important non-standard timings-graph, i.e. QAPASS differs from other
     manufacturers and the shattered-pdf is the knowledge source ;).
 5. **write_operation_QAPASS_5V.png**,
    - the non-standard QAPASS timings-graph took out of the poor quality PDF.
 6. **ST_Nucleo144_F767-ZI_Arduino_pins.png**,
    - STM Nucleo-144 board connectors' layout with assigned Arduino functions of pins.
 7. **Shenzhen_1602A1_v1.2_5V.pdf**,
    - other chinese LCD module, different from QAPASS.
 8. **adafruit-lesson-11-lcd-displays-part-1.pdf**,
    - basic LCD lession from Adafruid, good schematics (breadboard).
 9. **adafruit-lesson-12-lcd-displays-part-2.pdf**,
    - more advanced LCD lession.
 10. **chinese_QAPASS_1602A-3.3V-1.pdf**,
     - in chinese language, 3.3V voltage standard (uncommon), but with code
     samples at the end (i.e. example of initialization code that can match
     other. manufacturers (does match my QAPASS 5V))
