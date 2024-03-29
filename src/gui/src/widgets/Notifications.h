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
#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QWidget>
#include <QVBoxLayout>

namespace skvm_widgets
{

class Notifications : public QWidget
{
    Q_OBJECT
public:
    explicit Notifications(QWidget *parent = nullptr);
    void Add(QWidget* notification = nullptr);

signals:
    void NewNotification();

private:
    void initLayout();
    void addContainer();

    QVBoxLayout* m_layout = nullptr;
    QVBoxLayout* m_container = nullptr;
};

} //namespace skvm_widgets

#endif // NOTIFICATIONS_H
