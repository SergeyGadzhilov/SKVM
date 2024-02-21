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

#include "pages/settings/GeneralTabContent.h"
#include "pages/settings/NetworkTabContent.h"

namespace skvm_widgets
{

using namespace pages::settings;

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
    auto tabs = new Tabs(this);
    connect(tabs, &Tabs::SwitchTab, this, [this](QWidget* content) {
        if (m_content)
        {
            m_content->setCurrentWidget(content);
        }
    });
    m_layout->addWidget(tabs);

    initTabsContent(tabs);

    m_layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void SettingsPage::initTabsContent(Tabs* tabs)
{
    if (!tabs)
    {
        return;
    }

    m_content = new QStackedWidget(this);

    auto general = new GeneralTabContent();
    m_content->addWidget(general);
    tabs->AddTab(general, "General");

    auto network = new NetworkTabContent();
    m_content->addWidget(network);
    tabs->AddTab(network, "Network");

    m_layout->addWidget(m_content);
}

}
