btn->setIcon(QApplication::style()->standardIcon(QStyle::StandardPixmap::SP_FileDialogDetailedView));

MyQDialogs::ShowAllStandartIcons();

// Стандартные иконки Qt лежат в C:\Qt\Qt5.12.10\5.12.10\Src\qtbase\src\widgets\styles\images
// но они в png, чтобы присвоить проекту конвертировал через IcoFX

Установить иконку .exe файлу: в .pro указать:

RC_ICONS = resources/arrow_right.ico
// указывал путь относительно .pro файла 