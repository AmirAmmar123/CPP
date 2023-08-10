//
// Created by merom on 6/22/2023.
//


#include "Controller.h"

#include <memory>



Controller::Controller(int argc, char **argv): _view_ptr{make_shared<Viewer>()},
validator{std::make_unique<Validator>("")}
{

    loadmap(argc, argv);
}


void Controller::loadmap(int argc, char **argv) {
    try {
        if (argc != 3) {
            throw Validator("Usages: must be <executable> <castles.dat> <farms.dat>");
        }
        castle_file_Tookenizer(argv[1]);
        farm_file_Tookenizer(argv[2]);

    } catch (Validator& e){
        cerr << e.what() << endl;
        exit(1);
    }

}


void Controller::farm_file_Tookenizer(const string &fileName) {
    using namespace std;
    ifstream file(fileName);

    if (!file) throw Validator("File not found " + fileName);
    string line;

    Delimiters delimiters("(,)");

    while (getline(file,line)){
        if(!validator->verifyFormatFarm(line)) throw Validator("Invalid format " + line);

        TokenIterator<decltype(line.begin()),Delimiters> beging(line.begin(),line.end(),delimiters), end;
        vector<std::string> vec(beging,end);

        Model::getInstance().add(
                std::dynamic_pointer_cast<Farm>(
                        genericFactory2<Structure>::instance().create(
                                "Farm",
                                vec[0], // farm name
                                {stof(vec[2]),stof(vec[3])}, // location
                                 stoi(vec[4]), // initial crates
                                 stoi(vec[5])) // production rate per hour
                )
        );
    }

    file.close();

}

void Controller::castle_file_Tookenizer(const string &fileName) {

    using namespace std;
    ifstream file(fileName);
    if (!file) throw Validator("File not found " + fileName);
    string line;
    Delimiters delimiters("(,)");

    while (getline(file,line)){
        if(!validator->verifyFormatCastle(line)) throw Validator("Invalid format " + line);

        TokenIterator<decltype(line.begin()),Delimiters> beging(line.begin(),line.end(),delimiters), end;
        vector<std::string> vec(beging,end);

        Model::getInstance().add(
                std::dynamic_pointer_cast<Castle>(
                        genericFactory2<Structure>::instance().create(
                                "Castle",
                                vec[0], // castle name
                                {stof(vec[2]),stof(vec[3])}, // coordination
                                stoi(vec[4]), // initial crates
                                0)
                        )
                );
    }

    file.close();


}

void Controller::startGame() {
    string cmd;
    vector<string> commands;
    const unsigned int &time = Model::getInstance().getTime();
    cout << "Time " << time << ": Enter command: ";
    while(getline(std::cin, cmd)){
       try{
           auto val = validator->isLineMappedToEnum(cmd);
           switch(std::get<0>(val)){
               case Commands::EXIT:
                   return ;
               case Commands::CREATE:
                   create(val);
                   break;
               case Commands::COURSE:
                   setCourseSpeed(val);
                   break;
               case Commands::DESTINATION:
                   setDestinationForKnight(val);
                   break;
               case Commands::GO:
                   GiveKnightNewDestination();
                   GivePeasentsNewJob();
                   Model::getInstance().update();
                   break;
               case Commands::STATUS:
                   Model::getInstance().broadcast();
                   break;
               case Commands::ATTACK:
                   attack(val);
                   break;
               case Commands::STOP:
                   setStop(val);
                   break;
               case Commands::POSITION:
                   setPosition(val);
                   break;
               case Commands::STARTWORKING:
                   setJob(val);
                   break;
               case Commands::SHOW :
                   _view_ptr->show();
                   break;
               case Commands::PAN :
                   _view_ptr->pan(static_cast<float>( std::get<4>(val).x) ,
                                  static_cast<float>( std::get<4>(val).y));
                   break;
               case Commands::ZOOM :
                   _view_ptr->setZoom(static_cast<float>( std::get<6>(val) ));
                   break;
               case Commands::SIZE:
                   _view_ptr->setSize( static_cast<int>( std::get<6>(val) ) ) ;
                   break;
               case Commands::DEFAULT:
                   _view_ptr->setDefault();
                   break;
               default:
                   throw Validator("Illegal command, please try again\n");
           }
       }catch(Validator & e)
       {
           cerr<<e.what()<<endl;
       }
        cout << "Time " << time << ": Enter command: ";
    }
}



