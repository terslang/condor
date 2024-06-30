#pragma once

#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT ResultController : public ApplicationController
{
    Q_OBJECT
public:
    ResultController() : ApplicationController() { }

public slots:
    void show(const QString &id);
    void create();
};

