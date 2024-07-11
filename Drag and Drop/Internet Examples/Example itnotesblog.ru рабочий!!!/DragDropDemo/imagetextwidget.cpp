#include "imagetextwidget.h"

#include <QLabel>
#include <QVBoxLayout>

ImageTextWidget::ImageTextWidget( QWidget *parent ) : QWidget( parent ) {
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget( m_imageLabel = new QLabel( trUtf8( "<Место для изображения>" ) ), 1 );
    layout->addWidget( m_textLabel = new QLabel( trUtf8( "<Место для подписи>" ) ) );
    setLayout( layout );

    m_imageLabel->setAlignment( Qt::AlignVCenter | Qt::AlignHCenter );
    m_textLabel->setAlignment( Qt::AlignHCenter );

    resize( 300, 300 );
}

ImageTextWidget::~ImageTextWidget() {
}

void ImageTextWidget::setPixmap( const QPixmap& pix ) {
    m_imageLabel->setPixmap( pix );
}

QPixmap ImageTextWidget::getPixmap() const {
    return m_imageLabel->pixmap() ? *m_imageLabel->pixmap() : QPixmap();
}

void ImageTextWidget::setText( const QString& text ) {
    m_textLabel->setText( text );
}

QString ImageTextWidget::getText() const {
    return m_textLabel->text();
}
