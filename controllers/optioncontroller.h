#pragma once
#include "applicationcontroller.h"

class T_CONTROLLER_EXPORT OptionController : public ApplicationController
{
  Q_OBJECT
public slots:
  void index();
  void show(const QString& id);
  void create(const QString& electionId);
  void create();
  void save(const QString& id);
  void remove(const QString& id);
  bool preFilter() override;
};
