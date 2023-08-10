//
// Created by merom on 6/17/2023.
//
#include "Model.h"

SingeltonModel Model::_model_inst = nullptr;

Model & Model::getInstance() {
    if(_model_inst == nullptr) {
        _model_inst =  SingeltonModel(new Model);
    }
    return *_model_inst;
}

KnightList &Model::getKnights() {
    return _knightsList;
}

PeasentList &Model::getPeasants() {
    return _peasentsList;
}

ThugsList &Model::getThugs() {
    return _thugsList;
}

FarmsList &Model::getFarms() {
    return _farmsList;
}

const CastlesList &Model::getCastles() {
    return _castlesList;
}

sharedKnight Model::getKnight(const string &name) {
    auto ptr = std::find_if(_knightsList.begin(), _knightsList.end(), [&name](const auto & knight ){
        return knight->getName() == name;
    });
    return ptr != _knightsList.end() ? *ptr : nullptr;
}

sharedPeasant Model::getPeasant(const string &name) {
    auto ptr = std::find_if(_peasentsList.begin(), _peasentsList.end(), [&name](const auto & peasant ){
        return peasant->getName() == name;
    });
    return ptr != _peasentsList.end() ? *ptr : nullptr;
}

sharedThug Model::getThug(const string &name) {
    auto ptr = std::find_if(_thugsList.begin(), _thugsList.end(), [&name](const auto & thug ){
        return thug->getName() == name;
    });
    return ptr != _thugsList.end() ? *ptr : nullptr;
}

sharedCastle Model::getCastle(const string &name) {
    auto ptr = std::find_if(_castlesList.begin(), _castlesList.end(), [&name](const auto & castle ){
        return castle->getName() == name;
    });
    return ptr != _castlesList.end() ? *ptr : nullptr;
}

sharedFarm Model::getFarm(const string &name) {
    auto ptr = std::find_if(_farmsList.begin(), _farmsList.end(), [&name](const auto & farm ){
        return farm->getName() == name;
    });
    return ptr != _farmsList.end() ? *ptr : nullptr;
}



void Model::add(sharedKnight knight) {
    if(knight){
        _knightsList.emplace_back(std::move(knight));
    }
}

void Model::add(sharedPeasant peasant) {
    if(peasant){
        _peasentsList.emplace_back(std::move(peasant));
    }
}

void Model::add(sharedThug thug) {
    if(thug){
        _thugsList.emplace_back(std::move(thug));
    }
}

void Model::add(sharedCastle castle) {
    if(castle){
        _castlesList.emplace_back(std::move(castle));
    }
}

void Model::add(sharedFarm farm) {
    if(farm){
        _farmsList.emplace_back(std::move(farm));
    }
}

const unsigned int &Model::getTime() const {
    return _time;
}

void Model::update() {
    std::for_each(_farmsList.begin(), _farmsList.end(),[](auto & farm ){
        farm->update();
    });
    std::for_each(_castlesList.begin(),_castlesList.end(),[](auto & castle){
        castle->update();
    });
    std::for_each(_thugsList.begin(),_thugsList.end(),[](auto & thug){
        thug->update();
    });
    std::for_each(_peasentsList.begin(),_peasentsList.end(),[](auto & peasent){
        peasent->update();
    });
    std::for_each(_knightsList.begin(), _knightsList.end(), [](auto & knight){
        knight->update();
    });
    _time++;
    
}

void Model::broadcast() {
    std::for_each(_farmsList.begin(), _farmsList.end(),[](auto & farm ){
        farm->broadcast_current_state();
    });
    std::for_each(_castlesList.begin(),_castlesList.end(),[](auto & castle){
        castle->broadcast_current_state();
    });
    std::for_each(_thugsList.begin(),_thugsList.end(),[](auto & thug){
        thug->broadcast_current_state();
    });
    std::for_each(_peasentsList.begin(),_peasentsList.end(),[](auto & peasent){
        peasent->broadcast_current_state();
    });
    std::for_each(_knightsList.begin(), _knightsList.end(), [](auto & knight){
        knight->broadcast_current_state();
    });
}

bool Model::find_if_exist(const string &name)  {
    return   (
               getKnight(name)  ||
               getPeasant(name) ||
               getThug(name)    ||
               getCastle(name)  ||
               getFarm(name)

               );
}










