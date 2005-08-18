// -*- C++ -*-
//
// Package:    HcalDbSourceHardcode
// Class:      HcalDbSourceHardcode
// 
/**\class HcalDbSourceHardcode HcalDbSourceHardcode.h CalibFormats/HcalDbSourceHardcode/interface/HcalDbSourceHardcode.h

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Fedor Ratnikov
//         Created:  Wed Aug 10 15:40:06 CDT 2005
// $Id$
//
//


#include <iostream>

#include "FWCore/Framework/interface/ESHandle.h"

#include "HcalDbSourceHardcode.h"


 HcalDbSourceHardcode::HcalDbSourceHardcode( const edm::ParameterSet& iConfig )
 {
   std::cout << "HcalDbSourceHardcode::HcalDbSourceHardcode ..." << std::endl;
   this->findingRecord <HcalDbRecord> ();
   setWhatProduced(this);
 }


 HcalDbSourceHardcode::~HcalDbSourceHardcode() {}

// ------------ method called to produce the data  ------------
 HcalDbSourceHardcode::ReturnType
 HcalDbSourceHardcode::produce( const HcalDbRecord& iRecord )
 {

   std::cout << "HcalDbSourceHardcode::produce ..." << std::endl;
  
   std::auto_ptr<HcalDbServiceHardcode> pHcalDbServiceHardcode (new HcalDbServiceHardcode);

    return pHcalDbServiceHardcode ;
 }

 void 
 HcalDbSourceHardcode::setIntervalFor( const edm::eventsetup::EventSetupRecordKey&,
 				      const edm::IOVSyncValue& iTime, 
 				      edm::ValidityInterval& iInterval) {
   //Be valid for 3 time steps
   edm::CollisionID newTime = (iTime.collisionID() - 1 ) - ((iTime.collisionID() - 1 ) %3) +1;
   edm::CollisionID endTime = newTime + 2;
   iInterval = edm::ValidityInterval( edm::IOVSyncValue( newTime),
				      edm::IOVSyncValue(endTime) );
 }


//define this as a plug-in
// DEFINE_FWK_EVENTSETUP_SOURCE(HcalDbSourceHardcode)
  
