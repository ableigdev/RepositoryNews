#include "FillComboBox.h"
#include <algorithm>

void helpers::fillTimeComboBox(QComboBox* comboBox)
{
    if (comboBox != nullptr)
    {
        comboBox->addItem("5 minutes");
        comboBox->addItem("30 minutes");
        comboBox->addItem("1 hour");
    }
}

void helpers::fillBranchComboBox(std::vector<std::string>&& nameOfBranches, QComboBox* comboBox)
{
    if (comboBox != nullptr)
    {
        std::for_each(nameOfBranches.begin(), nameOfBranches.end(), [=](auto it){ comboBox->addItem(it.c_str()); });
    }
}
