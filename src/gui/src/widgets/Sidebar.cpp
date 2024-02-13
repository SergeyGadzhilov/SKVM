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
#include <QDesktopServices>
#include "sidebar/Button.h"

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
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet(QString::fromUtf8(
        "background-color: rgba(105, 145, 214, 0.2);"
    ));

    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(12);
    m_layout->setContentsMargins(-1, 15, -1, 30);
}

void Sidebar::addBottomControls()
{
    m_layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
    addButtonHome();
    addButtonSettings();
    addButtonLogs();
    addButtonHelp();
}

void Sidebar::addButtonHome()
{
    auto button = new sidebar::Button(this, "home");
    connect(button, &QPushButton::clicked, this, [this]() {
        emit OpenHome();
    });
    button->SetActive(true);
    m_layout->addWidget(button);
}

void Sidebar::addButtonSettings()
{
    auto button = new sidebar::Button(this, "settings");
    connect(button, &QPushButton::clicked, this, [this]() {
        emit OpenSettings();
    });
    m_layout->addWidget(button);
}

void Sidebar::addButtonLogs()
{
    auto button = new sidebar::Button(this, "logs");
    connect(button, &QPushButton::clicked, this, [this]() {
        emit OpenLogs();
    });
    m_layout->addWidget(button);
}

void Sidebar::addButtonHelp()
{
    auto button = new sidebar::Button(this, "help");
    connect(button, &QPushButton::clicked, []() {
        const QUrl documentation("https://github.com/SergeyGadzhilov/SKVM/wiki");
        QDesktopServices::openUrl(documentation);
    });
    m_layout->addWidget(button);
}

} //namespace skvm_widgets

