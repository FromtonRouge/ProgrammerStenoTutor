// ======================================================================
// This file is a part of the KaladriusTrainer project
//
// Copyright (C) 2017  Vissale NEANG <fromtonrouge at gmail dot com>
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

#pragma once

#include "../../Tree/TreeItems/TreeItem.h"
#include <QtCore/QStringList>
#include <QtCore/QUuid>

class LevelTreeItem : public TreeItem
{
public:
    enum LevelType
    {
        TimedRandomWords,
        FreeText,
    };

public:
    LevelTreeItem(LevelType levelType,
                  const QUuid& uuid,
                  const QString& sLabel,
                  const QString& sWordsFilePath);
    ~LevelTreeItem();

    virtual int type() const override {return Level;}
    void loadWords(const QString& sWordsFilePath);
    const QStringList& getWords() const {return _words;}
    QStringList getRandomWords(int iCount = 1000) const;
    const QUuid& getUuid() const {return _uuid;}

private:
    QUuid _uuid;
    LevelType _levelType;
    QStringList _words;
};
