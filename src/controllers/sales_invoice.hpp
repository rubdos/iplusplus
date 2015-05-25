#pragma once

#include <string.h>
#include <string>
#include <controller.hpp>
#include <context.hpp>

#include "models/sales_invoice.hpp"

class sales_invoice_controller : public mvcpp::controller<sales_invoice_controller>
{
public:
    virtual void register_routes(mvcpp::router& r) override
    {
        r("/sales_invoices", &sales_invoice_controller::index);
        r("/sales_invoices/view/:", &sales_invoice_controller::view);
        r("/sales_invoices/new", &sales_invoice_controller::insert);
        r("/sales_invoices/new/:", &sales_invoice_controller::insert_by_customer);
    }

    void index(mvcpp::context::ptr ctx)
    {
        auto page = ctx->get_view("sales_invoice/index");

        // Retrieve all invoices
        auto invoices = sales_invoice::find_all();
        std::string table;

        auto row = ctx->get_view("sales_invoice/index_table_line");
        for(auto invoice: invoices)
        {
            char time[100];
            auto t = invoice->value<time_t>("Invoice Time");
            struct tm* timeptr = localtime(&t);
            strftime(time, 100, "%d %B %Y", timeptr);
            row["INVOICE DATE"] = std::string(time);

            t = invoice->value<time_t>("Payment Time");
            timeptr = localtime(&t);
            strftime(time, 100, "%d %B %Y", timeptr);
            row["PAYED"] = ((t > 0) ? std::string(time) : "<span style=\"color:red;\">No</span>");

            row["NUMBER"] = invoice->value<std::string>("Invoice Number");
            row["CUSTOMER NAME"] = invoice->get_customer()->name();
            table += row.render() + "\n";
        }

        if(invoices.size() == 0)
        {
            table = "<tr><td colspan=\"5\" class=\"no-content\">No invoices</td></tr>";
        }
        page["TABLE"] = table;
        ctx->get_template().subview("PAGE") = page;
    }
    void view(mvcpp::context::ptr ctx)
    {
    }
    void insert_by_customer(mvcpp::context::ptr ctx)
    {
        std::cout << "insert_by_customer" << std::endl;
        auto page = ctx->get_view("sales_invoice/edit_invoice");

        auto c = customer::get(atol(ctx->get_parameter().c_str()));
        auto invoice = c->create_invoice();
        invoice->save();
        invoice->generate_number();
        if(c == nullptr)
            return;
        page["CUSTOMER NAME"] = c->name();
        page["INVOICE NUMBER"] = invoice->value<std::string>("Invoice Number");
        invoice->save();

        ctx->get_template().subview("PAGE") = page;
    }
    void insert(mvcpp::context::ptr ctx)
    {
        auto page = ctx->get_view("sales_invoice/new");

        ctx->get_template().subview("PAGE") = page;
    }
};
