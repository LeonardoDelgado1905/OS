# OS

1. Lista enlazada del archivo bogota_cadastral... en archivo binario como lista enlazada de Estructura, añadiendo atributo (siguiente)
  * Add:
    1. Se lee un registro **i** del CSV (router **X**)
    2. Se busca en el arrelgo de **tails** dónde está ubicado el último registro con el mismo *sourceid* en el archivo binario(router **Y**), si no hay ninguno, significa que él(**X**) será el *head* de esa "lista" enlazada.
    3. Se actualiza el arreglo de **tails**
    4. Se modifica ese archivo binario añadiendo el atributo *next* al **Y** **(Y.next = i)**
    5. Se escribe **X** en el archivo binario.
 
3. Tabla Hash
4. Proceso de búsqueda + tiempo
5. Interfaz de usuario
6. Pipe (mkfifo) http://es.tldp.org/Universitarios/seminario-1.html
7. Makefile 
