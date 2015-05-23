#pragma once

#include <string.h>
#include <controller.hpp>
#include <context.hpp>

#include "models/customer.hpp"

class customer_controller : public mvcpp::controller<customer_controller>
{
public:
    virtual void register_routes(mvcpp::router& r) override
    {
        r("/customers", &customer_controller::index);
        r("/customers/:", &customer_controller::view);
        r("/customers/new", &customer_controller::insert);
        r.post("/customers/new", &customer_controller::insert_post);
    }

    void index(mvcpp::context::ptr ctx)
    {
        auto page = ctx->get_view("customer/index");

        // Retrieve all customers
        auto customers = customer::find_all();
        std::string table;

        auto row = ctx->get_view("customer/index_table_line");
        for(auto c: customers)
        {
            row["ID"] = std::to_string(c->id());
            row["NAME"] = c->value<std::string>("Last Name");
            row["COMPANY"] = c->value<std::string>("Company Name");
            row["FIRST NAME"] = c->value<std::string>("First Name");
            row["EMAIL"] = c->value<std::string>("Email");
            row["VAT"] = c->value<std::string>("VAT number");

            table += row.render() + "\n";
        }
        page["TABLE"] = table;
        ctx->get_template().subview("PAGE") = page;
    }
    void view(mvcpp::context::ptr ctx)
    {
        auto page = ctx->get_view("customer/view");

        auto c = customer::get(atol(ctx->get_path().substr(11).c_str())); // This is not beautiful
        page["CUSTOMER_NAME"] = c->name();

        ctx->get_template().subview("PAGE") = page;
    }
    void insert(mvcpp::context::ptr ctx)
    {
        auto page = ctx->get_view("customer/new");
        ctx->get_template().subview("PAGE") = page;
    }
    void insert_post(mvcpp::context::ptr ctx)
    {
        auto page = ctx->get_view("customer/new");
        std::cout << "customer::index" << std::endl;
        ctx->get_template().subview("PAGE") = page;
        auto c = customer::factory(true,
            { 
                {"First Name", ctx->post_data("first_name").c_str()},
                {"Last Name", ctx->post_data("name").c_str()},
                {"Company Name", ctx->post_data("company_name").c_str()},
                {"Phone", ctx->post_data("phone").c_str()},
                {"Mobile Phone", ctx->post_data("mobile").c_str()},
                {"Email", ctx->post_data("email").c_str()},
                {"Street and number", ctx->post_data("street").c_str()},
                {"Postal code", ctx->post_data("postal_code").c_str()},
                {"City", ctx->post_data("city").c_str()},
                {"Country", ctx->post_data("country").c_str()},
                {"VAT number", ctx->post_data("vat").c_str()}
                }
            );
        std::stringstream url;
        url << "/customers/" << c->id();
        ctx->response_header("Location", url.str());
        ctx->set_response_code(303);
        // Fields of customer:
        // field(&customer::_first_name, "First Name");
        // field(&customer::_last_name, "Last Name");
        // field(&customer::_company_name, "Company Name");
        // field(&customer::_phone, "Phone");
        // field(&customer::_mobile, "Mobile Phone");
        // field(&customer::_email, "Email");
        // field(&customer::_street_and_no, "Street and number");
        // field(&customer::_postal_code, "Postal code");
        // field(&customer::_city, "City");
        // field(&customer::_country, "Country");
        // field(&customer::_vat_number, "VAT number");
    }
};
