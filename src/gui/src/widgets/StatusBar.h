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
#ifndef STATUSBAR_H
#define STATUSBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

namespace skvm_widgets
{

class StatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = nullptr);
    void SetStatus(const QString& status);
    void ShowPadlock();
    void HidePadlock();

private:
    void initLayout();
    void addStatusLabel();
    void addPadlockLabel();

    QLabel* m_padlock = nullptr;
    QLabel* m_status = nullptr;
    QHBoxLayout* m_layout = nullptr;
};

} //namespace skvm_widgets

#endif // STATUSBAR_H
