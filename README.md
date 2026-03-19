# Introducción al lenguaje C
- Become familiar with the use of the C languaje.
- Familiarize yourself with the linux console.
- Learn a little about the way Linux utilities are implemented.

## 🚀 Members
- Sebastian Andres Berrio Murillo, CC. 1066753315, sebastian.berriom@udea.edu.co.
- Sandy Dahiana Ruiz Higuita, CC. 1028031733, sandy.ruizh@udea.edu.co - sadrh97@gmail.com.

## Video: https://youtu.be/gatxD2ojayU

## Compilación

```bash
gcc wcat wcat.c
gcc wgrep wgrep.c
```

## wcat

Implementación simplificada de la utilidad Unix `cat`. Lee uno o más archivos y muestra su contenido por salida estándar.

### Uso

```bash
./wcat <archivo1> [archivo2] ... [archivoN]
```

### Comportamiento

- Recibe uno o más archivos como argumentos.
- Lee cada archivo secuencialmente y lo imprime en `stdout`.
- Usa un buffer fijo de 60 caracteres con `fgets`.

### Códigos de salida

| Código | Significado |
|--------|-------------|
| 0 | Ejecución exitosa |
| 1 | No se especificaron archivos o no se pudo abrir un archivo |

### Errores

- Sin argumentos: retorna 1 silenciosamente.
- Archivo no encontrado: imprime `wcat: cannot open file` y retorna 1.

### Ejemplo

```bash
./wcat archivo.txt
./wcat archivo1.txt archivo2.txt
```

---

## wgrep

Implementación simplificada de la utilidad Unix `grep`. Busca líneas que contengan un término dado en archivos o en la entrada estándar.

### Uso

```bash
./wgrep <término>                         # Lee desde stdin
./wgrep <término> <archivo1> [archivo2]   # Busca en archivos
```

### Comportamiento

- Búsqueda por subcadena usando `strstr` (sensible a mayúsculas/minúsculas).
- Si solo se pasa el término de búsqueda, lee desde `stdin` (Ctrl+D para terminar).
- Si se pasan archivos, busca en cada uno secuencialmente.
- Usa `getline` para lectura dinámica de líneas (sin límite de longitud).

### Funciones

| Función | Firma | Descripción |
|---------|-------|-------------|
| `main` | `int main(int argc, char *argv[])` | Punto de entrada, valida argumentos y gestiona archivos |
| `lines_reader` | `void lines_reader(const char *term, FILE *file)` | Lee líneas de un `FILE*` e imprime las que contienen el término |

### Códigos de salida

| Código | Significado |
|--------|-------------|
| 0 | Ejecución exitosa (incluso sin coincidencias) |
| 1 | Sin argumentos o no se pudo abrir un archivo |

### Errores

- Sin argumentos: imprime `wgrep: searchterm [file...]` y retorna 1.
- Archivo no encontrado: imprime `wgrep: cannot open file` y retorna 1.

### Ejemplo

```bash
./wgrep "hola" archivo.txt
echo "hola mundo" | ./wgrep "hola"
./wgrep "error" log1.txt log2.txt
```

## wzip

Implementación simplificada de una utilidad de compresión. Su función es comprimir uno o más archivos usando una técnica llamada Run-Length Encoding RLE. Esta técnica reduce el tamaño de archivos que tienen muchos caracteres repetidos seguidos.

### Uso

```bash
./wzip <archivo1> [archivo2] ... [archivoN]
```

Normalmente la salida se redirige a un archivo para guardar el resultado comprimido

```bash
./wzip archivo.txt >archivo.z
```

### Comportamiento

- Recibe uno o más archivos como argumentos.
- Lee cada archivo caracter por caracter.
- Cuenta cuántas veces aparece el mismo carácter de forma consecutiva
- Cuando el caracter cambia, guarda:
    - El número de repeticiones
    - El caracter repetido
- La información comprimida se escribe en `stdout` en formato binario

Por ejemplo si el archivo tiene: aaaaabbb

La compresión guarda algo equivalente a: 

5 a

3 b

Pero en realidad guarda en formato binario usando `fwrite`

### Códigos de salida

| Código | Significado |
|--------|-------------|
| 0 | Ejecución exitosa |
| 1 | No se especificaron archivos o no se pudo abrir un archivo |

