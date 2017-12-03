#include "SimG4Core/SensitiveDetector/interface/SensitiveDetectorPluginFactory.h"
#include "SimG4Core/SensitiveDetector/interface/SensitiveDetector.h"
#include "SimG4Core/SensitiveDetector/interface/AttachSD.h"
#include <string>
#include <vector>

#include "FWCore/MessageLogger/interface/MessageLogger.h"

AttachSD::AttachSD() {}

AttachSD::~AttachSD() {}

std::pair< std::vector<SensitiveTkDetector*>,
	   std::vector<SensitiveCaloDetector*> > 
AttachSD::create(const DDDWorld & w, 
		 const DDCompactView & cpv,
		 const SensitiveDetectorCatalog & clg,
		 edm::ParameterSet const & p,
		 const SimTrackManager* man,
		 SimActivityRegistry& reg) const
{
  std::pair< std::vector<SensitiveTkDetector *>,std::vector<SensitiveCaloDetector*> > detList;
  LogDebug("SimG4CoreSensitiveDetector") << " AttachSD: Initializing" ;
  const std::vector<std::string>& rouNames = clg.readoutNames();
  for (auto & rname : rouNames) {
    std::string className = clg.className(rname);
    edm::LogInfo("SimG4CoreSensitiveDetector") << " AttachSD: trying to find something for " 
					       << className << " "  << rname;
    std::unique_ptr<SensitiveDetectorMakerBase> 
      temp(SensitiveDetectorPluginFactory::get()->create(className));
    SensitiveTkDetector* tkDet = nullptr;
    SensitiveCaloDetector* caloDet = nullptr;
    temp.get()->make(rname,cpv,clg,p,man,reg,tkDet,caloDet);
    if(tkDet){
      detList.first.push_back(tkDet);
    }
    if(caloDet){
      detList.second.push_back(caloDet);
    }
    LogDebug("SimG4CoreSensitiveDetector") 
      << " AttachSD: created a " << className << " with name " << rname;
  }      
  return detList;
}

