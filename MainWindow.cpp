#include "MainWindow.h"
#include <QFileDialog>
#include <QFile>
#include <QLabel>
#include <QRegularExpression>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(onFileOpen()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));
	connect(ui.actionRead_Txt, SIGNAL(triggered()), this, SLOT(onReadTxt()));

	//connect(ui.plainTextEdit, SIGNAL(triggered()), this, SLOT(onReadTxt()));


	// Specify OpenGL context settings. Note this class is depricated.
	QGLFormat fmt;
	fmt.setVersion(3, 3);
	fmt.setProfile(QGLFormat::CoreProfile);

	// setup the OpenGL widget
	glWidget = new GLWidget3D(fmt);
	setCentralWidget(glWidget);
}

void MainWindow::onFileOpen()//for cow
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open OBJ file..."), "", tr("OBJ Files (*.obj)"));
	if (filename.isEmpty()) return;

	glWidget->loadOBJ(filename.toUtf8().data());
	glWidget->updateGL();
}

void MainWindow::onReadTxt()
{
	glWidget->connectParser();//readTxt("Facade.txt");
	bldg->makeVertexArrayObj();
	glWidget->updateGL();
}

void MainWindow::keyReleaseEvent(QKeyEvent* e) {
	//cout << "the main window's keyReleaseEvent has been initialized" << endl;
	switch (e->key()) {
	case Qt::Key_Escape:
		QApplication::quit();
		break;
	default:
		//QMainWindow::keyReleaseEvent(e);
		glWidget->keyReleaseEvent(e);
		break;
	}
}



