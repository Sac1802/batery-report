# batery-report

`batery-report` es una herramienta de monitoreo de batería para sistemas Linux, escrita en C. Proporciona una vista en tiempo real del estado de la batería directamente en tu terminal, utilizando la biblioteca `ncurses` para una interfaz clara y organizada.

## Para qué sirve

El propósito principal de `batery-report` es ofrecer una visión detallada del estado de la batería de tu portátil. La herramienta lee información directamente de los archivos del sistema en `/sys/class/power_supply/` y `/proc/`, presentando datos como:

-   **Nivel de Carga:** Porcentaje actual de la batería con una barra de estado visual.
-   **Información General:** Estado (cargando, descargando), nivel de capacidad y modelo de la batería.
-   **Datos de Energía:** Voltaje actual, energía máxima, energía de diseño y energía actual.
-   **Datos Técnicos:** Ciclos de carga, voltaje mínimo de diseño y consumo por hora.

## Instalación

Este proyecto utiliza un `PKGBUILD` para facilitar la construcción e instalación en distribuciones basadas en Arch Linux.

Para construir e instalar el paquete, simplemente ejecuta el siguiente comando en la raíz del proyecto:

```bash
makepkg -si
```

## Uso

### Ejecución Directa

Una vez instalado a través de `makepkg`, el ejecutable estará disponible en tu `PATH`. Puedes iniciarlo simplemente con:

```bash
batery-report
```

### Compilación Manual

Si prefieres compilar y ejecutar el programa manualmente, puedes usar `gcc`:

```bash
# Compilar el programa
gcc batery.c -o batery-report -lncurses

# Ejecutar el monitor
./batery-report
```

Para salir del monitor, presiona `Ctrl + C`.

## Próximas Funcionalidades

Se planea expandir `batery-report` para incluir las siguientes características:

-   **Análisis Profundo:** Implementar una lógica más detallada para analizar la salud de la batería, su degradación a lo largo del tiempo y otros atributos avanzados para un diagnóstico completo.
-   **Generación de Reportes en HTML:** Añadir la capacidad de exportar los datos recopilados a un reporte visual en formato HTML, facilitando su lectura, almacenamiento y compartición.
