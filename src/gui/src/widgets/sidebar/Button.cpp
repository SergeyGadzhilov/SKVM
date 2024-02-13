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
#include "Button.h"
#include <QIcon>

namespace skvm_widgets
{

namespace sidebar
{

Button::Button(QWidget *parent, const QString& iconName)
    : QPushButton{parent}
{
    setFlat(true);
    setCursor(Qt::PointingHandCursor);
    setIcon(iconName);
}

void Button::SetActive(bool isActive)
{
    if (isActive)
    {
        setStyleSheet(QString::fromUtf8(
            "border-radius: 15;"
            "background-color: #E0F7FA;"
        ));
    }
    else
    {
        setStyleSheet(QString::fromUtf8(
            "border: none;"
        ));
    }
}

void Button::setIcon(const QString& name)
{
    QIcon icon(QString(":/res/icons/sidebar/%1.svg").arg(name));
    QPushButton::setIcon(icon);
    setIconSize(QSize(30,30));
}

} //naspace sidebar

} //namespace skvm_widgets

