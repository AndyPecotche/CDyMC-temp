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
board = uno
framework = arduino
build_type = debug
extra_scripts = post:scripts/copy_sources_for_proteus.py
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


## 6. Simulación con avr:

Habilitar en template/platformio.ini la linea:

```ini
 debug_tool = simavr
```

En el panel izquierdo nos vamos a la pestaña de "Ejecucion" de VScode, y ahi elegimos la opcion "PIO Debug", equivalente a ejecuta el comando pio debug en consola.

(insertar captura)

### Posibles errores:

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




