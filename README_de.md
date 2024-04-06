[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver GP2Y1051AU0F
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/gp2y1051au0f/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

GP2Y1051AU0F ist ein Staubsensor mit optischem Sensorsystem. In diesem Gerät sind eine Infrarot-Emissionsdiode (IRED) und ein Fototransistor diagonal angeordnet. Es erkennt das reflektierte Licht von Staub in der Luft. Insbesondere ist es effektiv, sehr feine Partikel wie Zigarettenrauch zu erkennen. Darüber hinaus kann es durch das Pulsmuster der Ausgangsspannung zwischen Rauch und Hausstaub unterscheiden.

LibDriver GP2Y1051AU0F ist der von LibDriver eingeführte Vollfunktionstreiber von GP2Y1051AU0F. Er bietet die Funktion zum Lesen der Staubdichte und andere Funktionen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver GP2Y1051AU0F-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver GP2Y1051AU0F UART.

/test enthält den Testcode des LibDriver GP2Y1051AU0F-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver GP2Y1051AU0F-Beispielcode.

/doc enthält das LibDriver GP2Y1051AU0F-Offlinedokument.

/Datenblatt enthält GP2Y1051AU0F-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige UART-Schnittstellenvorlage und stellen Sie Ihren Plattform-UART-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

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

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/gp2y1051au0f/index.html](https://www.libdriver.com/docs/gp2y1051au0f/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.