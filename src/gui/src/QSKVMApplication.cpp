/*
 * SKVM -- mouse and keyboard sharing utility
 * Copyright (C) 2022 Serhii Hadzhilov.
 * Copyright (C) 2012-2016 Symless Ltd.
 * Copyright (C) 2008 Volker Lanz (vl@fidra.de)
 *
 * This package is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * found in the file LICENSE that should have accompanied this file.
 *
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "QSKVMApplication.h"
#include "MainWindow.h"

#include <QtCore>
#include <QtGui>

QSKVMApplication* QSKVMApplication::s_Instance = nullptr;

QSKVMApplication::QSKVMApplication(int& argc, char** argv) :
    QApplication(argc, argv)
{
    registerFonts();
    s_Instance = this;
}

void QSKVMApplication::commitData(QSessionManager&)
{
    auto widgets = topLevelWidgets();
    for (auto widget : qAsConst(widgets)) {
        auto mainWindow = qobject_cast<MainWindow*>(widget);
        if (mainWindow) {
            mainWindow->saveSettings();
        }
    }
}

QSKVMApplication* QSKVMApplication::getInstance()
{
    return s_Instance;
}

void QSKVMApplication::registerFonts()
{
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Regular.ttf");
    QFontDatabase::addApplicationFont(":/fonts/Roboto-Bold.ttf");

    QFont defaultFront;
    defaultFront.setFamily("Roboto-Regular");
    defaultFront.setPointSize(8);
#ifdef Q_OS_MAC
    defaultFront.setPointSize(12);
#endif
    setFont(defaultFront);
}

void QSKVMApplication::switchTranslator(QString lang)
{
    if (_translator) {
        removeTranslator(_translator.get());
        _translator.reset();
    }

    QResource locale(":/res/lang/gui_" + lang + ".qm");
    _translator = std::make_unique<QTranslator>();
    _translator->load(locale.data(), locale.size());
    installTranslator(_translator.get());
}

void QSKVMApplication::setTranslator(QTranslator* translator)
{
    _translator.reset(translator);
    installTranslator(_translator.get());
}
