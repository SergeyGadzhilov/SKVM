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
#include "Tab.h"
#include <QStyle>

namespace skvm_widgets
{

namespace pages
{

namespace settings
{

Tab::Tab(QWidget *parent, const QString& name) :
    QPushButton(parent)
{
    setFixedHeight(49);
    setFixedWidth(150);
    setText(name);
    setCursor(Qt::PointingHandCursor);
    Deactivate();
}

void Tab::Activate()
{
    setStyleSheet(QString::fromUtf8(
        "color: #0b57d0;"
        "background-color: #FFFFFF;"
        "border: none;"
        "border-bottom: 3px solid #0b57d0;"
        "border-radius: 1px;"
        "font-weight: bold;"
        "font-family: Roboto;"
        "font-size: 14px;"
        "margin-left: 5px;"
    ));
}

void Tab::Deactivate()
{
    setStyleSheet(QString::fromUtf8(
        "background-color: #FFFFFF;"
        "border: none;"
        "font-family: Roboto;"
        "font-size: 14px;"
        "margin-left: 5px;"
    ));
}

} //namespace settings
} //namespace pages
} //namespace skvm_widgets

