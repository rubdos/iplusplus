#pragma once

#include <string.h>
#include <controller.hpp>
#include <context.hpp>

class home_controller : public mvcpp::controller<home_controller>
{
public:
    virtual void register_routes(mvcpp::router& r) override
    {
        r("/", &home_controller::index);
    };

    void index(mvcpp::context::ptr ctx)
    {
    }
};
