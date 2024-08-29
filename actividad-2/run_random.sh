#!/bin/bash

# Seleccionar un archivo aleatorio de la carpeta tableros
random_file=$(ls tableros/ | shuf -n 1)

# Ejecutar ./correr.sh con el archivo seleccionado
make clean
./correr.sh "tableros/$random_file"

echo "tableros/$random_file"
cat "tableros/$random_file"
