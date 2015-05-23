#include "customer.hpp"
#include "sales_invoice.hpp"

std::shared_ptr<sales_invoice> customer::create_invoice()
{
    //auto i = sales_invoice::factory(true, _id);
    return nullptr;
}
void customer::register_fields()
{
    field(&customer::_first_name, "First Name");
    field(&customer::_last_name, "Last Name");
    field(&customer::_company_name, "Company Name");
    field(&customer::_phone, "Phone");
    field(&customer::_mobile, "Mobile Phone");
    field(&customer::_email, "Email");
    field(&customer::_street_and_no, "Street and number");
    field(&customer::_postal_code, "Postal code");
    field(&customer::_city, "City");
    field(&customer::_country, "Country");
    field(&customer::_vat_number, "VAT number");
}
