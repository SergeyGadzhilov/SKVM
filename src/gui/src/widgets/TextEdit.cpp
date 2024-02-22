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
#include "TextEdit.h"

namespace skvm_widgets
{

TextEdit::TextEdit(QWidget *parent, const QString& label, const QString& value)
    : QWidget{parent}
{
    m_label = new QLabel(label, this);
    m_label->setStyleSheet(QString::fromUtf8(
        "font-family: Roboto;"
        "font-size: 18px;"
    ));
    m_label->setFixedWidth(200);

    m_value = new QTextEdit(value, this);
    m_value->setStyleSheet(QString::fromUtf8(
        "font-family: Roboto;"
        "font-size: 18px;"
    ));

    initLayout();
}

void TextEdit::initLayout()
{
    m_layout = new QHBoxLayout(this);
    m_layout->addWidget(m_label);
    m_layout->addItem(new QSpacerItem(50, 40, QSizePolicy::Fixed, QSizePolicy::Fixed));
    m_layout->addWidget(m_value);
}

} //namespace skvm_widgets
