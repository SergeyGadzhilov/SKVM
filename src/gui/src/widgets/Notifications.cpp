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
#include "Notifications.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include "notifications/Title.h"

namespace skvm_widgets
{

Notifications::Notifications(QWidget *parent)
    : QWidget{parent}
{
    initLayout();
    m_layout->addWidget(new notifications::Title(this));
    addContainer();
    m_layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding));
    hide();
}

void Notifications::Add(QWidget *notification)
{
    if (!notification || !m_container)
    {
        return;
    }
    m_container->addWidget(notification);
    emit NewNotification();
}

void Notifications::initLayout()
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(QString::fromUtf8(
        "background-color: rgba(255, 255, 255, 1);"
    ));
    setFixedWidth(400);
    m_layout = new QVBoxLayout(this);
}

void Notifications::addContainer()
{
    m_container = new QVBoxLayout();
    m_container->setMargin(0);
    m_container->setSpacing(20);
    m_layout->addLayout(m_container);
}

}//namespace skvm_widgets
