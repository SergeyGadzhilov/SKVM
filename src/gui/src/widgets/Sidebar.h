/*
 * SKVM -- mouse and keyboard sharing utility
 * Copyright (C) 2024 Hadzhilov Serhii
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
#ifndef SKVM_SIDEBAR_H
#define SKVM_SIDEBAR_H

#include <QWidget>
#include <QVBoxLayout>
#include "sidebar/Button.h"

namespace skvm_widgets
{

class Sidebar : public QWidget
{
    Q_OBJECT
public:
    Sidebar(QWidget *parent = nullptr);

signals:
    void OpenHome();
    void OpenLogs();
    void OpenSettings();

private:
    void initLayout();
    void addBottomControls();
    void addButtonHome();
    void addButtonSettings();
    void addButtonLogs();
    void addButtonHelp();
    void activate(sidebar::Button* button);

    QVBoxLayout* m_layout = nullptr;
    sidebar::Button* m_activeButton = nullptr;
};

} //namespace skvm_widgets

#endif // SKVM_SIDEBAR_H
