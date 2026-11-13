#ifndef ESMFILE_H
#define ESMFILE_H

#include <QObject>
#include <iosfwd>  // Pour std::ostream
#include <QString>
#include <QVector>
#include <QSharedPointer>
#include <QLabel>
#include <QVBoxLayout>  // Inclure le layout nécessaire


class TopLevelBlock; // Forward declaration

class EsmFile : public QObject {
    Q_OBJECT  // Nécessaire pour utiliser tr()

public:
    EsmFile(const QString& filename);  // Constructeur

    // Membres
    QByteArray fileData;
    QVector<QSharedPointer<TopLevelBlock>> blocks;
    QList<QByteArray*> blockData;
    QString getErrors() const { return errors; }
    QString errorLog() const;
    QString suggestTitle() const;
    QString suggestFileName() const;

    friend class Reporter; // Si Reporter est dans le même namespace ou global, sinon précisez
    friend std::ostream& operator<<(std::ostream& os, const EsmFile& e); // opérateur de flux

public:
    void printOn(class Reporter& o) const; // Notez que Reporter est déclaré plus tard
    QString errors;

    // Méthode d'exemple où vous pouvez utiliser tr()
    void createLabel(QWidget* parent) {
        // Crée un QLabel avec traduction
        QLabel* label = new QLabel(tr("Test translation"), parent);

        // Utilisez un layout pour ajouter le label à un parent
        QVBoxLayout* layout = new QVBoxLayout(parent);
        layout->addWidget(label);

        parent->setLayout(layout);  // Assurez-vous que le layout est défini sur le parent
    }
};


// Déclaration de l'opérateur en dehors du namespace (si vous préférez)
std::ostream& operator<<(std::ostream& os, const EsmFile& e);

#endif // ESMFILE_H
