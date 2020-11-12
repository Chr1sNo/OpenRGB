#ifndef OPENRGBDIALOG2_H
#define OPENRGBDIALOG2_H

#include "ui_OpenRGBDialog2.h"

#include "OpenRGBClientInfoPage.h"
#include "OpenRGBSoftwareInfoPage.h"
#include "OpenRGBSystemInfoPage.h"

#include <vector>
#include "i2c_smbus.h"
#include "RGBController.h"
#include "ProfileManager.h"
#include "NetworkClient.h"
#include "NetworkServer.h"
#include "ResourceManager.h"

#include <QMainWindow>
#include <QTimer>
#include <QSystemTrayIcon>
#include <QMenu>

namespace Ui
{
    class OpenRGBDialog2;
}

class Ui::OpenRGBDialog2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit OpenRGBDialog2(std::vector<i2c_smbus_interface *>& bus, QWidget *parent = 0);
    ~OpenRGBDialog2();

    void AddClient(NetworkClient* new_client); // Deprecated and possibly unused
    void AddClientTab();
    void AddI2CToolsPage();
    void AddServerTab();

    void setMode(unsigned char mode_val);

protected:
    std::vector<i2c_smbus_interface *>& busses;

private:
    /*-------------------------------------*\
    | Page pointers                         |
    \*-------------------------------------*/
    OpenRGBClientInfoPage *ClientInfoPage;
    OpenRGBSystemInfoPage *SMBusToolsPage;
    OpenRGBSoftwareInfoPage *SoftInfoPage;

    bool ShowI2CTools = false;

    /*-------------------------------------*\
    | System tray icon and menu             |
    \*-------------------------------------*/
    QSystemTrayIcon* trayIcon;
    QMenu* profileMenu;

    /*-------------------------------------*\
    | User interface                        |
    \*-------------------------------------*/
    Ui::OpenRGBDialog2Ui *ui;

    void AddSoftwareInfoPage();

    void ClearDevicesList();
    //void UpdateDevicesList(); // Deprecated
    void LoadDevicesList();
    void UpdateDevicesList(int index, bool remove);
    void UpdateProfileList();
    void closeEvent(QCloseEvent *event);

    void SetDetectionViewState(bool detection_showing);

    bool device_view_showing = false;
    bool darkTheme = false;

private slots:
    void on_Exit();
    void on_LightsOff();
    void on_QuickRed();
    void on_QuickYellow();
    void on_QuickGreen();
    void on_QuickCyan();
    void on_QuickBlue();
    void on_QuickMagenta();
    void on_QuickWhite();
    void on_ClientListUpdated();
    void onDeviceListUpdated(int index, int list, bool removed);
    void onDetectionProgressUpdated();
    void on_SetAllDevices(unsigned char red, unsigned char green, unsigned char blue);
    void on_SaveSizeProfile();
    void on_ShowHide();
    void on_ProfileSelected();
    void on_ButtonSaveProfile_clicked();
    void on_ButtonLoadProfile_clicked();
    void on_ButtonDeleteProfile_clicked();
    void on_ButtonToggleDeviceView_clicked();
    void on_ButtonStopDetection_clicked();
    void on_ButtonRescan_clicked();
};

#endif // OPENRGBDIALOG2_H
