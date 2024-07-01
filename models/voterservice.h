#pragma once
#include "voter.h"
#include <TGlobal>

class THttpRequest;
class TSession;

class T_MODEL_EXPORT VoterService
{
public:
  void index();
  void show(const QString& email, int electionId);
  QString create(THttpRequest& request);
  QString create(const QString& email, int electionId);
  void edit(TSession& session, const QString& email, int electionId);
  int save(THttpRequest& request,
           TSession& session,
           const QString& email,
           int electionId);
  bool remove(const QString& email, int electionId);
  bool hasVoted(const QString& email, int electionId);
};
