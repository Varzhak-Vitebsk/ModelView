#include "mystringlistmodel.h"

MyStringListModel::MyStringListModel(QObject *parent) : QAbstractListModel(parent)
{
}

MyStringListModel::MyStringListModel(const QStringList &strings, QObject *parent)
    : QAbstractListModel(parent), list(strings)
{
}

int MyStringListModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid()) return 0;
    return list.count();
}

QVariant MyStringListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= list.size()) return QVariant();
    if (role == Qt::DisplayRole || role == Qt::EditRole) return list.at(index.row());
    return QVariant();
    /*if(!index.isValid()) return QVariant();
    if(index.row() >= list.size()) return QVariant();
    return list.at(index.row());*/
}

bool MyStringListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

    if (index.row() >= 0 && index.row() < list.size()
        && (role == Qt::EditRole || role == Qt::DisplayRole))
    {
        list.replace(index.row(), value.toString());
        emit dataChanged(index, index);
        return true;
    }
    return false;
    /*if(!index.isValid()) return false;
    list.insert(index.row(), value.toString());*/
}

void MyStringListModel::setStringList(const QStringList &strings)
{
    emit beginResetModel();
    list = strings;
    emit endResetModel();
}

QStringList MyStringListModel::stringList()
{
    return list;
}
