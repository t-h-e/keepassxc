#include "RemoteTrustDialog.h"
#include "ui_RemoteTrustDialog.h"

#include <QPushButton>

RemoteTrustDialog::RemoteTrustDialog(QWidget* parent)
    : QDialog(parent)
    , m_ui(new Ui::RemoteTrustDialog())
{
    m_ui->setupUi(this);
    m_ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Trust and Execute"));
}

RemoteTrustDialog::~RemoteTrustDialog() = default;

void RemoteTrustDialog::setRemoteName(const QString& name)
{
    m_ui->remoteNameValue->setText(name);
}

void RemoteTrustDialog::setCommand(const QString& command)
{
    m_ui->commandValue->setText(command);
}

void RemoteTrustDialog::setInput(const QString& input)
{
    m_ui->inputValue->setPlainText(input);
    m_ui->inputLabel->setVisible(!input.isEmpty());
    m_ui->inputValue->setVisible(!input.isEmpty());
}
