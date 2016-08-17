/*
 * Traceshark - a visualizer for visualizing ftrace and perf traces
 * Copyright (C) 2014, 2015, 2016  Viktor Rosendahl <viktor.rosendahl@gmail.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QApplication>
#include <QtCore>
#include "ui/mainwindow.h"
#include "ui/tracesharkstyle.h"

#define QT5_WARNING \
"WARNING!!! WARNING!!! WARNING!!!\n" \
"WARNING!!! WARNING!!! WARNING!!! WARNING!!! WARNING!!! WARNING!!!\n" \
"\n" \
"You are using a Qt version that is >= 5.0.0. This is not recommended\n"  \
"unless you are a developer who wants to try to fix the problems with\n" \
"using Qt5\n" \
"\n" \
"WARNING!!! WARNING!!! WARNING!!! WARNING!!! WARNING!!! WARNING!!!\n" \
"WARNING!!! WARNING!!! WARNING!!! WARNING!!! WARNING!!! WARNING!!!"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	MainWindow mainWindow;
	QPixmap pm(QLatin1String(":/traceshark/images/shark.png"));
	QIcon icon;
	QString appname = QLatin1String("Traceshark");
	QRect geometry;
	int width, height;

/* Set graphicssystem to opengl if we have old enough Qt */
#if QT_VERSION < QT_VERSION_CHECK(5, 0, 0)
	QApplication::setGraphicsSystem("opengl");
#else
#pragma message(QT5_WARNING)
#endif

	app.setStyle(new TraceSharkStyle);
	app.setApplicationName(appname);
	icon.addPixmap(pm);
	app.setWindowIcon(icon);
	
	mainWindow.setWindowIconText(appname);
	mainWindow.setWindowTitle(appname);

	mainWindow.show();

	geometry = QApplication::desktop()->availableGeometry();

	if (geometry.width() < 1600)
		width = geometry.width();
	else
		width = 1600 + (geometry.width() - 1600) / 2;

	if (geometry.height() < 1100)
		height = geometry.height();
	else
		height = geometry.height() - geometry.height() / 16;

	mainWindow.resize(width, height);

	return app.exec();
}
