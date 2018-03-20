#include "Stage.h"

Stage::Stage() {
}

void Stage::setName(QString name) {
    this -> m_Name = name;
}

void Stage::setResult(QString result) {
    this -> m_Result = result;
}

QString Stage::getName() {
    return m_Name;
}

QString Stage::getResult() {
    return m_Result;
}
