#ifndef SVGDAYACTIVITY_H
#define SVGDAYACTIVITY_H

#include <QString>

/// Graphique SVG d'une journée (0 h -> 24 h). 1 minute = 0,5 px, axe de 720 px.
class SvgDayActivity {
public:
    /// from, duration : en minutes ; height : 0..1 (fraction de 80 px)
    void add(int from, int duration, float height, const QString& color, const QString& title);
    QString toString() const;

private:
    QString collected;   // rectangles déjà tracés
};

#endif // SVGDAYACTIVITY_H