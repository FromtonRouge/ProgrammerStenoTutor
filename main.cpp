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

#include "MainWindow.h"
#include "ProjectConfig.h"
#include <QtWidgets/QApplication>
#include <QtCore/QCommandLineParser>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("FromtonRouge");
    QApplication::setApplicationName(PROJECT_APPLICATION_NAME);
    QApplication::setApplicationVersion(QString("v%1.%2.%3").arg(PROJECT_VERSION_MAJOR).arg(PROJECT_VERSION_MINOR).arg(PROJECT_VERSION_PATCH));

    QCommandLineParser parser;
    parser.setApplicationDescription(QObject::tr("Programmer Steno learning tool"));
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(a);

    MainWindow w;
    w.show();
    return a.exec();
}
