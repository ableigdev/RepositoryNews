#include "GetTimeInterval.h"
#include <QMessageBox>

std::chrono::seconds helpers::getTimeInterval(int index)
{
    switch (index)
    {
        case 0:
        {
            std::chrono::minutes min {5};
            return min;
        }
        case 1:
        {
            std::chrono::minutes min {30};
            return min;
        }
        case 2:
        {
            std::chrono::hours hour{1};
            return hour;
        }
        default:
        {
            QMessageBox::warning(nullptr, "Error", "Wrong index");
            std::chrono::minutes min {5};
            return min;
        }
    }
}
