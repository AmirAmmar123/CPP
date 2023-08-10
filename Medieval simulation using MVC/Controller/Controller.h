//
// Created by merom on 6/17/2023.
//

#ifndef HOMEWORK3_CONTROLLER_H
#define HOMEWORK3_CONTROLLER_H

#include <memory>
#include "../Viewer/Viewer.h"
#include "../Utilities/Validator.h"
#include "../Utilities/Tookenizer.h"
#include "../Utilities/Geometry.h"
#include "../Factory/structure_factory/factory.h"
#include "../Factory/agent_factory/factory.h"
#include "../Model/Model.h"
#include <fstream>
#include <map>

using KnightName = std::string;
using SiteName = std::string;
using PeasentName = std::string;
using PeasentCommands = std::pair<sharedFarm ,sharedCastle>;
using visited = bool;
using KnightMap = std::unique_ptr<std::map<site_name,visited>>;
using KnightsAndTheirMaps = std::map<KnightName, KnightMap>;
using QueueOfCommands = std::queue<PeasentCommands>;
using PeasantsJobs = std::map<PeasentName,QueueOfCommands>;


constexpr const static double is_one_km = 1.;
constexpr const static double is_two_km_and_half = 2.5;


class Controller{
public:
    void castle_file_Tookenizer(const std::string& fileName);
    void farm_file_Tookenizer(const std::string& fileName);
    Controller(int argc, char* argv[]);
    Controller()=default;
    ~Controller()=default;
    Controller(const Controller& rhs)=delete;
    Controller& operator=(const Controller& rhs)=delete;
    void startGame();

private:
    void create(const immutable & tuple);
    static void setCourseSpeed(const immutable & tuple);
    static void setPosition(const immutable & tuple);
    static void setDestinationForKnight(const immutable & tuple);
    void attack(const immutable & tuple);
    void setStop(const immutable & tuple);
    static void checkIfExists(const std::string & name);
    void GiveKnightNewDestination();
    void GivePeasentsNewJob();
    void setKnightMap(const KnightName & name, const std::string & castleSpoon);
    void loadmap(int argc, char* argv[]);
    void setJob(const immutable & tuple);

    std::shared_ptr<Viewer> _view_ptr;
    std::unique_ptr<Validator> validator;
    KnightsAndTheirMaps knightsAndTheirMaps;
    PeasantsJobs peasentsJobsMapper;

};
#endif //HOMEWORK3_CONTROLLER_H
