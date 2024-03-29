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
#include "StatusBar.h"

namespace skvm_widgets {

StatusBar::StatusBar(QWidget *parent)
    : QWidget{parent}
{
    initLayout();
    addPadlockLabel();
    addStatusLabel();
    m_layout->addItem(new QSpacerItem(5, 5, QSizePolicy::Expanding, QSizePolicy::Maximum));
    addNotificationButton();
}

void StatusBar::SetStatus(const QString &status)
{
    m_status->setText(status);
}

void StatusBar::ShowPadlock()
{
    m_padlock->show();
}

void StatusBar::HidePadlock()
{
    if (m_padlock)
    {
        m_padlock->hide();
    }
}

void StatusBar::NewNotification()
{
    QIcon icon(QString::fromUtf8(":/res/icons/statusbar/notification_unread.svg"));
    m_notification->setIcon(icon);
}

void StatusBar::initLayout()
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(QString::fromUtf8(
        "background-color: rgba(105, 145, 214, 0.2);"
    ));

    m_layout = new QHBoxLayout(this);
    m_layout->setSpacing(12);
    m_layout->setContentsMargins(0, 5, 25, 5);
}

void StatusBar::addStatusLabel()
{
    m_status = new QLabel(this);
    m_status->setText("Ready");
    m_status->setStyleSheet(QString::fromUtf8(
        "background-color: transparent;"
    ));
    m_layout->addWidget(m_status);
}

void StatusBar::addPadlockLabel()
{
    m_padlock = new QLabel(this);
    m_padlock->setEnabled(true);
    m_padlock->setStyleSheet(QString::fromUtf8(
        "background-color: transparent;"
    ));
    m_padlock->setPixmap(QPixmap(QString::fromUtf8(":/res/icons/16x16/padlock.png")));
    m_layout->addWidget(m_padlock);
    m_padlock->hide();
}

void StatusBar::addNotificationButton()
{
    QIcon icon(QString::fromUtf8(":/res/icons/statusbar/notification.svg"));

    m_notification = new QPushButton(this);
    m_notification->setFlat(true);
    m_notification->setIcon(icon);
    m_notification->setCursor(Qt::PointingHandCursor);

    connect(m_notification, &QPushButton::clicked, this, [this, icon]() {
        m_notification->setIcon(icon);
        emit ShowNotifications();
    });

    m_layout->addWidget(m_notification);
}

} //namespace skvm_widgets