void Controller::setKnightMap( const KnightName & knightName,const std::string & castleSpoon) {
    KnightMap map = std::make_unique<std::map<site_name,visited>>();
    sharedKnight knight = Model::getInstance().getKnight(knightName);
    knight->setSpoonCast(castleSpoon);

    (*map)[castleSpoon] = true;


    for (const auto & farm : Model::getInstance().getFarms()){
        (*map)[farm->getName()] = false;
    }

    for (const auto & castle : Model::getInstance().getCastles()) {
        if(castle->getName() != castleSpoon){
            (*map)[castle->getName()] = false;
        }
    }

    knightsAndTheirMaps[knightName] = std::move(map);

}

void Controller::create(const immutable & val) {
    std::string name =  std::get<1>(val);
    if(Model::getInstance().find_if_exist(name) ){
        throw Validator("Name " + name + " already in use");
    }else{
        if( std::get<2>(val) == "Knight"){
            //std::tuple<Commands, name, type, site_name, location,degree, speed>;
            std::string site_name = std::get<3>(val);
            auto shared_castle = Model::getInstance().getCastle(site_name);
            if(shared_castle){
                Model::getInstance().add(
                        std::dynamic_pointer_cast<Knight>(
                                genericFactory<Agent>::instance().create(
                                        "Knight",
                                        name,
                                        { shared_castle->getLocation().x/10, shared_castle->getLocation().y/10}
                                )
                        )
                );
                setKnightMap(name, shared_castle->getName());
                GiveKnightNewDestination();
            }else{
                throw Validator("Castle " + std::get<3>(val) + " not found");
            }
        }else if(std::get<2>(val) == "Peasant"){
            //std::tuple<Commands, name, type, site_name, location,degree, speed>;
            Point  location =   std::get<4>(val) ;
            Model::getInstance().add(
                    std::dynamic_pointer_cast<Peasant>(
                            genericFactory<Agent>::instance().create(
                                    "Peasant",
                                    name,
                                    location
                            )
                    )
            );
        }else if( std::get<2>(val) == "Thug" ){
            //std::tuple<Commands, name, type, site_name, location,degree, speed>;
            Model::getInstance().add(
                    std::dynamic_pointer_cast<Thug>(
                            genericFactory<Agent>::instance().create(
                                    "Thug",
                                    name,
                                    std::get<4>(val)
                            )
                    )
            );
        }
    }
}

void Controller::setDestinationForKnight(const immutable &tuple) {
    std::string name =  std::get<1>(tuple);
    std::string site = std::get<3>(tuple);
    checkIfExists(name);
    checkIfExists(site);

    auto knight = Model::getInstance().getKnight(name);
    auto castle = Model::getInstance().getCastle(name);
    auto farm = Model::getInstance().getFarm(name);

    if(knight){
        if(castle){
            knight->move_to(castle->getLocation(), site, knight->getSpeed());
            return;
        }
        if(farm){
            knight->move_to(farm->getLocation(), site, knight->getSpeed());
            return;
        }
    }else{
        throw Validator(name + " is not a knight\n");
    }

}


void Controller::GivePeasentsNewJob() {
    PeasentList & Peasents = Model::getInstance().getPeasants();

    for(auto & peasent : Peasents){
        /* if a job is finished or peasant is not died then*/
        if(peasent->checkIfJobFinished() && !peasent->isDead()){

            /*if a Peasant has a job within the queue then*/
            if(!peasentsJobsMapper[peasent->getName()].empty()){
                peasent->move();
                /*push a new job for peasant*/
                peasent->push_job(peasentsJobsMapper[peasent->getName()].front().first, peasentsJobsMapper[peasent->getName()].front().second);

                peasentsJobsMapper[peasent->getName()].pop();
            }

        }
    }
}