### Errores

- Sin argumentos: imprime `wzip: file1 [file2 ...]` y retorna 1.
- Archivo no encontrado: imprime `wzip: cannot open file` y retorna 1.

### Ejemplo

```bash
./wzip archivo.txt > archivo.z
./wzip archivo1.txt archivo2.txt > comprimido.z
```

---

## wunzip

Implementación simplificada de una utilidad de descompresión. Este programa toma un archivo comprimido generado por `wzip` y reconstruye el contenido original.

### Uso

```bash
./wunzip <archivo_comprimido>
```

### Comportamiento

- Recibe uno o más archivos comprimidos como argumentos.
- Lee los datos en bloques que contienen.
    - El número de repeticiones
    - El caracter asociado
- Luego imprime ese carácter la cantidad de veces indicada
- La salida se escribe en `stdout` reconstruyendo el texto original

Por ejemplo si el archivo contiene información equivalente a:

5 a

3 b

El programa imprimirá: aaaaabbb 

### Códigos de salida

| Código | Significado |
|--------|-------------|
| 0 | Ejecución exitosa |
| 1 | No se especificaron archivos o no se pudo abrir un archivo |

### Errores

- Sin argumentos: imprime `wunzip: file1 [file2 ...]` y retorna 1.
- Archivo no encontrado: imprime `wunzip: cannot open file` y retorna 1.

### Ejemplo

```bash
./wunzip archivo.z
```

### Salida
```bash
aaaaabbb
```

---


## Problemas y soluciones durante el desarrollo

### wcat: Manejo del buffer y punteros con `fgets`

**Problema:** Comprender cómo `fgets` utiliza un puntero a un arreglo de caracteres (`char buffer[60]`) para almacenar los datos leídos del archivo. La confusión principal fue entender que `buffer` actúa como un puntero al inicio del arreglo y que `fgets` escribe directamente en esa zona de memoria, requiriendo definir un tamaño fijo que limita la cantidad de caracteres leídos por iteración.

**Solución:** Se revisó la documentación sobre arreglos y punteros en C para entender que el nombre del arreglo decae a un puntero (`char *`) al pasarse a `fgets`. Se definió un buffer de 60 caracteres y se iteró con `while` hasta alcanzar `EOF`, permitiendo que líneas más largas se lean en múltiples pasadas sin perder datos.

### wgrep: Punteros y memoria dinámica con `getline`

**Problema:** A diferencia de `wcat`, `wgrep` requería manejar líneas de longitud variable. Comprender cómo `getline` recibe un puntero a puntero (`char **line`) y un puntero a `size_t` para redimensionar el buffer dinámicamente fue el principal reto, ya que implica entender la indirección doble y la asignación de memoria en heap.

**Solución:** Se estudió el comportamiento de `getline`: al inicializar `line = NULL` y `tam = 0`, la función asigna memoria automáticamente con `malloc` y la redimensiona según sea necesario. Esto eliminó la limitación del buffer fijo y se liberó la memoria al final con `free(line)`.

### wzip: contar correctamente caracteres repetidos

**Problema:** Al implementar la compresión fue necesario entender cómo contar correctamente los caracteres repetidos mientras se lee el archivo carácter por carácter. También fue importante para nosotros manejar correctamente el momento en en que el caracter cambia para poder guardar esta información que se había comprimido.

**Solución:** Utilizamos `fgetc` para leer cada caracter del archivo y también un contador que se aumenta cuando el caracter leído es igual al anterior. Cuando el caracter cambia, se escribe la cantidad de repeticiones y el caracter, usando `fwrite`. Esto nos permitió guardar los datos en formato binario.

### wunzip: Lectura de datos binarios

**Problema:** En la función `wunzip` nuestro principal reto fue entender cómo leer correctamente los datos que fueron guardados por `wzip`. Como el archivo comprimido tiene números y caracteres almacenados en fomato binario, no se podía usar `fgetc` o `getline` como en las anteriores funciones.

**Solución:** Utilizamos la función `fread` para leer primero el número de repeticiones, que es un entero, y luego el caracter asociado. Esto nos permitió recuperar la información almacenada correctamente en el archivo comprimido.
