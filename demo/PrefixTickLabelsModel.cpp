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


// Prefix

bool PrefixTickLabelsModel::hasPrefix() const
{
    return m_hasPrefix;
}
double PrefixTickLabelsModel::prefix() const
{
    return m_prefix;
}
QString PrefixTickLabelsModel::prefixLabel() const
{
    return m_prefixLabel;
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
void PrefixTickLabelsModel::setPrefixLabel(const QString &prefixLabel)
{
    if (m_prefixLabel != prefixLabel)
    {
        m_prefixLabel = prefixLabel;
        emit prefixLabelChanged();
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

    const PrefixTickLabels ptl(min(), max(), static_cast<unsigned>(targetNbTicks()));
    setHasPrefix(ptl.hasPrefix());
    setPrefix(ptl.prefixValue());
    setPrefixLabel(ptl.prefixLabel(prefixPlaceholder()).remove(prefixPlaceholder()));
    setTicksAndLabels(ptl.ticksAndLabel());
}

