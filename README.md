
<p align="center">
  <img alt="FlowForm" src="https://github.com/mtaurian/TLA_TP/blob/development/doc/asset/ff_logo.png">
</p>


# FlowForm Compiler

Un compilador construido a partir de https://github.com/agustin-golmar/Flex-Bison-Compiler.
FlowForm busca facilitar la creación de formularios y permite otorgarle mayor personalización al mismo. FlowForm genera un archivo HTML que contiene todo lo necesario para que al abrirlo sea un formulario con estilos predefinidos inspirados en Taylor Swift. 

## Construcción:

Para construir el proyecto por completo, ejecute:

En Linux:

    script/ubuntu/build.sh 

En Windows:

    script\windows\build.bat

## Testing:

Para correr todos los tests del proyecto, ejecute:

En Linux:

    script/ubuntu/test.sh

En Windows:

    script\windows\test.bat

## Ejecución:

Para correr un programa, ejecute:

En Linux:

    script/ubuntu/start.sh <path del programa>

En Windows:

    script\windows\start.bat <path del programa>

---

### Archivos de salida:
Los archivos generados por el compilador se encuentran en una carpeta llamada "FlowForm".
- El archivo "Form.html" contendrá el HTML, JavaScript y CSS correspondiente al formulario.
- El archivo "Form.gs" [cuando aplique] contendrá el código necesario para deployar el formulario en GoogleScripts. Para más información, leer la sección Adicionales del informe en "doc/TLA TPE - FlowForm - Stage III.pdf"

---

### Librerías externas:
- Hashmap: https://github.com/tidwall/hashmap.c

---

## Autores:

| Nombre | Legajo |
| ------ | ------ |
| Badin, Diego | 63551 |
| Rabinovich, Diego | 63155 |
| Taurian, Magdalena | 62828 |
