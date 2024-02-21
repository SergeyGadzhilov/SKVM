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
#ifndef SKVM_WIDGETS_PAGES_SETTINGS_TABS_H
#define SKVM_WIDGETS_PAGES_SETTINGS_TABS_H

#include <QWidget>
#include <QHBoxLayout>
#include "Tab.h"

namespace skvm_widgets
{
namespace pages
{
namespace settings
{

class Tabs : public QWidget
{
    Q_OBJECT
public:
    explicit Tabs(QWidget *parent = nullptr);
    void AddTab(QWidget* content, QString name);

signals:
    void SwitchTab(QWidget* tab);

private:
    void initLayout();
    void activate(Tab* tab);

    QHBoxLayout* m_layout = nullptr;
    Tab* m_activeTab = nullptr;
};

}
}
}

#endif // SKVM_WIDGETS_PAGES_SETTINGS_TABS_H
