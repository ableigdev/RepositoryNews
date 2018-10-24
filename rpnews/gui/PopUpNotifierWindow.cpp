#include "PopUpNotifierWindow.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>

PopUpNotifierWindow::PopUpNotifierWindow(QWidget* parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint |
                  Qt::Tool |
                  Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    m_Animation.setTargetObject(this);
    m_Animation.setPropertyName("popupOpacity");
    connect(&m_Animation, &QAbstractAnimation::finished, this, &PopUpNotifierWindow::hideSlot);

    m_Label.setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
    m_Label.setStyleSheet("QLabel { color : white; "
                          "margin-top: 6px;"
                          "margin-bottom: 6px;"
                          "margin-left: 10px;"
                          "margin-right: 10px; }");

    m_Button.setMaximumWidth(15);
    m_Button.setText("X");
    m_Button.setFlat(true);
    connect(&m_Button, &QPushButton::clicked, this, &PopUpNotifierWindow::pushButtonClickedSlot);

    m_Layout.addWidget(&m_Button, 0, 1, Qt::AlignRight);
    m_Layout.addWidget(&m_Label, 0, 0);
    setLayout(&m_Layout);

    m_Timer = new QTimer();
    connect(m_Timer, &QTimer::timeout, this, &PopUpNotifierWindow::stopTimerSlot);
}

void PopUpNotifierWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    QRect roundedRect;

    painter.setRenderHint(QPainter::Antialiasing);
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    painter.setBrush(QBrush(QColor(0, 0, 0, 180)));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(roundedRect, 10, 10);
}

void PopUpNotifierWindow::setPopUpText(const QString& text)
{
    m_Label.setText(text);
    adjustSize();
}

void PopUpNotifierWindow::show()
{
    setWindowOpacity(0.0);
    m_Animation.setDuration(150);
    m_Animation.setStartValue(0.0);
    m_Animation.setEndValue(1.0);

    setGeometry(QApplication::desktop()->availableGeometry().width() - 36 - width() + QApplication::desktop()->availableGeometry().x(),
                QApplication::desktop()->availableGeometry().height() - 36 - height() + QApplication::desktop()->availableGeometry().y(),
                width(),
                height());
    QWidget::show();
    m_Animation.start();
    m_Timer->start(3000);
}

void PopUpNotifierWindow::stopTimerSlot()
{
    m_Timer->stop();
}

void PopUpNotifierWindow::hideSlot()
{
    if (getPopupOpacity() == 0.0)
    {
        QWidget::hide();
    }
}

void PopUpNotifierWindow::setPopupOpacity(double opacity)
{
    m_PopUpOpacity = opacity;
    setWindowOpacity(opacity);
}

double PopUpNotifierWindow::getPopupOpacity() const
{
    return m_PopUpOpacity;
}

void PopUpNotifierWindow::pushButtonClickedSlot()
{
    m_Animation.setDuration(1000);
    m_Animation.setStartValue(1.0);
    m_Animation.setEndValue(0.0);
    m_Animation.start();
}
