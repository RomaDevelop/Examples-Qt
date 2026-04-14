//==========================================================================================================================================
/*
 * Добавление в проект:
 * INCLUDEPATH += ../include
 * DEPENDPATH += ../include
 * win32:CONFIG(release, debug|release): LIBS += -L../bin/ -lCANSettingDialog
 * else:win32:CONFIG(debug, debug|release): LIBS += -L../bin/ -lCANSettingDialog
 *
 * Примение в проекте:
 * #include "CANSettingDialog.h"
 * if(CANSettingDialog::Execute(&allChannels,ICANChannel::BR_1M)) { } // пользователь нажал Ok
 * else { } // пользователь нажал Cancel или закрыл диалог
 *
 * при вызове диалога в Execute передается список каналов с которыми он будет работать,
 * скорость по умолчанию и флаг startSingleChannel, если нужно запустить только один канал
 * при нажатии Ok диалог запустит/перезапустит с заданным режимом и скоростью выбранные каналы, не выбранные - остановит, возвратит true
 * при нажатии Cancel или закрытии диалог ничего не делает, возвращает false
*/
//==========================================================================================================================================
#ifndef CANSettingDialog_h
#define CANSettingDialog_h
//------------------------------------------------------------------------------------------------------------------------------------------
#include <QDialog>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QRadioButton>
#include <QComboBox>
#include <QLabel>
#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

#include <vector>
#include <memory>

#include "CommonChannelSettingsDialog.h"

#include "icanchannel.h"

#include "CANSettingDialog_global.h"

//------------------------------------------------------------------------------------------------------------------------------------------
class CANSETTINGDIALOG_EXPORT CANSettingDialog : public QDialog, public CommonChannelSettingsDialog
{
	Q_OBJECT

public:
	///\brief Вызов диалога настройки CAN
	///\return true если было нажато Ok, в остальных случаях - false
	///\param[in,out] *channels_ - коллекция каналов с которыми будет работать диалог
	///\param[in] defaultBaud - скорость по умолчанию
	///\param[in] Start1Channel - флаг возможности пуска только одного канала
	static bool Execute(std::vector<ICANChannel*> *aChannels,
						unsigned int defaultBaud = ICANChannel::BR_500K,
						bool aStartSingleChannel = false);

private:
	///\brief создается диалог
	explicit CANSettingDialog(QWidget *parent = nullptr);
	///\brief заполняет ListChannels имеющимися каналами CAN
	void FillListChannels();

	///\brief запуск выбранного канала
	void StartChannel(ICANChannel *CANChannel);

	unsigned int GetSelectedRegime();
	unsigned int GetSelectedBaud();

private slots:
	///\brief Всем каналам, на которых установлена галочка, будут запущены с заданныи режимом и скоростью.
	/// Каналы без галочки будут остановлены и освобождены.
	/// После чего диалог будет скрыт.
	void Ok_click();

	///\brief Скрывает диалог.
	void Cancel_click();
	
private:
	QDialogButtonBox	*buttonBox;
	QPushButton			*btnOk;
	QPushButton			*btnCancel;

	QLabel				*labelBaud;
	QComboBox			*comboBoxBaud;

	QGroupBox			*groupBoxFrame;
	QRadioButton		*radioFrame11;
	QRadioButton		*radioFrame29;
	QRadioButton		*radioFrame11_29;

	QListWidget			*listWidgetChannels;

	///\brief хранение значения последнего выбранного действия (Ok | Cancel | Close)
	QString	action;
	///\brief флаг работы только с одникм каналом. Если выбрано несколько - при нажатии Ok выдаёт предупреждение.
	bool startSingleChannel;

	std::vector<ICANChannel*> channels;
};
//------------------------------------------------------------------------------------------------------------------------------------------
#endif // CANSettingDialog_h
