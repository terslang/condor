#pragma once

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT HomeController : public ApplicationController
{
    Q_OBJECT
public:
    HomeController() : ApplicationController() { }

public slots:
    void index();
    bool preFilter() override;
};

