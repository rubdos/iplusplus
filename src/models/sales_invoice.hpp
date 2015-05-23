#include "orm.hpp"

#pragma once

class sales_invoice : public mvcpp::orm_object<sales_invoice>
{
    ORM_OBJECT(sales_invoice);

    HAS_ONE(customer);

private:
    static void register_fields()
    {
        field(&sales_invoice::_customer_id, "Customer ID");
        field(&sales_invoice::_invoice_number, "Invoice Number");
    }

    std::string _invoice_number;
};
