#ifndef PREFIXTICKLABELS_H
#define PREFIXTICKLABELS_H

#include <QPair>
#include <QString>
#include <QVector>

class PrefixTickLabels
{
    // Construction
public:
    /**
     * @param min, lower limit of the range
     * @param max, upper limit of the range
     * @param targetNbTicks,
     * @param unit
     */
    PrefixTickLabels(double min, double max, unsigned targetNbTicks, const QString &unit = {});
private:
    const QString m_unit;
    static const QString s_unitSpace;
    static const int s_group_10 = 3; // Scientific notation is multiple of 3


    // Prefix
public:
    /** Is there a common value that can be used as prefix?
     */
    bool hasPrefix() const;
    /**
     * @pre hasPrefix()
     */
    double prefixValue() const;
    /** Textual representation of the prefix value
     * @pre hasPrefix()
     * @param placeholder, character used to indicate place of the ticks values
     */
    QString prefixLabel(const QString &placeholder = QLatin1String("xxx")) const;
    /// The part of the prefix label before the placeholder
    QString prefixLabelLeading() const;
    /// The part of the prefix label after the placeholder
    QString prefixLabelTrailing() const;
private:
    int m_prefix_10 = 0;
    double m_prefixValue = 0.0;
    QString m_prefixLabel;


    // Ticks
public:
    using TicksAndLabel = QVector<QPair<double, QString>>;
    const TicksAndLabel &ticksAndLabel() const;
private:
    TicksAndLabel m_ticksAndLabels;


    // Utility
public:
    /** Returns a power of 10 multiple of 1, 2 or 5 for the given value
     * @see "Nice Numbers for Graph Labels", Graphics Gems, Andrew S. Glassner, Elsevier Science, 1990
     */
    static double niceNum(double value);
    /** Prefix for the given power of 10
     * @param power
     * @returns "?" if there is no relevant prefix
     */
    static QString siPrefix(int power);
};

#endif // PREFIXTICKLABELS_H
