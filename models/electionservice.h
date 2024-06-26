#pragma once
#include <TGlobal>

class THttpRequest;
class TSession;


class T_MODEL_EXPORT ElectionService {
public:
    void index();
    void show(int id);
    int create(THttpRequest &request);
    void edit(TSession &session, int id);
    int save(THttpRequest &request, TSession &session, int id);
    bool remove(int id);
};

