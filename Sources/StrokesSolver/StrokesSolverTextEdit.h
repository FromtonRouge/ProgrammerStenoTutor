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

#include "Theories/TheoryModel.h"
#include <QtWidgets/QTextEdit>
#include <QtGui/QColor>

class QTimer;
class StrokesSolverTextEdit : public QTextEdit
{
    Q_OBJECT

signals:
    void solverStarted() const;
    void dictionaryMatch(const QString& sDictionaryName, const QBitArray& inputsKeysBits) const;

public:
    StrokesSolverTextEdit(QWidget* pParent = nullptr);
    void setTrainingMode(bool);

protected slots:
    void onCursorPositionChanged();
    void onTimerSolve();

protected:
    virtual void keyPressEvent(QKeyEvent* pKeyEvent) override;

private:
    bool solve(QString sText, const TheoryModel::CacheDictionaries& cachedDictionaries, const QStringList& dictionaries) const;

private:
    bool _bTrainingMode;
    QColor _colorOk;
    QColor _colorWarning;
    QColor _colorError;
    QTimer* _pTimerSolve;
};
