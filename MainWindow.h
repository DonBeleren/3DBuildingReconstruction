#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <ui_MainWindow.h>
#include <QKeyEvent>
#include "GLWidget3D.h"


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	QStringList values;

public slots:
	void onFileOpen();
	void onReadTxt();

protected:
	void keyReleaseEvent(QKeyEvent* e);

private:
	Ui::MainWindowClass ui;
	//Ui::TextFinder *ui;
	GLWidget3D* glWidget;
};

#endif // MAINWINDOW_H
