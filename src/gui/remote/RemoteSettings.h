//
// Created by Stefan on 26/03/2023.
//

#ifndef KEEPASSXC_REMOTESETTINGS_H
#define KEEPASSXC_REMOTESETTINGS_H

#include <QObject>
#include <QMap>
#include <QVariant>

class RemoteSettings : QObject
{
    Q_OBJECT

public:
    explicit RemoteSettings(QObject* parent = nullptr);
    ~RemoteSettings() override = default;

    QString getName();
    bool getAddToMenu();
    QString getDownloadCommand();
    QString getDownloadCommandInput();
    QString getUploadCommand();
    QString getUploadCommandInput();

    void setName(QString name);
    void setAddToMenu(bool addToMenu);
    void setDownloadCommand(QString downloadCommand);
    void setDownloadCommandInput(QString downloadCommandInput);
    void setUploadCommand(QString uploadCommand);
    void setUploadCommandInput(QString uploadCommandInput);

    QMap<QString, QVariant> toConfig();
    void fromConfig(const QMap<QString, QVariant>&);

private:
    QString m_name;
    bool m_addToMenu;
    QString m_downloadCommand;
    QString m_downloadCommandInput;
    QString m_uploadCommand;
    QString m_uploadCommandInput;
};

#endif // KEEPASSXC_REMOTESETTINGS_H
