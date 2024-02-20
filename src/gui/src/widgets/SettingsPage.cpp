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
#include "SettingsPage.h"
#include "pages/settings/SettingsTabs.h"

namespace skvm_widgets
{

SettingsPage::SettingsPage(QWidget *parent)
    : QWidget{parent}
{
    initLayout();
    initTabs();
}

void SettingsPage::initLayout()
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(QString::fromUtf8(
        "background-color: #ffffff;"
    ));

    m_layout = new QVBoxLayout(this);
    m_layout->setMargin(0);
}

void SettingsPage::initTabs()
{
    auto tabs = new pages::settings::Tabs(this);
    m_layout->addWidget(tabs);
    m_layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

}
