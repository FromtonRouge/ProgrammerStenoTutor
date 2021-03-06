// ======================================================================
// This file is a part of the KaladriusTrainer project
//
// Copyright (C) 2020  Vissale NEANG <fromtonrouge at gmail dot com>
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// ======================================================================

#include "TextsModel.h"
#include "../Database/Database.h"
#include "../Main/Application.h"
#include <QtCore/QDebug>

TextsModel::TextsModel(QObject* pParent)
    : QStandardItemModel(pParent)
{
}

void TextsModel::reset()
{
    clear();
}

bool TextsModel::hasChildren(const QModelIndex& parent) const
{
    auto pDatabase = qApp->getDatabase();
    if (!parent.isValid())
    {
        const int iCount = pDatabase->getCount("Text Files");
        return iCount > 0;
    }
    else if (!parent.parent().isValid())
    {
        return true;
    }
    return false;
}

bool TextsModel::canFetchMore(const QModelIndex& parent) const
{
    auto pDatabase = qApp->getDatabase();
    if (!parent.isValid())
    {
        const int iCount = pDatabase->getCount("Text Files");
        if (invisibleRootItem()->rowCount() < iCount)
        {
            return true;
        }
    }
    else
    {
        if (!parent.parent().isValid())
        {
            const int iTextFileId = parent.data(Qt::UserRole + 1).toInt();

            QString sQuery = "SELECT COUNT(Id) FROM \"Texts\" WHERE TextFileId == %1";
            sQuery = sQuery.arg(iTextFileId);
            QSqlQuery query = pDatabase->execute(sQuery);
            if (query.next())
            {
                const int iCount = query.value(0).toInt();
                if (itemFromIndex(parent)->rowCount() < iCount)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void TextsModel::fetchMore(const QModelIndex& parent)
{
    auto pDatabase = qApp->getDatabase();
    if (!parent.isValid())
    {
        QString sQuery = "SELECT Id, Filename FROM \"Text Files\"";
        QSqlQuery query = pDatabase->execute(sQuery);
        while (query.next())
        {
            const int iTextFileId = query.value(0).toInt();
            const QString& sName = query.value(1).toString();
            QStandardItem* pItem = new QStandardItem(QIcon(":/Icons/book.png"), sName);
            pItem->setEditable(false);
            pItem->setData(iTextFileId);
            pItem->setCheckable(true);
            invisibleRootItem()->appendRow(pItem);
        }
    }
    else
    {
        if (!parent.parent().isValid())
        {
            const int iTextFileId = parent.data(Qt::UserRole + 1).toInt();

            QString sQuery = "SELECT Id, Enabled FROM \"Texts\" WHERE TextFileId == %1";
            sQuery = sQuery.arg(iTextFileId);
            QSqlQuery query = pDatabase->execute(sQuery);
            while (query.next())
            {
                const int iTextId = query.value(0).toInt();
                QStandardItem* pItem = new QStandardItem(QIcon(":/Icons/book-open-text.png"), QString());
                pItem->setEditable(false);
                pItem->setData(iTextId);
                pItem->setCheckable(true);
                itemFromIndex(parent)->appendRow(pItem);
            }
        }
    }
}

QVariant TextsModel::headerData(int iSection, Qt::Orientation, int iRole) const
{
    if (iSection == 0 && iRole == Qt::DisplayRole)
    {
        return "Texts";
    }
    return QVariant();
}

QVariant TextsModel::data(const QModelIndex& index, int iRole) const
{
    QVariant result = QStandardItemModel::data(index, iRole);

    auto pDatabase = qApp->getDatabase();

    if (index.parent().isValid())
    {
        auto pItem = itemFromIndex(index);
        const int iTextId = pItem->data().toInt();
        switch (iRole)
        {
        case Qt::DisplayRole:
            {
                result = QString("[%1] Text-%2").arg(index.row()).arg(iTextId);
                break;
            }
        case Qt::ToolTipRole:
            {
                result = QString("TextId = %1").arg(iTextId);
                break;
            }
        case Qt::CheckStateRole:
            {
                QString sQuery = "SELECT Enabled FROM \"Texts\" WHERE Id == %1";
                sQuery = sQuery.arg(iTextId);
                QSqlQuery query = pDatabase->execute(sQuery);
                Qt::CheckState checkState = Qt::Unchecked;
                if (query.next())
                {
                    checkState = query.value(0).toInt() == 1 ? Qt::Checked : Qt::Unchecked;
                }
                result = checkState;
                break;
            }
        default:
            {
                break;
            }
        }
    }
    else
    {
        switch (iRole)
        {
        case Qt::CheckStateRole:
            {
                int iTotalRows = 0;
                const int iTextFileId = index.data(Qt::UserRole + 1).toInt();
                QString sQuery = "SELECT COUNT(Id) FROM \"Texts\" WHERE TextFileId == %1";
                sQuery = sQuery.arg(iTextFileId);
                QSqlQuery query = pDatabase->execute(sQuery);
                if (query.next())
                {
                    iTotalRows = query.value(0).toInt();
                }

                int iEnabledRows = 0;
                sQuery = "SELECT COUNT(Id) FROM \"Texts\" WHERE TextFileId == %1 AND Enabled == 1";
                sQuery = sQuery.arg(iTextFileId);
                query = pDatabase->execute(sQuery);
                if (query.next())
                {
                    iEnabledRows = query.value(0).toInt();
                }

                if (iEnabledRows == 0)
                {
                    return Qt::Unchecked;
                }

                if (iTotalRows == iEnabledRows)
                {
                    return Qt::Checked;
                }

                return Qt::PartiallyChecked;
            }
        default:
            {
                break;
            }
        }
    }
    return result;
}

bool TextsModel::setData(const QModelIndex& index, const QVariant& value, int iRole)
{
    auto pDatabase = qApp->getDatabase();
    if (index.parent().isValid())
    {
        switch (iRole)
        {
        case Qt::CheckStateRole:
            {
                const int iTextId = index.data(Qt::UserRole + 1).toInt();
                QString sQuery = "UPDATE \"Texts\" SET Enabled = %1 WHERE Id == %2";
                sQuery = sQuery.arg(value.toInt() == 2 ? 1 : 0).arg(iTextId);
                pDatabase->execute(sQuery);
                emit dataChanged(index.parent(), index.parent(), {Qt::CheckStateRole});
                break;
            }
        default:
            {
                break;
            }
        }
    }
    else
    {
        switch (iRole)
        {
        case Qt::CheckStateRole:
            {
                const int iTextFileId = index.data(Qt::UserRole + 1).toInt();
                QString sQuery = "UPDATE \"Texts\" SET Enabled = %1 WHERE TextFileId == %2";
                sQuery = sQuery.arg(value.toInt() > 1 ? 1 : 0).arg(iTextFileId);
                pDatabase->execute(sQuery);
                const int iRows = rowCount();
                if (iRows)
                {
                    emit dataChanged(this->index(0, 0, index), this->index(iRows-1, 0, index), {Qt::CheckStateRole});
                }
                break;
            }
        default:
            {
                break;
            }
        }
    }

    return QStandardItemModel::setData(index, value, iRole);
}

bool TextsModel::removeRows(int iRow, int iCount, const QModelIndex& parent)
{
    const QString TEXT_LEVEL = "Text Level ab1575a2-c508-4565-8e25-3515c9e22aef";

    auto pDatabase = qApp->getDatabase();
    if (parent.isValid() == false)
    {
        // Remove Text files
        for (int i = iRow+iCount-1; i >= iRow ; --i)
        {
            const QModelIndex& indexToRemove = index(i, 0, parent);
            const int iTextFileId = indexToRemove.data(Qt::UserRole + 1).toInt();

            // Delete test results first
            QString sQuery = "DELETE FROM '%1' WHERE TextId IN (SELECT Id FROM 'Texts' WHERE TextFileId == %2)";
            sQuery = sQuery.arg(TEXT_LEVEL).arg(iTextFileId);
            pDatabase->execute(sQuery);

            // Delete texts
            sQuery = "DELETE FROM 'Texts' WHERE TextFileId == %1";
            sQuery = sQuery.arg(iTextFileId);
            pDatabase->execute(sQuery);

            // Delete text file
            sQuery = "DELETE FROM 'Text Files' WHERE Id == %1";
            sQuery = sQuery.arg(iTextFileId);
            pDatabase->execute(sQuery);
        }
    }
    else
    {
        // Remove Text
        QStringList textIds;
        for (int i = iRow+iCount-1; i >= iRow ; --i)
        {
            const QModelIndex& indexToRemove = index(i, 0, parent);
            const int iTextId = indexToRemove.data(Qt::UserRole + 1).toInt();
            textIds << QString::number(iTextId);
        }

        const QString& sTextIds = textIds.join(",");

        // Delete test results first
        QString sQuery = "DELETE FROM '%1' WHERE TextId IN (%2)";
        sQuery = sQuery.arg(TEXT_LEVEL).arg(sTextIds);
        pDatabase->execute(sQuery);

        // Delete text
        sQuery = "DELETE FROM 'Texts' WHERE Id IN (%1)";
        sQuery = sQuery.arg(sTextIds);
        pDatabase->execute(sQuery);
    }

    return QStandardItemModel::removeRows(iRow, iCount, parent);
}