void Controller::GiveKnightNewDestination() {
    KnightList & knights = Model::getInstance().getKnights();

    auto comp = [](const double &a, const double & b){return a < b;};

    std::map<std::string, Point> nextKnightCommand;

    for(sharedKnight & knight : knights){
        bool found = false;


        if(knight->getPilotMode() && knight->getPhysicsDone()){// maybe he is moving on autopilot but still have not reached the closest destination


            std::multimap<double, std::string, decltype(comp)> norms(comp);

            /*iterate on this knight map */
            for(auto & site : *(knightsAndTheirMaps)[knight->getName()] ){

                /*get a knight sites map sorted according to the ||V|| = sqrt(vdot(v)),
                 * find the closet norm point to knight
                 * */

                if(site.first == knight->getCityDestination()){
                    site.second = true;
                }

                auto castle = Model::getInstance().getCastle(site.first);
                auto farm = Model::getInstance().getPeasant(site.first);

                if(castle){
                    norms.insert(std::pair<double, std::string>(getNorm(knight->getLocation(),castle->getLocation()), castle->getName()));
                }else if (farm){
                    norms.insert(std::pair<double, std::string>(getNorm(knight->getLocation(),farm->getLocation()), castle->getName()));
                }


            }

            for(const auto & norm : norms){
                /* find the first minimum norm find in the norm map
                 * that has not been visited by the knight if found
                 * */
                if(!(*(knightsAndTheirMaps)[knight->getName()])[norm.second]){
                    found = true;
                    auto castle =  Model::getInstance().getCastle(norm.second);
                    auto farm = Model::getInstance().getFarm(norm.second);

                    if(castle){
                        knight->autoPilotCommand(castle->getLocation(), castle->getName());
                        break;
                    }
                    if(farm){
                        knight->autoPilotCommand(farm->getLocation(), farm->getName());
                        break;
                    }

                }

            }
            /*it seems that the knight visited all places, so it's time to go back to
             * the spoon castle and start again
             * set all places that has been visited as false*/
            if(!found){
                auto castle = Model::getInstance().getCastle(knight->getSpoonCastle());
                knight->autoPilotCommand(castle->getLocation(), castle->getName());

                auto & knightmap = *(knightsAndTheirMaps)[knight->getName()] ;
                for(auto & site : knightmap) {
                        site.second = false;
                }
                break;
            }
        }
    }
}





void Controller::setCourseSpeed(const immutable &val) {
    /*NOT FOR FARMER*/
    std::string name =  std::get<1>(val);
    double degree = std::get<5>(val);
    double speed = std::get<6>(val);

    //std::tuple<Commands, name, type, site_name, location,degree, speed>;
    checkIfExists(name);

    auto knight = Model::getInstance().getKnight(name);
    auto thug = Model::getInstance().getThug(name);
    auto farmer = Model::getInstance().getPeasant(name);

    if(thug){
             thug->course(degree, speed);
             return;
    }

    if( (knight && speed == 10) || (knight && speed == 0) ){
        knight->cancelAutoPilot();
        knight->course(degree); // set degree and update on course
        return;
    }else if((knight && speed != 10) || (knight && speed != 0) ){
        throw Validator("Knight has a constant speed 10k/h, can't assign speed " + std::to_string(speed));
    }
    if(farmer){
        throw Validator("peasant does not support course functionality\n");
    }
}

void Controller::setPosition(const immutable &val) {
    /*NOT FOR FARMER*/
    std::string name =  std::get<1>(val);

    checkIfExists(name);
    auto knight = Model::getInstance().getKnight(name);
    auto thug = Model::getInstance().getThug(name);
    auto farmer = Model::getInstance().getPeasant(name);

    Point p = std::get<4>(val);
    if(knight){
        //std::tuple<Commands, name, type, site_name, location,degree, speed>;
        knight->move_to(std::get<4>(val), "("+ std::to_string(p.x) + ", " + std::to_string(p.y)+ ")",10);

        return;
    }

    if(thug){
        double speed = std::get<5>(val);
        if(speed < 0 || speed > 30 ){
            throw Validator("speed of thug bellow 0 or speed exceeded 30 k/h: speed " + std::to_string(speed));
        }
        thug->move_to(std::get<4>(val),  "("+ std::to_string(p.x) + ", " + std::to_string(p.y)+ ")", speed);
    }

    if(farmer){
        throw Validator("peasant does not support position functionality\n");
    }


}


/* attack a peasant if:
 *    1: the farmer is within one k'm radius from thug
 *    2: the power units of the thug are greater than farmer power unit
 *    3: there is no Knight in 2.5 k'm radius around the thug
 * */

