#include "PrefixTickLabelsModel.h"

#include "PrefixTickLabels.h"

#include <QDebug>

// Configuration

double PrefixTickLabelsModel::min() const
{
    return m_min;
}
void PrefixTickLabelsModel::setMin(double min)
{
    m_min = min;
    emit minChanged();
    updateTicks();
}

double PrefixTickLabelsModel::max() const
{
    return m_max;
}
void PrefixTickLabelsModel::setMax(double max)
{
    m_max = max;
    emit maxChanged();
    updateTicks();
}

int PrefixTickLabelsModel::targetNbTicks() const
{
    return m_targetNbTicks;
}
void PrefixTickLabelsModel::setTargetNbTicks(int targetNbTicks)
{
    m_targetNbTicks = targetNbTicks;
    emit targetNbTicksChanged();
    updateTicks();
}

QString PrefixTickLabelsModel::unit() const
{
    return m_unit;
}
void PrefixTickLabelsModel::setUnit(const QString &unit)
{
    m_unit = unit;
    emit unitChanged();
}


// Prefix

bool PrefixTickLabelsModel::hasPrefix() const
{
    return m_hasPrefix;
}
double PrefixTickLabelsModel::prefix() const
{
    return m_prefix;
}
QString PrefixTickLabelsModel::prefixLabelLeading() const
{
    return m_prefixLabelLeading;
}
QString PrefixTickLabelsModel::prefixLabelTrailing() const
{
    return m_prefixLabelTrailing;
}

QString PrefixTickLabelsModel::prefixPlaceholder() const
{
    return m_prefixPlaceholder;
}

void PrefixTickLabelsModel::setHasPrefix(bool hasPrefix)
{
    if (m_hasPrefix != hasPrefix)
    {
        m_hasPrefix = hasPrefix;
        emit hasPrefixChanged();
    }
}
void PrefixTickLabelsModel::setPrefix(double prefix)
{
    m_prefix = prefix;
    emit prefixChanged();
}

void PrefixTickLabelsModel::setPrefixLabelLeading(const QString &prefixLabelLeading)
{
    if (m_prefixLabelLeading != prefixLabelLeading)
    {
        m_prefixLabelLeading = prefixLabelLeading;
        emit prefixLabelLeadingChanged();
    }
}
void PrefixTickLabelsModel::setPrefixLabelTrailing(const QString &prefixLabelTrailing)
{
    if (m_prefixLabelTrailing != prefixLabelTrailing)
    {
        m_prefixLabelTrailing = prefixLabelTrailing;
        emit prefixLabelTrailingChanged();
    }
}

void PrefixTickLabelsModel::setPrefixPlaceHolder(const QString &placeholder)
{
    if (m_prefixPlaceholder != placeholder)
    {
        m_prefixPlaceholder = placeholder;
        emit prefixPlaceholderChanged();
    }
}



// Ticks

int PrefixTickLabelsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_ticksAndLabels.count();
}

QVariant PrefixTickLabelsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return {};
    }

    switch (role)
    {
    case tickRole:
        return m_ticksAndLabels[index.row()].first;
    case labelRole:
        return m_ticksAndLabels[index.row()].second;
    }
    return {};
}

QHash<int, QByteArray> PrefixTickLabelsModel::roleNames() const
{
    return {{tickRole, "tick"}, {labelRole, "label"}};
}
void PrefixTickLabelsModel::setTicksAndLabels(const PrefixTickLabelsModel::TicksAndLabels &ticksAndLabels)
{
    beginResetModel();
    m_ticksAndLabels = ticksAndLabels;
    endResetModel();
}


// PrefixTickLabels

void PrefixTickLabelsModel::updateTicks()
{
    if (min() == max())
    {
        return;
    }

    const PrefixTickLabels ptl(min(), max(), static_cast<unsigned>(targetNbTicks()), unit());
    setHasPrefix(ptl.hasPrefix());
    setPrefix(ptl.prefixValue());
    setPrefixLabelLeading(ptl.prefixLabelLeading());
    setPrefixLabelTrailing(ptl.prefixLabelTrailing());
    setTicksAndLabels(ptl.ticksAndLabel());
}

