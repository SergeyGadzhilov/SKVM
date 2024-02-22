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
#include "GeneralTabContent.h"
#include "widgets/TextEdit.h"

namespace skvm_widgets
{

namespace pages
{

namespace settings
{

GeneralTabContent::GeneralTabContent(QWidget *parent)
    : QWidget{parent}
{
    initLayout();
}

void GeneralTabContent::initLayout()
{
    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(new TextEdit(this, "Test", "TestValue"));
    m_layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Maximum));
}

} //namespace settings
} //namespace pages
} //namespace skvm_widgets
