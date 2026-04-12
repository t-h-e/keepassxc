#ifndef KEEPASSXC_REMOTETRUSTDIALOG_H
#define KEEPASSXC_REMOTETRUSTDIALOG_H

#include <QDialog>
#include <QScopedPointer>

namespace Ui
{
    class RemoteTrustDialog;
}

class RemoteTrustDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RemoteTrustDialog(QWidget* parent = nullptr);
    ~RemoteTrustDialog() override;

    void setRemoteName(const QString& name);
    void setCommand(const QString& command);
    void setInput(const QString& input);

private:
    QScopedPointer<Ui::RemoteTrustDialog> m_ui;
};

#endif // KEEPASSXC_REMOTETRUSTDIALOG_H
