#!/bin/bash

# Verificar si se ha proporcionado un argumento
if [ $# -eq 1 ]; then
  # Usar el archivo proporcionado como argumento
  archivo="$1"
else
  # Seleccionar un archivo aleatorio de la carpeta tableros
  archivo=tableros/$(ls tableros/ | shuf -n 1)
fi

# Mostrar el contenido del archivo seleccionado
cat "$archivo"

# Esperar a que el usuario presione Enter
# read -p "Presiona Enter para continuar..."

make clean
make robot
valgrind --leak-check=full --track-origins=yes --show-leak-kinds=all -s ./robot "$archivo"

echo "Archivo seleccionado: $archivo"
