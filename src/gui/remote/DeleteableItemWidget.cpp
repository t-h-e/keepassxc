/*
 *  Copyright (C) 2023 KeePassXC Team <team@keepassxc.org>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 or (at your option)
 *  version 3 of the License.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "DeleteableItemWidget.h"
#include <QStyleOptionButton>

DeleteableItemWidget::DeleteableItemWidget(const QString& text, QWidget* parent)
    : QWidget(parent)
    , m_layout(this)
    , m_label(text, this)
    , m_button("x", this)
{
    connect(&m_button, &QToolButton::clicked, this, &DeleteableItemWidget::onDelete);
    m_layout.addWidget(&m_label);
    m_layout.addStretch();
    //    m_button.setMinimumHeight(5);
    //    auto textSize = m_button.fontMetrics().size(Qt::TextShowMnemonic, m_button.text());
    //    QStyleOptionButton opt;
    //    opt.initFrom(&m_button);
    //    opt.rect.setSize(textSize);
    //    m_button.setMinimumSize(m_button.style()->sizeFromContents(QStyle::CT_PushButton, &opt, textSize, &m_button));
    m_button.setFixedHeight(5);
    m_button.setMinimumHeight(5);
    m_button.setMaximumHeight(5);
    m_layout.addWidget(&m_button);
}

DeleteableItemWidget::~DeleteableItemWidget() = default;

QString DeleteableItemWidget::getText()
{
    return m_label.text();
}
