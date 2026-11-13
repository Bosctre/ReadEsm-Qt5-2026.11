#!/bin/bash

OUTPUT_FILE="/opt/readesm-fr.3.0/build/lupdate_files.txt"

# Supprime le fichier s'il existe déjà
rm -f "$OUTPUT_FILE"

# Ajoute les chemins des fichiers sources
find /opt/readesm-fr.3.0/fileformat -name "*.cpp" -o -name "*.h" >> "$OUTPUT_FILE"
find /opt/readesm-fr.3.0/gui -name "*.cpp" -o -name "*.h" >> "$OUTPUT_FILE"

# Affiche le contenu du fichier généré
echo "Contenu de $OUTPUT_FILE :"
cat "$OUTPUT_FILE"
