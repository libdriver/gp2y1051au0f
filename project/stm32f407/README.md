### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

UART2 Pin: RX PA3.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. GP2Y1051AU0F

#### 3.1 Command Instruction

1. Show gp2y1051au0f chip and driver information.

   ```shell
   gp2y1051au0f (-i | --information)
   ```

2. Show gp2y1051au0f help.

   ```shell
   gp2y1051au0f (-h | --help)
   ```

3. Show gp2y1051au0f pin connections of the current board.

   ```shell
   gp2y1051au0f (-p | --port)
   ```

4. Run gp2y1051au0f read test, num is the test times.

   ```shell
   gp2y1051au0f (-t read | --test=read) [--times=<num>]
   ```


6. Run gp2y1051au0f read function, num is the test times.

   ```shell
   gp2y1051au0f (-e read | --example=read) [--times=<num>]
   ```

#### 3.2 Command Example

```shell
gp2y1051au0f -i

gp2y1051au0f: chip is SHARP GP2Y1051AU0F.
gp2y1051au0f: manufacturer is SHARP.
gp2y1051au0f: interface is UART.
gp2y1051au0f: driver version is 1.0.
gp2y1051au0f: min supply voltage is 4.8V.
gp2y1051au0f: max supply voltage is 5.2V.
gp2y1051au0f: max current is 20.00mA.
gp2y1051au0f: max temperature is 65.0C.
gp2y1051au0f: min temperature is -10.0C.
```

```shell
gp2y1051au0f -p

gp2y1051au0f: TX connected to GPIOA PIN3.
```

```shell
gp2y1051au0f -t read --times=3

gp2y1051au0f: chip is SHARP GP2Y1051AU0F.
gp2y1051au0f: manufacturer is SHARP.
gp2y1051au0f: interface is UART.
gp2y1051au0f: driver version is 1.0.
gp2y1051au0f: min supply voltage is 4.8V.
gp2y1051au0f: max supply voltage is 5.2V.
gp2y1051au0f: max current is 20.00mA.
gp2y1051au0f: max temperature is 65.0C.
gp2y1051au0f: min temperature is -10.0C.
gp2y1051au0f: start read test.
gp2y1051au0f: dust density is 3.43mg/m3.
gp2y1051au0f: dust density is 4.57mg/m3.
gp2y1051au0f: dust density is 4.57mg/m3.
gp2y1051au0f: finish read test.
```

```shell
gp2y1051au0f -e read --times=3

gp2y1051au0f: 1/3.
gp2y1051au0f: dust density is 2.86mg/m3.
gp2y1051au0f: 2/3.
gp2y1051au0f: dust density is 3.14mg/m3.
gp2y1051au0f: 3/3.
gp2y1051au0f: dust density is 4.00mg/m3.
```

```shell
gp2y1051au0f -h

Usage:
  gp2y1051au0f (-i | --information)
  gp2y1051au0f (-h | --help)
  gp2y1051au0f (-p | --port)
  gp2y1051au0f (-t read | --test=read) [--times=<num>]
  gp2y1051au0f (-e read | --example=read) [--times=<num>]

Options:
  -e <read>, --example=<read>        Run the driver example.
  -h, --help                         Show the help.
  -i, --information                  Show the chip information.
  -p, --port                         Display the pins used by this device to connect the chip.
  -t <read>, --test=<read>           Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
```

