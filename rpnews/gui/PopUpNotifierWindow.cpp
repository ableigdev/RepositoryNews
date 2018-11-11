#include "PopUpNotifierWindow.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QtMultimedia/QSound>

PopUpNotifierWindow::PopUpNotifierWindow(QWidget* parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint |
                  Qt::Tool |
                  Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);
    setMaximumHeight(50);

    m_Animation.setTargetObject(this);
    m_Animation.setPropertyName("popupOpacity");
    connect(&m_Animation, &QAbstractAnimation::finished, this, &PopUpNotifierWindow::hideSlot);

    m_LabelAuthor.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_LabelAuthor.setStyleSheet("QLabel { color : black; "
                          "margin-top: 6px;"
                          "margin-left: 10px;"
                          "margin-right: 10px; "
                          "font-weight: bold; }");

    m_LabelMessage.setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    m_LabelMessage.setStyleSheet("QLabel { color : black; "
                          "margin-left: 10px;"
                          "margin-right: 10px; }");

    m_LabelDate.setAlignment(Qt::AlignRight);
    m_LabelDate.setStyleSheet("QLabel { color : gray; "
                          "margin-left: 10px;"
                          "margin-right: 10px; }");

    m_LabelRepositoryName.setAlignment(Qt::AlignLeft);
    m_LabelRepositoryName.setStyleSheet("QLabel { color : gray; "
                          "margin-left: 10px;"
                          "margin-right: 10px; }");

    m_Button.setMaximumWidth(15);
    m_Button.setText("x");
    m_Button.setStyleSheet("QPushButton { color: red; }");
    m_Button.setFlat(true);
    connect(&m_Button, &QPushButton::clicked, this, &PopUpNotifierWindow::pushButtonClickedSlot);

    m_Layout.addWidget(&m_Button, 0, 1, Qt::AlignRight);
    m_Layout.addWidget(&m_LabelAuthor, 0, 0);
    m_Layout.addWidget(&m_LabelMessage, 1, 0);
    m_Layout.addWidget(&m_LabelRepositoryName, 2, 0);
    m_Layout.addWidget(&m_LabelDate, 2, 0);
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

    painter.setBrush(QBrush(QColor(255, 250, 250, 255)));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(roundedRect, 0, 0);
}

void PopUpNotifierWindow::setPopUpText(const commit& commit, const std::string& name)
{
    m_LabelAuthor.setText(commit.author.c_str());
    m_LabelDate.setText(commit.date_time.c_str());
    m_LabelRepositoryName.setText(name.c_str());
    setMaximumWidth(500);

    if (commit.message.size() > 72)
    {
        m_LabelMessage.setText(commit.message.substr(0, 68).append("...").c_str());
    }
    else
    {
        setMaximumWidth(400);
        m_Layout.setColumnStretch(0, 400);
        m_LabelMessage.setText(commit.message.c_str());
    }
}

void PopUpNotifierWindow::show()
{
    setWindowOpacity(0.0);
    m_Animation.setDuration(150);
    m_Animation.setStartValue(0.0);
    m_Animation.setEndValue(1.0);

    setGeometry(QApplication::desktop()->availableGeometry().width() - width() + QApplication::desktop()->availableGeometry().x(),
                QApplication::desktop()->availableGeometry().height() - height() + QApplication::desktop()->availableGeometry().y(),
                width(),
                height());
    QWidget::show();
    m_Animation.start();
    m_Timer->start(1500);
    QSound::play(":/sounds/sounds/open-ended.wav");
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
