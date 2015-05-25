#include "orm.hpp"

#pragma once

class sales_invoice;
class customer : public mvcpp::orm_object<customer>
{
    ORM_OBJECT(customer);
public:
    std::string name()
    {
        if(_company_name.length() > 0)
        {
            return _company_name + " (" + _first_name + " " + _last_name + ")";
        }
        return _first_name + " " + _last_name;
    }
    std::shared_ptr<sales_invoice> create_invoice();
    static std::vector<std::shared_ptr<customer>> search(std::string query);
    
private:
    std::string _first_name;
    std::string _last_name;
    std::string _company_name;
    std::string _phone;
    std::string _mobile;
    std::string _email;
    std::string _street_and_no;
    std::string _postal_code;
    std::string _city;
    std::string _country;
    std::string _vat_number;

    static void register_fields();
};
