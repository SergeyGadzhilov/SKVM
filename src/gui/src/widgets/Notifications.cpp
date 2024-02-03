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

namespace skvm_widgets
{

Notifications::Notifications(QWidget *parent)
    : QWidget{parent}
{
    initLayout();
    addTitle();
    m_layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding));
    hide();
}

void Notifications::initLayout()
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(QString::fromUtf8(
        "background-color: rgba(255, 255, 255, 1);"
    ));
    setFixedWidth(300);
    m_layout = new QVBoxLayout(this);
}

void Notifications::addTitle()
{
    auto titleLayout = new QHBoxLayout();
    QFont font("Roboto", 11);
    auto title = new QLabel(this);
    title->setText("Notifications");
    title->setFont(font);
    titleLayout->addWidget(title);

    titleLayout->addItem(new QSpacerItem(150, 0, QSizePolicy::Fixed, QSizePolicy::Fixed));

    QIcon icon(QString::fromUtf8(":/res/icons/notifications/close.svg"));
    auto close = new QPushButton(this);
    close->setFlat(true);
    close->setIcon(icon);
    close->setCursor(Qt::PointingHandCursor);
    connect(close, &QPushButton::clicked, this, [this](){
        hide();
    });
    titleLayout->addWidget(close);

    m_layout->addLayout(titleLayout);
}

}//namespace skvm_widgets
