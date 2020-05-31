#include "PrefixTickLabels.h"

#include <cmath>

// Construction

const QString PrefixTickLabels::s_unitSpace(" "); // thin space

PrefixTickLabels::PrefixTickLabels(const double min, const double max, const unsigned targetNbTicks, const QString &unit)
    : m_unit(unit)
{
    const double range = std::abs(max - min);
    const double mid = (min + max)/2;

    const auto range_10 = static_cast<int>(floor(log10(range))) - (log10(range) <= 0.0 ? 1 : 0);

    const int scale_10 = s_group_10 * static_cast<int>((range_10 - (range_10 < 0 ? s_group_10 - 1 : 0 ))/ s_group_10);
    const double inv_scale = pow(10, -scale_10);

    m_prefix_10 = scale_10 + s_group_10;
    const double prefix_power = pow(10, m_prefix_10);

    // Prefer the left most prefix in range
    std::vector<double> prefixCandidates {
        ceil(min / prefix_power) * prefix_power,
        floor(mid / prefix_power) * prefix_power,
        floor(max / prefix_power) * prefix_power,
    };
    std::sort(prefixCandidates.begin(), prefixCandidates.end());
    const auto prefixCandidate = std::find_if(prefixCandidates.begin(), prefixCandidates.end(), [min, max](const double candidate) {
        return min <= candidate && candidate <= max;
    });
    if (prefixCandidate != prefixCandidates.end())
    {
        m_prefixValue = *prefixCandidate;
    }
    else
    {
        // .. if none found, take the left most
        m_prefixValue = prefixCandidates.front();
    }

    const double spacing = niceNum(range / targetNbTicks);
    const int labelFraction_10 = std::max(0, scale_10 - static_cast<int>(floor(log10(spacing))));

    const double niceMin = ceil(min / spacing) * spacing;
    const int nbTicks = static_cast<int>(floor((max - niceMin) / spacing));

    const auto siPrefix = PrefixTickLabels::siPrefix(scale_10);
    m_ticksAndLabels.reserve(nbTicks);
    for (int j = 0; j <= nbTicks; j++)
    {
        const double tick = niceMin + j * spacing;
        const auto tickLabel = QString(QLatin1String("%1%2%3%4"))
                                   .arg((tick - m_prefixValue) * inv_scale, 0, 'f', labelFraction_10)
                                   .arg(m_unit.isEmpty() ? QString() : s_unitSpace, tick != 0.0 ? siPrefix : QString(), m_unit);
        m_ticksAndLabels.push_back({ tick, tickLabel });
    }
}


// Prefix

bool PrefixTickLabels::hasPrefix() const
{
    return m_prefixValue != 0.0;
}

double PrefixTickLabels::prefixValue() const
{
    return m_prefixValue;
}

QString PrefixTickLabels::prefixLabel(const QString &placeholder) const
{
    if (!hasPrefix())
    {
        return {};
    }

    return prefixLabelLeading() + placeholder + prefixLabelTrailing();
}

QString PrefixTickLabels::prefixLabelLeading() const
{
    if (!hasPrefix())
    {
        return {};
    }

    if (m_prefix_10 > 1)
    {
        return QString::number(static_cast<int>(floor(m_prefixValue/pow(10, s_group_10))));
    }
    if (m_prefix_10 == 0)
    {
        return QString::number(static_cast<int>(floor(m_prefixValue))) + QLatin1Char('.');
    }

    return QString(QLatin1String("%1")).arg(m_prefixValue, 0, 'f', -m_prefix_10);
}

QString PrefixTickLabels::prefixLabelTrailing() const
{
    if (!hasPrefix())
    {
        return {};
    }

    return m_unit.isEmpty() ? "" : s_unitSpace + m_unit;
}


// Ticks

const PrefixTickLabels::TicksAndLabel &PrefixTickLabels::ticksAndLabel() const
{
    return m_ticksAndLabels;
}


// Utility

double PrefixTickLabels::niceNum(double value)
{
    const auto value_10 = static_cast<int>(floor(log10(value)));
    const auto fraction = value * pow(10, -value_10);

    int niceFraction = 10;
    if (fraction <= 1.0)
    {
        niceFraction = 1;
    }
    else if (fraction <= 2.0)
    {
        niceFraction = 2;
    }
    else if (fraction <= 5.0)
    {
        niceFraction = 5;
    }

    return niceFraction * pow(10, value_10);
}

QString PrefixTickLabels::siPrefix(int power)
{
    switch(power)
    {
    case 24: return QStringLiteral("Y"); //yotta
    case 21: return QStringLiteral("Z"); // zetta
    case 18: return QStringLiteral("E"); // exa
    case 15: return QStringLiteral("P"); // peta
    case 12: return QStringLiteral("T"); // tera
    case 9: return QStringLiteral("G"); // giga
    case 6: return QStringLiteral("M"); // mega
    case 3: return QStringLiteral("k"); // kilo
    case 2: return QStringLiteral("h"); // hecto
    case 1: return QStringLiteral("da"); // deca
    case 0: return {};
    case -1: return QStringLiteral("d"); // deci
    case -2: return QStringLiteral("c"); // centi
    case -3: return QStringLiteral("m"); // milli
    case -6: return QStringLiteral("µ"); // micro
    case -9: return QStringLiteral("n"); // nano
    case -12: return QStringLiteral("p"); // pico
    case -15: return QStringLiteral("f"); // femto
    case -18: return QStringLiteral("a"); // atto
    case -21: return QStringLiteral("z"); // zepto
    case -24: return QStringLiteral("y"); // tocto
    }
    return QLatin1String("?");
}
