#ifndef GAZETOOLBAR_H
#define GAZETOOLBAR_H

#include <qtoolbar.h>
#include <qpushbutton.h>
#include <qcombobox.h>
#include "EyeGazeCommon.h"
//#include "UtilCamera.h"
#include "qapplication.h"
#include <QDesktopWidget>
#include <QGridLayout>
#include <QLabel>
#include <QDebug>
#include <QProcess>

class GazeToolbar : public QToolBar
{
	Q_OBJECT
public:
	GazeToolbar(void);
	~GazeToolbar(void);

	// Widgets
	QPushButton* pushButton_Start;
	QPushButton* pushButton_Calibrate;
    //QComboBox* comboBox_trackerInputRight;
    //QComboBox* comboBox_trackerInputLeft;
    QComboBox* comboBox_trackerInputBoth;
	QComboBox* comboBox_calibNumber;
//	QComboBox* comboBox_trackerType;
	QComboBox* comboBox_calibMonitor;
    QComboBox* comboBox_calibEye;
    QPushButton* pushButton_Log;
    //QPushButton* pushButton_Calibrate3D;
    QPushButton* pushButton_streamGazePosition;
    QPushButton* pushButton_ManualGlints;
    QPushButton* pushButton_Head;
    //QPushButton* pushButton_HeadRepeat;

    bool isLooking();
    
    // Set/Get
    void setStatus_pushButton_streamGazePosition(bool status);
    bool getStatus_pushButton_streamGazePosition();
    void setStatus_pushButton_manualGlint(bool status);
    bool getStatus_pushButton_manualGlint();
public slots:
    void onButtonClickLog();
	void onButtonClickStart();
	void onButtonClickCalibNumber();
	void onComboBoxSelect_trackerType();
   // void onButtonClick_Calibrate3D();
    void onButtonClick_StreamGaze();

private:
	void initLayout();
	bool startButtonOn;
	bool calibrateButtonOn;
    bool logButtonOn;
    bool streamGazeButtonOn;
    bool manualGlints;
};

#endif

