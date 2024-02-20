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
#ifndef SKVM_WIDGETS_PAGES_SETTINGS_TAB_H
#define SKVM_WIDGETS_PAGES_SETTINGS_TAB_H

#include <QPushButton>

namespace skvm_widgets
{

namespace pages
{

namespace settings
{

class Tab : public QPushButton
{
    Q_OBJECT
public:
    Tab(QWidget *parent = nullptr, const QString& name = "");
    void Activate();
    void Deactivate();
};

} //namespace settings
} //namespace pages
} //namespace skvm_widgets

#endif // SKVM_WIDGETS_PAGES_SETTINGS_TAB_H
