### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

UART Pin: RX GPIO15.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```
#### 2.2 Configuration

Enable serial port.

Disable serial console.

#### 2.3 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.4 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(gp2y1051au0f REQUIRED)
```

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
./gp2y1051au0f -i

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
./gp2y1051au0f -p

gp2y1051au0f: TX connected to GPIO15(BCM).
```

```shell
./gp2y1051au0f -t read --times=3

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
gp2y1051au0f: dust density is 2.86mg/m3.
gp2y1051au0f: dust density is 2.86mg/m3.
gp2y1051au0f: dust density is 2.00mg/m3.
gp2y1051au0f: finish read test.
```

```shell
./gp2y1051au0f -e read --times=3

gp2y1051au0f: 1/3.
gp2y1051au0f: dust density is 2.00mg/m3.
gp2y1051au0f: 2/3.
gp2y1051au0f: dust density is 4.00mg/m3.
gp2y1051au0f: 3/3.
gp2y1051au0f: dust density is 2.00mg/m3.
```

```shell
./gp2y1051au0f -h

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

