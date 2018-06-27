#ifndef DIALOG_DATALOGSETTINGS_H
#define DIALOG_DATALOGSETTINGS_H

#include <QSettings>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QCheckBox>
#include <QString>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
class Dialog_DataLogSettings : public QDialog
{
    Q_OBJECT
public:
    Dialog_DataLogSettings( QSettings* settings );
    ~Dialog_DataLogSettings();
private slots:
    void onPushButtonPressedBrowse();
    void onCheckBoxSelected();
private:
    QSettings* _settings;
    QCheckBox* m_checkBoxList[16];
    QString m_settingsFilename;
    QGridLayout* m_layout;
    void loadSettings();
    void initializeWidgets();
    QPushButton* m_button_browse;
    QLineEdit* m_lineEdit_logDirectory;
};

#endif // DIALOG_DATALOGSETTINGS_H
