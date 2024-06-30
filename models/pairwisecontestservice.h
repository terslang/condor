#pragma once
#include <TGlobal>

class THttpRequest;
class TSession;


class T_MODEL_EXPORT PairwiseContestService {
public:
    void index();
    void show(int electionId);
    int create(int electionId, const QString& optionAId, const QString& optionBId);
    void edit(TSession &session, int electionId);
    int save(THttpRequest &request, TSession &session, int electionId);
    bool remove(int electionId);
};