/*
 *  Agent Peasant cases:
 *    1: successful attack on the peasant:
 *        a: causing him losing one unit power => health --
 *        b: causing him to lose all crates
 *        c: change status from moving to Stopped
 *    2: unsuccessful attacks:
 *        the peasant continues with command regularly like nothing happened
 *
 *  Agent Thug cases:
 *        a: whether it's a successful attack or not halt (status = STOPPED!!!)
 *        b: successful attack =>  power_units+=1
 *        c: unsuccessful attack =>  power_units-=1
 *
 *  Both Agents cases:
 *       a: if health/power_units == 0 then status is DEAD!!!
 *
 *  Agent Knight:
 *      not around do nothing
 * */
void Controller::attack(const immutable &val) {
    /*Only for thug*/

    std::string thug_name =  std::get<1>(val);
    std::string peasant_name = std::get<2>(val);

    checkIfExists(thug_name);
    checkIfExists(peasant_name);


    auto peasant_ptr = Model::getInstance().getPeasant(peasant_name);
    auto thug_ptr = Model::getInstance().getThug(thug_name);

    if(peasant_ptr == nullptr) throw Validator( peasant_ptr->getName() +" in_radius not a peasant\n");
    if(thug_ptr == nullptr) throw Validator( thug_ptr->getName() +" in_radius not a thug\n");

    if(thug_ptr->isDead() || peasant_ptr->isDead()){
        std::cout << ( (thug_ptr->isDead())?thug_ptr->getName():peasant_ptr->getName() \
        + " is dead, can't attack") << std::endl;
        return;
    }

    double norm = getNorm(peasant_ptr->getLocation(),thug_ptr->getLocation());

    bool in_radius = norm <= is_one_km;

    /* if farmer in_radius radius 1k'm and the power units of Thug are bigger than the health of peasant*/
    if(in_radius && (thug_ptr->getPowerUnits() > peasant_ptr->getPowerUnits())){

        /* each attack on peasant weather it's successful or not, we will cost him 1 HP*/
        peasant_ptr->reduce_units_by_one();

        for( const auto & knight : Model::getInstance().getKnights() ){
            /* if all knights are in_radius radius > 2.5 k'm from the thug */
            in_radius = (getNorm(peasant_ptr->getLocation(), knight->getLocation()) > is_two_km_and_half);
            if(!in_radius)
                break;
        }

    }

    /* Weather it's a successful attack or not halt Thug, set location to the location of the incident*/
    thug_ptr->halt();
    thug_ptr->setLocation(peasant_ptr->getLocation());
    if(!in_radius){
        /* if it's not a successful attack on peasant*/
        thug_ptr->reduce_units_by_one();

    }else{
        /* if it's a successful attack on peasant*/
        peasant_ptr->set_invy_zero();
        peasant_ptr->halt();

    }





}


void Controller::setStop(const immutable &val) {
    std::string name =  std::get<1>(val);
    checkIfExists(name);

    auto knight = Model::getInstance().getKnight(name);
    auto farmer = Model::getInstance().getPeasant(name);
    auto thug = Model::getInstance().getThug(name);

    if(knight){
        knight->cancelAutoPilot();
        knight->halt();
    }
    else if(farmer){
        farmer->halt();
    }
    else if(thug){
        thug->halt();
    }else{
        throw Validator(name + " is not a knight or thug or peasant\n");
    }


}


void Controller::checkIfExists(const string &name) {
    if(! Model::getInstance().find_if_exist(name) ){
        throw Validator("Name " + name + " does not exist");
    }
}

/**/
void Controller::setJob(const immutable &tuple) {
    std::string name = std::get<1>(tuple);
    std::string farm = std::get<2>(tuple);
    std::string castle = std::get<3>(tuple);

    checkIfExists(name);
    checkIfExists(castle);
    checkIfExists(farm);

    auto farm_ptr = Model::getInstance().getFarm(farm);
    auto castle_ptr = Model::getInstance().getCastle(castle);
    auto peasant_ptr = Model::getInstance().getPeasant(name);

    /*mapping between a peasant and queue of tasks*/
    if(!peasant_ptr->isDead())
        peasentsJobsMapper[peasant_ptr->getName()].emplace(farm_ptr,castle_ptr);
    else
       throw Validator(peasant_ptr->getName() + " is died");
}

