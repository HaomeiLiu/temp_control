# Arduino Pins #

| Pin Number | R/W   | Description               |                   |
| ---------- | ----- | ------------------------- | ----------------- |
| A0         | Read  | heater temperature        |                   |
| A1         | Read  | body temperature          |                   |
| D2         | R     | input MUX select          | ADS1232 A0        |
| D3         | W     | pwm out                   | pid out           |
| D4         | R     | serial clock              | ADS1232 SCLK      |
| D5         | W     | data ready/output         | ADS1232 DRDY/DOUT |
| D6         | R     | data rate select          | ADS1232 SPEED     |
| D7         | R     | gain select               | ADS1232 GAIN0     |
| D8         | R     | gain select               | ADS1232 GAIN1     |
| D9         | Write | heater enable             | L6202 EN          |
| D10        | Write | heater control (PWM)      | L6202 IN1         |
| D11        | Write | heater control (PWM)      | L6202 IN2         |
| D12        | R     | temperature sensor select | ADS1232 A1/TEMP   |
| D13        | R     | power down                | ADS1232 PDWN      |

