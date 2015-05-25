#include <time.h>

#include "sales_invoice.hpp"

void sales_invoice::generate_number()
{
    time_t now = time(NULL);
    struct tm *atime = localtime(&now);

    int year = atime->tm_year + 1900;
    std::string sId = std::to_string(id());
    this->_invoice_number = "SI" + std::to_string(year);
    for(int i = 0; i < 4 - sId.length(); i++)
    {
        this->_invoice_number += "0";
    }
    this->_invoice_number += sId;
}
