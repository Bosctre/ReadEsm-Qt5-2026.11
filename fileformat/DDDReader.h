
#ifndef DDDREADER_H
#define DDDREADER_H

#include <QString>


// Lit un fichier DDD et retourne le résultat dans 'output'.
// Retourne true si la lecture est réussie, false sinon.
// En cas d'erreur, 'error' contient un message d'erreur.
bool readDDD(const QString& filePath, QString& error, QString& output);


#endif // DDDREADER_H