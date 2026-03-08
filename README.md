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

<img width="1148" height="622" alt="image" src="https://github.com/user-attachments/assets/f11e7f18-f3a4-4873-bb5e-03187992ddf3" />

### Configuración de Python
Si PlatformIO no detecta Python automáticamente, es posible que debas instalarlo manualmente:

* **En Linux:**
  ```bash
  sudo apt install python3
  sudo apt install python3-venv
  ``` 
* **En Windows:**
  Descarga el instalador desde [python.org](https://www.python.org/downloads/windows/) y asegúrate de marcar la opción para **agregar Python al PATH** durante la instalación.

<img width="1148" height="622" alt="image" src="https://github.com/user-attachments/assets/f3f9c791-ca7c-4355-8429-060f489069fc" />

## 3. Configuración del Proyecto
Con la instalación finalizada, puedes iniciar un proyecto utilizando un archivo `platformio.ini` con la siguiente configuración base:

```ini
[env:ATmega328P]
platform = atmelavr
board = uno
framework = arduino
build_type = debug
extra_scripts = post:scripts/copy_sources_for_proteus.py
``` 

### Descarga del proyecto base
Puedes obtener el proyecto base desde este enlace de [GitHub](https://github.com/AndyPecotche/CDyMC-temp/archive/5b8f4ef347cc84534499874ecf4e2d45f3614554.zip).

<img width="1148" height="622" alt="image" src="https://github.com/user-attachments/assets/53e6b75a-e8f5-440d-8297-a53457da11a5" />

## 4. Uso de la Interfaz
1. Abre el proyecto desde **File → Open folder**.
2. Accede al icono de la extensión de PlatformIO para cargar las opciones de la plataforma.

<img width="1148" height="622" alt="image" src="https://github.com/user-attachments/assets/759200f2-7723-4445-b7eb-f472efd49e32" />

4. En la interfaz encontrarás iconos para:
   * **Compilación (Checkmark)**.
   * **Grabar programa en Arduino (Flecha)**.
   * **Limpiar builds (Tacho de basura):** Se recomienda usar esta opción antes de compilar y grabar para evitar cargar versiones antiguas.
   * **Terminal serie (Icono de enchufe/monitor)**.

<img width="1148" height="622" alt="image" src="https://github.com/user-attachments/assets/3a72d2e2-ba41-422b-ba83-8087987a439c" />

## 5. Simulación y Archivos Compilados
El archivo compilado `firmware.elf` se genera en la ruta `template/.pio/build/ATmega328P`. 

Es recomendable antes de grabar un nuevo programa en la placa, darle a clean (icono del tacho de basura), antes de compilar ya que a veces sino se graba nuevamente el programa viejo.

Si utilizas el proyecto base del enlace, un script de post-build (`copy_sources_for_proteus.py`) copiará automáticamente los archivos `.c` y `.h` de la carpeta `src` a la carpeta del build. Teniendo los archivos originales en una carpeta src junto al archivo .elf, nos permite poder acceder al código desde simulaciones en **proteus**.
