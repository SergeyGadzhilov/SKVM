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
#ifndef SKVM_WIDGETS_NOTIFICATIONS_NEWVERSIONNOTIFICATION_H
#define SKVM_WIDGETS_NOTIFICATIONS_NEWVERSIONNOTIFICATION_H

#include <QWidget>
#include <QVBoxLayout>
#include "updater/Version.h"

namespace skvm_widgets
{

namespace notifications
{

class NewVersionNotification : public QWidget
{
    Q_OBJECT
public:
    explicit NewVersionNotification(const skvm::updater::Version& version);

private:
    void initLayout();
    void addTitle();
    void addDescription();
    void addButtons();

    skvm::updater::Version m_version;
    QVBoxLayout* m_layout = nullptr;
};

} //namespace notifications

} //namespace skvm_widgets

#endif // SKVM_WIDGETS_NOTIFICATIONS_NEWVERSIONNOTIFICATION_H
