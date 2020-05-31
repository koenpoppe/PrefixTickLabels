#ifndef PREFIXTICKLABELSMODEL_H
#define PREFIXTICKLABELSMODEL_H

#include <QAbstractListModel>

class PrefixTickLabelsModel : public QAbstractListModel
{
    Q_OBJECT

    // Construction
public:
    using QAbstractListModel::QAbstractListModel;


    // Configuration
public:
    Q_PROPERTY(double min READ min WRITE setMin NOTIFY minChanged)
    Q_PROPERTY(double max READ max WRITE setMax NOTIFY maxChanged)
    Q_PROPERTY(int targetNbTicks READ targetNbTicks WRITE setTargetNbTicks NOTIFY targetNbTicksChanged)
    Q_PROPERTY(QString unit READ unit WRITE setUnit NOTIFY unitChanged)

    double min() const;
    void setMin(double min);
    double max() const;
    void setMax(double max);
    int targetNbTicks() const;
    void setTargetNbTicks(int targetNbTicks);
    QString unit() const;
    void setUnit(const QString &unit);
signals:
    void minChanged();
    void maxChanged();
    void targetNbTicksChanged();
    void unitChanged();
private:
    double m_min = 0;
    double m_max = 1;
    int m_targetNbTicks = 10;
    QString m_unit;


    // Prefix
public:
    Q_PROPERTY(bool hasPrefix READ hasPrefix NOTIFY hasPrefixChanged)
    Q_PROPERTY(double prefix READ prefix NOTIFY prefixChanged)
    Q_PROPERTY(QString prefixLabelLeading READ prefixLabelLeading NOTIFY prefixLabelLeadingChanged)
    Q_PROPERTY(QString prefixLabelTrailing READ prefixLabelTrailing NOTIFY prefixLabelTrailingChanged)
    Q_PROPERTY(QString prefixPlaceholder READ prefixPlaceholder WRITE setPrefixPlaceHolder NOTIFY prefixPlaceholderChanged)
    bool hasPrefix() const;
    double prefix() const;
    QString prefixLabelLeading() const;
    QString prefixLabelTrailing() const;
    QString prefixPlaceholder() const;
    void setPrefixPlaceHolder(const QString &placeholder);
signals:
    void hasPrefixChanged();
    void prefixChanged();
    void prefixLabelLeadingChanged();
    void prefixLabelTrailingChanged();
    void prefixPlaceholderChanged();
protected:
    void setHasPrefix(bool hasPrefix);
    void setPrefix(double prefix);
    void setPrefixLabelLeading(const QString &prefixLabelLeading);
    void setPrefixLabelTrailing(const QString &prefixLabelTrailing);
private:
    bool m_hasPrefix = false;
    double m_prefix = 0.0;
    QString m_prefixLabelLeading;
    QString m_prefixLabelTrailing;
    QString m_prefixPlaceholder;


    // Ticks
public:
    enum RoleNames {
        tickRole = Qt::UserRole + 1,
        labelRole,
    };
    int rowCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;
protected:
    using TicksAndLabels = QVector<QPair<double, QString>>;
    void setTicksAndLabels(const TicksAndLabels &ticksAndLabels);
private:
    TicksAndLabels m_ticksAndLabels;


    // PrefixTickLabels
protected:
    void updateTicks();
};

#endif // PREFIXTICKLABELSMODEL_H
