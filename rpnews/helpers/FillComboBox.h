#ifndef FILLCOMBOBOX_H
#define FILLCOMBOBOX_H

#include <QComboBox>
#include <vector>
#include <string>

namespace helpers
{
    void fillTimeComboBox(QComboBox* comboBox);
    void fillBranchComboBox(std::vector<std::string>&& nameOfBranches, QComboBox* comboBox);
}

#endif // FILLCOMBOBOX_H
