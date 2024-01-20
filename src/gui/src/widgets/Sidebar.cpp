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
#include "Sidebar.h"
#include <QUrl>
#include <QPushButton>
#include <QDesktopServices>

namespace skvm_widgets
{

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent)
{
    initLayout();
    addBottomControls();
}

void Sidebar::initLayout()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(5);
    m_layout->setContentsMargins(-1, 15, -1, 15);
}

void Sidebar::addBottomControls()
{
    m_layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    addButtonHelp();
}

void Sidebar::addButtonHelp()
{
    QIcon icon(QString::fromUtf8(":/res/icons/sidebar/help.svg"));

    auto button = new QPushButton(this);
    button->setFlat(true);
    button->setIcon(icon);
    button->setIconSize(QSize(30, 30));
    button->setCursor(Qt::PointingHandCursor);
    connect(button, &QPushButton::clicked, []() {
        const QUrl documentation("https://github.com/SergeyGadzhilov/SKVM/wiki");
        QDesktopServices::openUrl(documentation);
    });

    m_layout->addWidget(button);
}

} //namespace skvm_widgets

