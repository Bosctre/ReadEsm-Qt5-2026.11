/* file: scripts/generate_cardblocks.py
Minimal generator reading DataDefinitions.xml and emitting .h/.cpp stubs for CardBlocks.
Usage: python3 generate_cardblocks.py DataDefinitions.xml output_dir
*/

Lance le générateur pour produire tous les CardBlocks automatiquement :

python3 fileformat/Scripts/generate_cardblocks.py fileformat/DataDefinitions.xml

Le dossier generated/ contiendra des stubs .h/.cpp pour chaque CardBlock du XML