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
#include "NewVersionNotification.h"
#include <QUrl>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <QDesktopServices>

namespace skvm_widgets
{

namespace notifications
{

NewVersionNotification::NewVersionNotification(const skvm::updater::Version& version):
    QWidget{nullptr},
    m_version(version)
{
    initLayout();
    addTitle();
    addDescription();
    addButtons();
}

void NewVersionNotification::initLayout()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setMargin(0);
}

void NewVersionNotification::addTitle()
{
    QFont font("Roboto", 10, QFont::Bold);
    auto label = new QLabel(this);
    label->setText("New version is available!");
    label->setFont(font);
    m_layout->addWidget(label);
}

void NewVersionNotification::addDescription()
{
    QFont font("Roboto", 10);
    auto description = QString("New version SKVM %1 is available!")
                           .arg(m_version.GetVersion().c_str());

    auto label = new QLabel(this);
    label->setText(description);
    label->setFont(font);
    label->setWordWrap(true);
    label->setTextFormat(Qt::RichText);
    label->setTextInteractionFlags(Qt::TextBrowserInteraction);
    label->setOpenExternalLinks(true);
    m_layout->addWidget(label);
}

void NewVersionNotification::addButtons()
{
    QFont font("Roboto", 9);
    auto layout = new QHBoxLayout();
    layout->setSpacing(15);
    layout->setMargin(0);

    auto download = new QPushButton(this);
    download->setText("DOWNLOAD");
    download->setFont(font);
    download->setFlat(true);
    download->setStyleSheet(QString::fromUtf8(
        "border: 1px solid #7C4DFF;"
        "border-radius: 5px;"
        "padding: 10px;"
        "background-color: #7C4DFF;"
        "color: #FFFFFF"
    ));
    download->setCursor(Qt::PointingHandCursor);
    connect(download, &QPushButton::clicked, this, [this](){
        const QUrl documentation(m_version.GetLink().c_str());
        QDesktopServices::openUrl(documentation);
        hide();
    });
    layout->addWidget(download);

    auto dismiss = new QPushButton(this);
    dismiss->setText("DISMISS");
    dismiss->setFlat(true);
    dismiss->setFont(font);
    dismiss->setStyleSheet(QString::fromUtf8(
        "border: 1px solid #5C1349;"
        "border-radius: 5px;"
        "padding: 10px;"
        "background-color: transparent;"
    ));
    dismiss->setCursor(Qt::PointingHandCursor);
    connect(dismiss, &QPushButton::clicked, this, [this](){
        hide();
    });
    layout->addWidget(dismiss);

    m_layout->addLayout(layout);
}

} //namespace notifications

} //namespace skvm_widgets


