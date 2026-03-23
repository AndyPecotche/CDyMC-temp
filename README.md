# Guía de instalación y uso de PlatformIO para desarrollo con ATmega328p

Esta guía detalla los pasos para la instalación y configuración de PlatformIO, ejemplificando el proceso en Ubuntu y Windows. 

Para otras distribuciones de Linux o macOS, los pasos pueden variar ligeramente, pero cada plataforma cuenta con su propio instructivo oficial.

## 1. Instalación de Visual Studio Code

### Linux (Debian/Ubuntu)
1. Descarga el archivo `.deb` desde la [página oficial](https://code.visualstudio.com/download)
2. Consulta el [instructivo oficial](https://code.visualstudio.com/docs/setup/linux) si es necesario.
3. Ejecuta el siguiente comando en la terminal dentro de la carpeta donde se descargó el archivo:
   ```bash
   sudo apt install ./<nombre_del_archivo>.deb
   ``` 

### Windows
* Descarga y ejecuta el instalador `.exe` desde la [página oficial](https://code.visualstudio.com/download)

## 2. Instalación de la extensión PlatformIO
Una vez instalado Visual Studio Code:
1. Dirígete a la sección de **Extensiones**.
2. Busca **"platformio"** e instala la extensión oficial.

<img width="630" height="341" alt="image" src="https://github.com/user-attachments/assets/d3df7c7a-6470-4be3-8e49-f425624be0af" />

<img width="510" height="176" alt="{3711E335-3EE7-4779-80BC-BB3D4E13E8C8}" src="https://github.com/user-attachments/assets/9db170ef-8cc4-41ed-bf95-dd70a7dbfab7" />

#### En este paso puede que no termine de instalar y nos pida definir el path o instalar python, si no es el caso, saltear el siguiente paso.

### Configuración de Python
Si PlatformIO no detecta Python automáticamente, es posible que debas instalarlo manualmente:

* **En Linux:**
  ```bash
  sudo apt install python3
  sudo apt install python3-venv
  ``` 
* **En Windows:**
  Descarga el instalador desde [python.org](https://www.python.org/downloads/windows/) y asegúrate de marcar la opción para **agregar Python al PATH** durante la instalación.

<img width="565" height="346" alt="image" src="https://github.com/user-attachments/assets/dcd0411e-df57-4f2d-a9dc-c388d5b46b3d" />

## 3. Configuración del Proyecto
Con la instalación finalizada, podes iniciar un proyecto utilizando un archivo `platformio.ini` con la siguiente configuración base:

```ini
[env:ATmega328P]
platform = atmelavr
board = ATmega328P
#debug_tool = simavr #Descomentar para ejecutar simulaciones con simavr.
build_type = debug
extra_scripts =
 	post:scripts/copy_sources_for_proteus.py
upload_protocol = arduino
``` 

### Descarga del proyecto base
Podes obtener el proyecto base desde este enlace de [GitHub](https://github.com/AndyPecotche/CDyMC-temp/archive/refs/heads/main.zip).

## 4. Uso de la Interfaz
1. Abre el proyecto desde **File → Open folder**.

<img width="653" height="327" alt="image" src="https://github.com/user-attachments/assets/307276fd-7293-4ee4-85a7-4689149e5017" />

La primera vez inicializara la configuracion necesaria:

<img width="492" height="148" alt="{DE32E3E8-71B9-45BD-A9E0-92E88557140E}" src="https://github.com/user-attachments/assets/fbb49ba4-658c-4e95-9adc-23de8c38b35b" />


3. Accede al icono de la extensión de PlatformIO para cargar las opciones de la plataforma.

      <img width="241" height="153" alt="image" src="https://github.com/user-attachments/assets/d43998b3-2de2-45a4-b30b-b72814a21b6e" />

4. En la parte extrema inferior interfaz encontrarás iconos para:
   * **Compilación (Checkmark)**.
   * **Grabar programa en Arduino (Flecha)**.
   * **Limpiar builds (Tacho de basura):** Se recomienda usar esta opción antes de compilar y grabar para evitar cargar versiones antiguas.
   * **Terminal serie (Icono de enchufe)**.


   <img width="659" height="23" alt="image" src="https://github.com/user-attachments/assets/0b7a915b-3c5d-43d9-8eb5-f534e6d4bc08" />


## 5. Simulación y Archivos Compilados
El archivo compilado `firmware.elf` se genera en la ruta `template/.pio/build/ATmega328P`. 

Es recomendable antes de grabar un nuevo programa en la placa, darle a clean (icono del tacho de basura), antes de compilar ya que a veces sino se graba nuevamente el programa viejo.

Si utilizas el proyecto base del enlace, un script de post-build (`copy_sources_for_proteus.py`) copiará automáticamente los archivos `.c` y `.h` de la carpeta `src` a la carpeta del build. Teniendo los archivos originales en una carpeta src junto al archivo .elf, nos permite poder acceder al código desde simulaciones en **proteus**.


### 5.1 Simulación con simavr:

- Si se parte de este proyecto como template en el mismo ya se encuentran aplicados todos los pasos de instalacion/configuracion detallados adelante por lo que se pueden omitir. Se dejan detallados igualmente a modo de instructivo.

Instalación en Debian/Ubuntu:

NOTA: No es necesario instalar estas herramientas para usar el simulador integrado de PlatformIO.  
Sin embargo, si se desea utilizar funcionalidades avanzadas de simavr (como generación de trazas VCD que se vera mas adelante), es necesario contar con los headers del proyecto.


```bash
# Clonar repositorio de simavr
mkdir -p /tmp/simavr
git clone https://github.com/buserror/simavr.git /tmp/simavr

# Copiar header necesario para VCD
cp /tmp/simavr/simavr/sim/avr/avr_mcu_section.h ../include/avr_mcu_section.h
```

Habilitar en template/platformio.ini la linea:

```ini
 debug_tool = simavr
```

En el panel izquierdo nos vamos a la pestaña de "Ejecucion" de VScode, y ahi elegimos la opcion "PIO Debug", equivalente a ejecuta el comando pio debug en consola:

<img width="434" height="293" alt="image" src="https://github.com/user-attachments/assets/7d5232af-3274-4cbe-9775-f295893531a8" />

## Primeros pasos: 

<img width="1142" height="895" alt="image" src="https://github.com/user-attachments/assets/438a8901-01db-40e3-8e91-c0ab82ccb465" />

- Luego de darle a `RUN`, la simulacion comenzara a ejecutarse, para interactual con la misma vamos a utlizar la consola de GNU Debugger *(Referencia numero 2)*, la misma nos permitira interactuar ya sea para consultar como modificar, variables, pines, registros, interrupciones, etc.

- En el apartado de `WATCH` *(referencia 1)*, podemos definir expresiones de la consola para hacer seguimiento a los valores de las mismas sin tener que escribir los comandos en la consola. 

- Los comandos solo pueden introducirse mientras la simulacion se encuentra `pausada`, tambien pueden agregarse `breakpoints` desde conosla como desde el mismo IDE.

- En el ejemplo de la captura podemos observar el comando para modificar el registro `PIND`, para encender el LED (definir `PD2` en bajo), y en el apartado de `WATCH` observar su valor actual (0b00000100) (`PD2` en alto).
Ademas podemos ejecutar por pasos la simulacion desde los comandos que provee la UI *(referencia 3)*.

#### Toda la documentacion relacionada a la consola de GNU Deugger puede encontrarse en <insertar link / comando>

#### Para mayor detalle y ejemplos de uso de simavr, se encuentra el repositorio oficial del proyecto con mas informacion: `https://github.com/buserror/simavr`

### VCD y analizador logico:

Simavr permite no solo ejecutar firmware AVR, sino también registrar señales internas del microcontrolador (registros, pines, flags, etc.) y exportarlas a un archivo en formato VCD (Value Change Dump).
Este archivo puede visualizarse con herramientas como GTKWave, permitiendo analizar el comportamiento temporal de las señales.
En la práctica, esto funciona como un analizador lógico virtual, similar a un osciloscopio digital:
   - Permite ver cambios de estado en pines
   - Analizar timing y secuencias
   - Detectar errores lógicos
   - Debuggear sin necesidad de hardware físico
Para esto simavr utiliza una sección especial del binario (.mmcu) donde se define qué señales deben registrarse. Esto se logra mediante una estructura especial:

```c
const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_
```

En este proyecto se encuentra el ejemplo de esta estructura declarada en `template/src/vcd.h`:

```c
#include <avr/io.h>
#include "avr_mcu_section.h"
const struct avr_mmcu_vcd_trace_t _mytrace[];
```

Y en el ejemplo aplicado en `template/src/vcd.c`, se hace la trazabilidad del estado de:

PIND → estado de entradas digitales (botón)
PORTB → estado de salidas (LED)
LED_PB5 → pin específico del LED
BTN_PD2 → pin específico del botón

```c
#include <vcd.h> 
const struct avr_mmcu_vcd_trace_t _mytrace[] _MMCU_ = {

    // Ver todo el puerto D (entrada)
    { AVR_MCU_VCD_SYMBOL("PIND"), .what = (void*)&PIND },

    // Ver todo el puerto B (salida)
    { AVR_MCU_VCD_SYMBOL("PORTB"), .what = (void*)&PORTB },

    // Ver SOLO el LED (PB5)
    { AVR_MCU_VCD_SYMBOL("LED_PB5"), .mask = (1 << PB5), .what = (void*)&PORTB },

    // Ver SOLO el botón (PD2)
    { AVR_MCU_VCD_SYMBOL("BTN_PD2"), .mask = (1 << PD2), .what = (void*)&PIND },
};
```

*IMPORTANTE*: Agregar en el platformio.ini 
```
build_flags =
    -Wl,--undefined=_mytrace
```

El simavr de platformio no generara el archivo vcd, por lo que debe ejecutarse en consola manualmente, para lo cual primero se debe instalar simavr:

En ubuntu/debian:
```
sudo apt install simavr
sudo apt install gtkwave #(opcional pero recomendado para visualizar el archivo VCD)
```
Y luego ejecutar:
```
simavr -m atmega328p -f 16000000 .pio/build/ATmega328P/firmware.elf
```
Se deberia generar un archivo de salida: `gtkwave_trace.vcd`
Visualizar registro con :
```
gtkwave gtkwave_trace.vcd
```

### Ejemplo:

Modificamos el programa main.c para que ahora alterne automaticamente el estado del registo PB5 un numero finito de veces:

```c
	for (int i = 0; i < 10; i++) {
		// Leer PD2 (D2) con pull-up interna: si se conecta a GND -> LOW -> encender LED
		_delay_ms(1000);
		PORTB |= (1<<PB5); // encender LED integrado
		_delay_ms(1000);
		PORTB &= ~(1<<PB5); // apagar LED
	}
```
Lo compilamos desde platformio o con `pio build`, y luego ejecutamos en la consola simavr (ya que como mencionamos antes con el integrado por platformio no funciona):
```bash
simavr -v -m atmega328p -f 16000000 .pio/build/ATmega328P/firmware.elf
# abrimos gtkwave parados en la raiz del proyecto donde se genera el archivo de salida (junto al .ini):
gtkwave gtkwave_trace.vcd
```
<img width="1247" height="489" alt="image" src="https://github.com/user-attachments/assets/266c62c5-6d0d-4b9b-854b-323aec0da0e6" />


Podemos notar que tenemos reigstro del estado de los puertos que listamos en el archivo `template/src/vcd.c` con las mismas etiquetas que le asignamos. PIND y PD2 podemos ver que no se modificaron porque no ingresamos ninguna modificacion para alterarl el valor el mismo, pero podriamos ingresar:
```
set var PIND=0b00000000
```
Para lograr esto, como no estamos usando el simavr de platformio que nos provee la consola de debug, tendremos que ejecutar simavr con el siguiente comando:

```bash
simavr -g -m atmega328p -f 16000000 .pio/build/ATmega328P/firmware.elf
#Salida
# avr_gdb_init listening on port 1234
```
En otra consola ejecutaremos avr_gdb:

```
#dentro del proyecto
cd template
avr-gdb .pio/build/ATmega328P/firmware.elf
target remote :1234 # nos conectamos al puerto que abrimos antes en avr_gdb_init
set var PIND = 0b00000000
```
En este tipo de ejecucion, a diferencia de la anterior, tendremos que ejecutar `continue` en el GDB, para que la ejecucion retome, y ctr+c para pausarla y modificar valores, por lo que este tipo de uso quizas no presenta tanta utilidad. Alternativamente pueden ingresarse archivos .VCD como entrada a la simulacion.



#### Posibles errores:

Si sale algun error en consola por dependencias como el siguinte:

```bash
undefined/home/xxxx/.platformio/packages/toolchain-atmelavr/bin/avr-gdb: error while loading shared libraries: libtinfo.so.5: cannot open shared object file: No such file or directory
```

Puede solucionarse simplemente instalando la dependencia no encontrada:

En el caso del ejemplo vemos que no puede encontrar libtinfo.so.5, en ubuntu o debian puede instalarse con "apt install libtinfo", si la depedencia fuera vieja (como el caso del ejemplo) y la version de la distribucion no la tiene soportada, podemos generar un link simbolico de la version equivalente actual a la anterior:

Verificamos si la version actual la tenemos instalada (y sino la instalamos):

```bash
ls /usr/lib/x86_64-linux-gnu/libtinfo.so.5
ls: cannot access '/usr/lib/x86_64-linux-gnu/libtinfo.so.5': No such file or directory

ls -l /usr/lib/x86_64-linux-gnu/libtinfo.so.6
lrwxrwxrwx 1 root root 15 abr  8  2024 /usr/lib/x86_64-linux-gnu/libtinfo.so.6 -> libtinfo.so.6.4
#Vemos que tenemos la version 6.4 instalada
```

Creamos el link simbolico para poder resolver la dependencia de la version solicitada:

```bash
sudo ln -s /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4 /usr/lib/x86_64-linux-gnu/libtinfo.so.5
#Verificamos con:
ls -l /usr/lib/x86_64-linux-gnu/libtinfo.so.5
# Y ahora si quedo 'existente' la version que necesitamos
lrwxrwxrwx 1 root root 41 mar 22 20:07 /usr/lib/x86_64-linux-gnu/libtinfo.so.5 -> /usr/lib/x86_64-linux-gnu/libtinfo.so.6.4
```

De esta manera ahora la dependencia "libtinfo.so.5" queda resuelta apuntando a la libtinfo.so.6.4. Probamos ejecutar debug nuevamente, y seguimos resolviendo dependencias de la misma manera o instalando las mismas, hasta que no tire mas errores. (Esto es comun en versiones mas modernas de distribuciones como ubuntu 24)




