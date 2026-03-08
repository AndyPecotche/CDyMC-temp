# Guía de instalación y uso de PlatformIO para desarrollo con ATmega328p

Esta guía detalla los pasos para la instalación y configuración de PlatformIO, ejemplificando el proceso en Ubuntu y Windows. 

Para otras distribuciones de Linux o macOS, los pasos pueden variar ligeramente, pero cada plataforma cuenta con su propio instructivo oficial.

## 1. Instalación de Visual Studio Code

### Linux (Debian/Ubuntu)
1. Descarga el archivo `.deb` desde la [página oficial](https://code.visualstudio.com/download)[cite: 1].
2. Consulta el [instructivo oficial](https://code.visualstudio.com/docs/setup/linux) si es necesario.
3. Ejecuta el siguiente comando en la terminal dentro de la carpeta donde se descargó el archivo:
   ```bash
   sudo apt install ./<nombre_del_archivo>.deb
   ``` 

### Windows
* [cite_start]Descarga y ejecuta el instalador `.exe` desde la [página oficial](https://code.visualstudio.com/download)[cite: 1].

## 2. Instalación de la extensión PlatformIO
Una vez instalado Visual Studio Code:
1. Dirígete a la sección de **Extensiones**.
2. [cite_start]Busca **"platformio"** e instala la extensión oficial.

### Configuración de Python
Si PlatformIO no detecta Python automáticamente, es posible que debas instalarlo manualmente:

* **En Linux:**
  ```bash
  sudo apt install python3
  sudo apt install python3-venv
  [cite_start]``` 
* **En Windows:**
  Descarga el instalador desde [python.org](https://www.python.org/downloads/windows/) y asegúrate de marcar la opción para **agregar Python al PATH** durante la instalación.

## 3. Configuración del Proyecto
Con la instalación finalizada, puedes iniciar un proyecto utilizando un archivo `platformio.ini` con la siguiente configuración base:

```ini
[env:ATmega328P]
platform = atmelavr
board = uno
framework = arduino
build_type = debug
extra_scripts = post:scripts/copy_sources_for_proteus.py
[cite_start]
``` 

### Descarga del proyecto base
Puedes obtener el proyecto base desde este enlace de [GitHub](https://github.com/AndyPecotche/CDyMC-temp/archive/5b8f4ef347cc84534499874ecf4e2d45f3614554.zip).

## 4. Uso de la Interfaz
1. Abre el proyecto desde **File → Open folder**.
2. Accede al icono de la extensión de PlatformIO para cargar las opciones de la plataforma.
3. En la interfaz encontrarás iconos para:
   * **Compilación (Checkmark)**.
   * **Grabar programa en Arduino (Flecha)**.
   * **Limpiar builds (Tacho de basura):** Se recomienda usar esta opción antes de compilar y grabar para evitar cargar versiones antiguas.
   * **Terminal serie (Icono de enchufe/monitor)**.

## 5. Simulación y Archivos Compilados
El archivo compilado `firmware.elf` se genera en la ruta `demo/.pio/build/ATmega328P`. 

Si utilizas el proyecto base del enlace, un script de post-build (`copy_sources_for_proteus.py`) copiará automáticamente los archivos `.c` y `.h` de la carpeta `src` a la carpeta del build. Esto facilita el acceso al código fuente durante las simulaciones en **Proteus**.
