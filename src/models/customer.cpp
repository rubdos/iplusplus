#include "customer.hpp"
#include "sales_invoice.hpp"

std::shared_ptr<sales_invoice> customer::create_invoice()
{
    auto s = sales_invoice::factory();
    s->value("Customer ID", id());
    return s;
}
std::vector<std::shared_ptr<customer>> customer::search(std::string query)
{
    auto cs = customer::find_all();
    for(auto it = cs.begin();
            it != cs.end();
            ++it)
    {
        auto find = [&query](decltype(it) it){
            std::string name = (*it)->name();
            return (
                    std::search(name.begin(), name.end(),
                        query.begin(), query.end(), [](char c1, char c2){
                            return std::tolower(c1) == std::tolower(c2);
                        })
                    != name.end());
        };

        while(!find(it))
        {
            it = cs.erase(it);
            if(it == cs.end())
                break;
        }
        if(it == cs.end())
            break;
    }
    return cs;
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
