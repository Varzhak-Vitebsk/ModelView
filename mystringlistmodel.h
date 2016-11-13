#ifndef MYSTRINGLISTMODEL_H
#define MYSTRINGLISTMODEL_H

#include <QAbstractListModel>

class MyStringListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit MyStringListModel(QObject *parent = Q_NULLPTR);
    explicit MyStringListModel(const QStringList &strings, QObject *parent = Q_NULLPTR);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    void setStringList(const QStringList &strings);
    QStringList stringList();

private:
    QStringList list;

signals:

public slots:
};

#endif // MYSTRINGLISTMODEL_H
