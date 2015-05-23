#pragma once

#include <application.hpp>
#include "controllers/home.hpp"
#include "controllers/customer.hpp"

#include "models/customer.hpp"
#include "models/sales_invoice.hpp"

#include <orm/sqlite.hpp>

class ippapp : public mvcpp::application
{
public:
    ippapp(unsigned short port) : application(port)
    {
        set_default_template("template");

        mvcpp::database::current_database = new mvcpp::sqlite("data.db"); // start database

        // Register all controllers
        register_controller<home_controller>();
        register_controller<customer_controller>();

        // Register all models
        customer::create_tables(true);
        sales_invoice::create_tables(true);
    }
    virtual void initialize_default_template(mvcpp::context::ptr ctx) override
    {
        ctx->get_template().subview("MENU") = ctx->get_view("_menu");
        ctx->get_template()["TITLE"] = "i++ | Customizable customers and invoicing system";
    }
};
