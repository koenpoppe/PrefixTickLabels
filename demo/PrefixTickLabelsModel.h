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

    double min() const;
    void setMin(double min);
    double max() const;
    void setMax(double max);
    int targetNbTicks() const;
    void setTargetNbTicks(int targetNbTicks);
signals:
    void minChanged();
    void maxChanged();
    void targetNbTicksChanged();
private:
    double m_min = 0;
    double m_max = 1;
    int m_targetNbTicks = 10;


    // Prefix
public:
    Q_PROPERTY(bool hasPrefix READ hasPrefix NOTIFY hasPrefixChanged)
    Q_PROPERTY(double prefix READ prefix NOTIFY prefixChanged)
    Q_PROPERTY(QString prefixLabel READ prefixLabel NOTIFY prefixLabelChanged)
    Q_PROPERTY(QString prefixPlaceholder READ prefixPlaceholder WRITE setPrefixPlaceHolder NOTIFY prefixPlaceholderChanged)
    bool hasPrefix() const;
    double prefix() const;
    QString prefixLabel() const;
    QString prefixPlaceholder() const;
    void setPrefixPlaceHolder(const QString &placeholder);
signals:
    void hasPrefixChanged();
    void prefixChanged();
    void prefixLabelChanged();
    void prefixPlaceholderChanged();
protected:
    void setHasPrefix(bool hasPrefix);
    void setPrefix(double prefix);
    void setPrefixLabel(const QString &prefixLabel);
private:
    bool m_hasPrefix = false;
    double m_prefix = 0.0;
    QString m_prefixLabel;
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
