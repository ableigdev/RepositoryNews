#ifndef POPUPNOTIFIERWINDOW_H
#define POPUPNOTIFIERWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPushButton>

class PopUpNotifierWindow : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(float popupOpacity READ getPopupOpacity WRITE setPopupOpacity)
public:
    explicit PopUpNotifierWindow(QWidget* parent = nullptr);

public slots:
    void setPopUpText(const QString& text);
    void show();

private slots:
    void stopTimerSlot();
    void hideSlot();
    void pushButtonClickedSlot();

protected:
    void paintEvent(QPaintEvent* event);

private:
    void setPopupOpacity(double opacity);
    double getPopupOpacity() const;

private:
    QLabel m_Label;
    QPushButton m_Button;
    QGridLayout m_Layout;
    QPropertyAnimation m_Animation;
    double m_PopUpOpacity;
    QTimer* m_Timer;
};

#endif // POPUPNOTIFIERWINDOW_H
