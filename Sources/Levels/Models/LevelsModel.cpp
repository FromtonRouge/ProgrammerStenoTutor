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

#include "LevelsModel.h"
#include "../TreeItems/LevelsTreeItem.h"
#include "../TreeItems/LevelTreeItem.h"

LevelsModel::LevelsModel(QObject* pParent)
    : TreeItemModel(pParent)
{
    setHorizontalHeaderLabels({tr("Name"), tr("Progress")});
    appendRow({new LevelsTreeItem()});
}

LevelsModel::~LevelsModel()
{

}

void LevelsModel::updateLevelDisplay(const QModelIndex& indexLevel)
{
    emit dataChanged(indexLevel.siblingAtColumn(0), indexLevel.siblingAtColumn(1), {Qt::DisplayRole});
}

QVariant LevelsModel::data(const QModelIndex& index, int iRole) const
{
    if (index.column() == 1 && iRole == Qt::DisplayRole)
    {
        const QModelIndex& indexFirstColumn = index.siblingAtColumn(0);
        const int iTreeItemType = indexFirstColumn.data(TreeItemTypeRole).toInt();
        if (iTreeItemType == TreeItem::Level)
        {
            auto pLevelTreeItem = static_cast<LevelTreeItem*>(itemFromIndex(indexFirstColumn));
            if (pLevelTreeItem->getLevelType() != LevelTreeItem::Text)
            {
                return QString("%1 %").arg(QString::number(pLevelTreeItem->getProgressionPercentage(), 'f', 1));
            }
        }
    }

    return TreeItemModel::data(index, iRole);
}
