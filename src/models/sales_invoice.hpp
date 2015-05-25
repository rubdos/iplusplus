#include <ctime>

#include "customer.hpp"
#include "orm.hpp"

#pragma once

class sales_invoice : public mvcpp::orm_object<sales_invoice>
{
    ORM_OBJECT(sales_invoice);

    HAS_ONE(customer);
public:
    void generate_number();
    virtual void init() override
    {
        _invoice_time = time(NULL);
        _payment_time = 0;
    }

private:
    static void register_fields()
    {
        field(&sales_invoice::_customer_id, "Customer ID");
        field(&sales_invoice::_invoice_number, "Invoice Number");
        field(&sales_invoice::_invoice_time, "Invoice Time");
        field(&sales_invoice::_payment_time, "Payment Time");
    }

    std::string _invoice_number;
    time_t _invoice_time;
    time_t _payment_time;
};
