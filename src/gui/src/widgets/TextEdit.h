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
#ifndef SKVM_WIDGETS_TEXTEDIT_H
#define SKVM_WIDGETS_TEXTEDIT_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QHBoxLayout>

namespace skvm_widgets
{

class TextEdit : public QWidget
{
    Q_OBJECT
public:
    TextEdit(QWidget *parent, const QString& label, const QString& value);

private:
    void initLayout();

    QLabel* m_label = nullptr;
    QTextEdit* m_value = nullptr;
    QHBoxLayout* m_layout = nullptr;

};

} //namespace skvm_widgets


#endif // SKVM_WIDGETS_TEXTEDIT_H
