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

#include "OutputTextTreeItem.h"
#include <QtGui/QIcon>

OutputTextTreeItem::OutputTextTreeItem(const QString& sOutputText)
{
    setEditable(false);
    setToolTip(QObject::tr("Output text"));
    setOutputText(sOutputText);
}

OutputTextTreeItem::~OutputTextTreeItem()
{

}

QString OutputTextTreeItem::getOutputText() const
{
    return text();
}

void OutputTextTreeItem::setOutputText(const QString& sOutputText)
{
    QString sIcon(":/Icons/edit.png");
    QString sText = sOutputText;
    if (sText.isEmpty())
    {
        sIcon = (":/Icons/question.png");
        sText = "<no_entry>";
    }
    setIcon(QIcon(sIcon));
    setText(sText);
}
