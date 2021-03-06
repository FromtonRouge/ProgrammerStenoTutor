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

#pragma once

#include "../Main/MainTabWindow.h"
#include <QtCore/QScopedPointer>

namespace Ui
{
    class TextsManagerMainWindow;
}

class TextsModel;

class TextsManagerMainWindow : public MainTabWindow
{
    Q_OBJECT

signals:
    void sendText(int iTextId) const;

public:
    TextsManagerMainWindow(QWidget* pParent = nullptr);
    ~TextsManagerMainWindow();

    void Init() override;

protected slots:
    void on_actionAbout_triggered();
    void on_actionImport_Text_triggered();
    void on_actionImport_Directory_triggered();
    void on_actionImport_Default_Texts_triggered();

private:
    void importDirectory(const QString& sDirectory);
    void importTextFile(const QString& sFilePath);
    void importFiles(const QStringList& files);

private:
    QScopedPointer<Ui::TextsManagerMainWindow> _pUi;
    TextsModel* _pTextsModel = nullptr;
};

