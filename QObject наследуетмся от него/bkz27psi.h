#ifndef BKZ27PSI_H
#define BKZ27PSI_H

#include <QTextBrowser>

#include "iwindow.h"

// public QObject должен быть первым в иерархии наследования
// макрос Q_OBJECT
// сигналы private: signals:
// слоты private slots:
// connect: connect(this,&BKZ27_psi::SignalVklChan,this,&BKZ27_psi::SlotVklChan);
class BKZ27_psi: public QObject, public LogedClass, public IWindow
{
	Q_OBJECT

	QString name;
	QString connectString;
	std::vector<Object*> objects;
	std::vector<Protocol*> protocols;
	IConnectExternalWidgets *programm = nullptr;

	std::unique_ptr<QWidget> window;
	QTextBrowser *textBrowser = nullptr;
	std::vector<std::pair<QWidget*,ConnectData>> ctrlElements;
	std::vector<std::pair<QWidget*,ConnectData>> viewElements;

public:
	explicit BKZ27_psi(QString connectString_, QString name_, QObject *parent = nullptr);
	~BKZ27_psi() = default;

	virtual QString GetClassName() const override { return classBKZ27_psi; }
	virtual QString ToStrForLog() const override { return GetClassName() + " ToStrForLog " + CodeMarkers::mock; }

	virtual QString Name() const override { return name; }
	virtual QWidget* Window() override { return window.get(); }

	virtual void ConnectToObjects(IConnectExternalWidgets *programm_, std::vector<Object*> allObjects, std::vector<Protocol*> allProtocols) override;

	virtual QString GetSettings() const override { return { "no settings" };}
	virtual void SetSettings(const QString &str) override { if(str!="no settings") Error(GetClassName()+"::SetSettings has no settings"); }

	inline static const QString classBKZ27_psi { "BKZ27_psi" };

private: signals:
	void SignalVklChan(int i, FrameWorker *vklYprAper1);

private slots:
	void SlotVklChan(int i, FrameWorker *vklYprAper1)
	{
		qdbg << "SlotVklChan";
		CANMsg_t frame;
		EasyData ed(frame);
		ed.SetBitBi(i,1);
		ed.ToMsg(frame);
		auto commands = Code::TextToCommands((QString)
											 "thisFrameWorker.новыеСостояния = Data[][0-47];"+
											 "SendFrame(thisFrameWorker)");
		for(auto &command:commands)
			protocols[0]->DoEverything(command, nullptr, vklYprAper1, frame, Protocol::DEretNullptr());
	}

};

#endif // BKZ27PSI_H
