#include "Gui.h"
#include <QApplication>
#include <qfile.h>
#include <qdebug.h>

int main(int argc, char *argv[])
{
    qDebug() << "Starting Application";
    Q_INIT_RESOURCE(gazetrackguiresources);

    QApplication a(argc, argv);

    // Load style sheet
    QFile f(QString("..gazeTrackGUI/Resources/gazeStyle.qss"));//C:/Users/Sean/Documents/Gaze Track/Gaze SVN/branches/gazeTrackGUI/Resources/gazeStyle.qss
    if (f.open(QIODevice::ReadOnly)) {
        QString styleSheet = QLatin1String(f.readAll());
		qDebug() << styleSheet;
        a.setStyleSheet(styleSheet);
    }

    // Open window
    GazeTrackGUI w;
    w.show();

    return a.exec();
}
