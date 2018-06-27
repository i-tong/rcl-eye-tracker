#ifndef GAZEPARAMTOOLBAR_H
#define GAZEPARAMTOOLBAR_H

#include "qwidget.h"
#include <qtoolbar.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcombobox.h>
#include "Util.h"
#include "qapplication.h"
#include <QDesktopWidget>
#include <qgridlayout.h>
#include <qlabel.h>
#include <qhash.h>

class GazeParamToolbar : public QToolBar
{
	Q_OBJECT
public:
	GazeParamToolbar(void);
	~GazeParamToolbar(void);

public slots:
	void onSetButtonClicked();
signals:
	void paramChanged(QHash<QString, float> outHash);
private:
	void initLayout();
    QHash<QString, float> paramHash;
    // Widgets
    QPushButton* pushButton_set;
    QLineEdit* textBox_numPixKeep;
    QLineEdit* textBox_numPixKeepROI;
    QLineEdit* textBox_roughPupilMinIQ;
    QLineEdit* textBox_roughPupilMinArea;
    QLineEdit* textBox_roughPupilMaxArea;
    QLineEdit* textBox_finePupilThresMultiplier;
    QLineEdit* textBox_finePupilMinIQ;
    QLineEdit* textBox_finePupilMinArea;
    QLineEdit* textBox_finePupilMaxArea;
};

#endif

