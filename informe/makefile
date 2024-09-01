# Define el nombre base del archivo (sin extensión)
BASE = main

# Directorio de compilación
BUILD_DIR = build

# Regla por defecto
all: $(BUILD_DIR)/$(BASE).pdf

# Regla para generar el PDF
$(BUILD_DIR)/$(BASE).pdf: $(BASE).tex
	mkdir -p $(BUILD_DIR)
	pdflatex -output-directory=$(BUILD_DIR) $(BASE).tex
	pdflatex -output-directory=$(BUILD_DIR) $(BASE).tex  # Ejecutar de nuevo para asegurar referencias

# Regla para limpiar archivos generados
clean:
	rm -f $(BUILD_DIR)/*.pdf $(BUILD_DIR)/*.aux $(BUILD_DIR)/*.log $(BUILD_DIR)/*.out $(BUILD_DIR)/*.synctex.gz

# Regla para generar el índice (si es necesario)
index: $(BASE).tex
	# Aquí podrías añadir comandos para generar un índice si lo necesitas
