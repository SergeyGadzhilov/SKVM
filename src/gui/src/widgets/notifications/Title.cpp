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
#include "Title.h"
#include <QLabel>
#include <QPushButton>

namespace skvm_widgets
{

namespace notifications
{

Title::Title(QWidget *parent)
    : QWidget{parent}
{
    m_layout = new QHBoxLayout(this);
    m_layout->setMargin(0);
    addText();
    addCloseButton();
}

void Title::addText()
{
    QFont font("Roboto", 11);
    auto label = new QLabel(this);
    label->setText("Notifications");
    label->setFont(font);

    m_layout->addWidget(label);
    m_layout->addItem(new QSpacerItem(200, 0, QSizePolicy::Expanding, QSizePolicy::Fixed));
}

void Title::addCloseButton()
{
    QIcon icon(QString::fromUtf8(":/res/icons/notifications/close.svg"));
    auto button = new QPushButton(this);
    button->setFlat(true);
    button->setIcon(icon);
    button->setCursor(Qt::PointingHandCursor);
    connect(button, &QPushButton::clicked, this, [this](){
        auto parent = parentWidget();
        if (parent)
        {
            parent->hide();
        }
    });

    m_layout->addWidget(button);
}

} //namespace notifications

} //namespace skvm_widgets
