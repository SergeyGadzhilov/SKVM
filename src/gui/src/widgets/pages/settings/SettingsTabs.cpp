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
#include "SettingsTabs.h"

#include <QPushButton>

namespace skvm_widgets
{

namespace pages
{

namespace settings
{

Tabs::Tabs(QWidget *parent)
    : QWidget{parent}
{
    initLayout();
    initTabs();
}

void Tabs::initLayout()
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(QString::fromUtf8(
        "border-bottom: 1px solid #c4c7c5;"
    ));
    setFixedHeight(50);
    m_layout = new QHBoxLayout(this);
    m_layout->setMargin(0);
}

void Tabs::initTabs()
{
    auto general = new Tab(this, "General");
    connect(general, &QPushButton::clicked, this, [this, general]() {
        activate(general);
    });
    m_layout->addWidget(general);
    activate(general);

    auto network = new Tab(this, "Network");
    connect(network, &QPushButton::clicked, this, [this, network]() {
        activate(network);
    });
    m_layout->addWidget(network);
    m_layout->addItem(new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Maximum));
}

void Tabs::activate(Tab* tab)
{
    if (tab)
    {
        if (m_activeTab)
        {
            m_activeTab->Deactivate();
        }
        m_activeTab = tab;
        m_activeTab->Activate();
    }
}

} //namespace settings
} //namespace pages
} //namespace skvm_widgets

