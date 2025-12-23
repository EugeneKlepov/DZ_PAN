#include "Aircraft.hpp"
#include "Environment.hpp"
#include <cmath>
#include <print>

AircraftData::AircraftData(){}
AircraftData::~AircraftData(){}
double AircraftData::StartMass() const {return start_mass_;}
double AircraftData::WingArea() const {return wing_area_;}
double AircraftData::EngineCount() const {return  EngineCount_;}


