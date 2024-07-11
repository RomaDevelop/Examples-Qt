#include <QCloseEvent>
	
	
	в методах окна:
	
	
	void closeEvent (QCloseEvent *event)
	{
		QMessageBox::StandardButton resBtn = QMessageBox::question(this, "Editor",
																	"Are you sure?\n",
																	QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
																	QMessageBox::Yes);
		if (resBtn != QMessageBox::Yes)
		{
			event->ignore();
		}
		else
		{
			event->accept();
		}
	}