#ifndef MAIN_WINDOW
#define MAIN_WINDOW

#include <QtGui/QMainWindow>
#include <QtGui>

#include "TileView.h"
#include "TileManager.h"
#include "MapMarker.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
	public:
		MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
		~MainWindow();

	private slots:
		void standardButtonPressed();
		void cycleButtonPressed();
		void cycleTransportButtonPressed();

		void zoomUpButtonPressed();
		void zoomDownButtonPressed();

	private:
		MapMarker planeMarker;

		TileManager* tileManager;
		TileView* imageView;

		QPushButton* standardButton;
		QPushButton* cycleButton;
		QPushButton* cycleTransportButton;

		QPushButton* zoomUpButton;
		QPushButton* zoomDownButton;

    private:
		virtual void wheelEvent(QWheelEvent* event);

};

#endif
