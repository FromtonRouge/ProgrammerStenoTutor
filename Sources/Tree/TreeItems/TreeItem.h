// ======================================================================
// This file is a part of the ProgrammerStenoTutor project
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

#include <QtGui/QStandardItem>

class AttributeTreeItem;
struct TreeItem : public QStandardItem
{
    enum Type
    {
        // Generic
        Empty = UserType,
        List,
        Value,
        Attribute,

        // Keyboard
        Keyboard,
        Keycap,

        // Theory
        Theory,
        LinkedTheory,
        LinkedDictionary,
        OutputText,
        InputKeys,
        Dictionary,

        // Lessons
        Course,
        Lesson,
    };

    virtual int type() const override = 0;
    virtual AttributeTreeItem* addAttribute(const QString& sName, const QVariant& value);
};

struct EmptyTreeItem : public TreeItem
{
    EmptyTreeItem() {setEditable(false); setSelectable(false);}
    virtual int type() const override {return Empty;}
};