[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver GP2Y1051AU0F

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/gp2y1051au0f/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

GP2Y1051AU0F is a dust sensor by optical sensing system. An infrared emitting diode (IRED) and an phototransistor are diagonally arranged into this device. It detects the reflected light of dust in air. Especially, it is effective to detect very fine particle like the cigarette smoke. In addition it can distinguish smoke from house dust by pulse pattern of output voltage.

LibDriver GP2Y1051AU0F is the full function driver of GP2Y1051AU0F launched by LibDriver.It provides the function of dust density reading and other functions. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver GP2Y1051AU0F source files.

/interface includes LibDriver GP2Y1051AU0F UART platform independent template.

/test includes LibDriver GP2Y1051AU0F driver test code and this code can test the chip necessary function simply.

/example includes LibDriver GP2Y1051AU0F sample code.

/doc includes LibDriver GP2Y1051AU0F offline document.

/datasheet includes GP2Y1051AU0F datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface UART platform independent template and finish your platform UART driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_gp2y1051au0f_basic.h"

uint8_t res;
uint32_t i;

res = gp2y1051au0f_basic_init();
if (res != 0)
{
    return 1;
}

...
    
for (i = 0; i < 3; i++)
{
    float mg_m3;

    /* delay 1000ms */
    gp2y1051au0f_interface_delay_ms(1000);

    /* read data */
    res = gp2y1051au0f_basic_read(&mg_m3);
    if (res != 0)
    {
        (void)gp2y1051au0f_basic_deinit();

        return 1;
    }

    /* output */
    gp2y1051au0f_interface_debug_print("gp2y1051au0f: %d/%d.\n", i + 1, 3);
    gp2y1051au0f_interface_debug_print("gp2y1051au0f: dust density is %0.2fmg/m3.\n", mg_m3);
    
    ...
}

...
    
/* deinit */
(void)gp2y1051au0f_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/gp2y1051au0f/index.html](https://www.libdriver.com/docs/gp2y1051au0f/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.