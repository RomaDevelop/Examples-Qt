#ifndef IMAGETEXTWIDGET_H
#define IMAGETEXTWIDGET_H

#include <QWidget>

class QLabel;

class ImageTextWidget : public QWidget {
    Q_OBJECT

public:
    ImageTextWidget( QWidget *parent = 0 );
    ~ImageTextWidget();

    void setPixmap( const QPixmap& pix );
    QPixmap getPixmap() const;

    void setText( const QString& text );
    QString getText() const;

private:
    QLabel* m_imageLabel;
    QLabel* m_textLabel;
};

#endif // IMAGETEXTWIDGET_H
