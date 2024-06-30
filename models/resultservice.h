#pragma once
#include <TGlobal>

class THttpRequest;

class T_MODEL_EXPORT ResultService {
public:
    void show(int electionId);
    int create(THttpRequest &request);
};

