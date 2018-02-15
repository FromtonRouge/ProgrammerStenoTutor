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

#include "MainTabDialog.h"
#include "ui_MainTabDialog.h"
#include <QtWidgets/QMainWindow>
#include <QtCore/QSettings>

MainTabDialog::MainTabDialog(QWidget* pParent)
    : QDialog(pParent)
    , _pUi(new Ui::MainTabDialog)
{
    _pUi->setupUi(this);
    setWindowFlags(Qt::Window);
}

MainTabDialog::~MainTabDialog()
{
}

QTabWidget*MainTabDialog::getTabWidget() const
{
    return _pUi->tabWidget;
}

void MainTabDialog::closeEvent(QCloseEvent* pEvent)
{
    QSettings settings;
    settings.setValue("MainTabDialog/geometry", saveGeometry());
    auto pMainWindow = qobject_cast<QMainWindow*>(_pUi->tabWidget->widget(0)->layout()->itemAt(0)->widget());
    if (pMainWindow)
    {
        settings.setValue("windowState", pMainWindow->saveState());
    }
    QDialog::closeEvent(pEvent);
}
