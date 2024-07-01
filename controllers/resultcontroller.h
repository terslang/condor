#pragma once

#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT ResultController : public ApplicationController
{
  Q_OBJECT
public:
  ResultController()
    : ApplicationController()
  {
  }

public slots:
  void show(const QString& electionId);
  void create(const QString& electionId);
  bool preFilter() override;
};
