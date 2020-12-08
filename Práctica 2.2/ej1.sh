# Información extraída de man ls
ls -a   # Incluye en el listado ficheros cuyos nombres empiecen por `.' (incluye los directorios . (actual) y .. (padre))
ls -l   # Escribe (en formato de una sola columna) los permisos del fichero, el número de enlaces que tiene, el nombre del propietario, el del grupo al que pertenece, el tamaño (en bytes),
              #una marca de tiempo, y el nombre del fichero.  De forma predeterminada, la marca de tiempo que se muestra es la de la última modificación; las opciones -c y  -u  seleccionan  las
              #otras dos que hay.  Para ficheros especiales de dispositivo el campo de tamaño se reemplaza comúnmente por los números de dispositivo mayor y menor
ls -d   # Lista nombres de directorios como otros ficheros, en vez de listar sus contenidos
ls -h   # Añade una letra indicativa de tamaño, tal como M para megabytes binarios (`mebibytes'), a cada tamaño
ls -i   # Muestra el número de nodo-í (también llamado el número de serie del fichero o el número índice o número-í) de cada fichero a la izquierda de su nombre. (Este número identifica de
              #forma inequívoca a cada fichero dentro de un sistema de ficheros particular.)
ls -R   # Lista recursivamente los subdirectorios encontrados
ls -1   # Lista recursivamente los subdirectorios encontrados.
ls -F   # Añade tras cada nombre de directorio un `/', tras cada nombre de FIFO un `|', y tras cada nombre de un ejecutable un `*'
ls --color  # Especifica  si emplear color para distinguir tipos de ficheros