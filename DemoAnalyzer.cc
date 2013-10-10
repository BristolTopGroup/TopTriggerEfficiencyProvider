// -*- C++ -*-
//
// Package:    DemoAnalyzer
// Class:      DemoAnalyzer
// 
/**\class DemoAnalyzer DemoAnalyzer.cc MyAnalysers/DemoAnalyzer/src/DemoAnalyzer.cc

 Description: Analyzer to demonstrate the use of the TopTriggerEfficiencyProvider class

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Kelly Beernaert
//         Created:  Thu Nov  8 12:01:23 CET 2012
// $Id: DemoAnalyzer.cc,v 1.3 2012/12/12 11:14:42 bbetchar Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "./TopTriggerEfficiencyProvider.h"
#include <DataFormats/PatCandidates/interface/Jet.h>
#include <DataFormats/JetReco/interface/PFJet.h>
#include "DataFormats/EgammaCandidates/interface/GsfElectron.h"
#include "DataFormats/Common/interface/View.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

//
// class declaration
//

class DemoAnalyzer : public edm::EDAnalyzer {
   public:
      explicit DemoAnalyzer(const edm::ParameterSet&);
      ~DemoAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
      virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
      virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
DemoAnalyzer::DemoAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


DemoAnalyzer::~DemoAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
DemoAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  using namespace edm;
  edm::Handle< std::vector<reco::GsfElectron> > electron;
  iEvent.getByLabel("gsfElectrons", electron);

  edm::Handle< std::vector<reco::PFJet> > jet;
  iEvent.getByLabel("ak5PFJets", jet);
  
  edm::Handle<std::vector<reco::Vertex> > vertex;
  iEvent.getByLabel("offlinePrimaryVertices", vertex);
  
  TopTriggerEfficiencyProvider *weight_provider = new TopTriggerEfficiencyProvider();                                                                                                                    
  weight_provider->setLumi(TopTriggerEfficiencyProvider::RunB,3.1);
  weight_provider->setLumi(TopTriggerEfficiencyProvider::RunA,0);
  weight_provider->setLumi(TopTriggerEfficiencyProvider::RunC,6.01);
  weight_provider->setLumi(TopTriggerEfficiencyProvider::RunD,0);
  if(jet->size() < 4 || electron->size() == 0){return;}
  std::vector<double> weight = weight_provider->get_weight((*electron)[0].pt(), (*electron)[0].eta(), (*jet)[4].pt(), (*jet)[4].eta(), vertex->size(), jet->size(), false, TopTriggerEfficiencyProvider::NOMINAL);
  std::cout << "weight is "<<(weight)[0] << " +/- "<<(weight)[1]<< std::endl;
}


// ------------ method called once each job just before starting event loop  ------------
void 
DemoAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
DemoAnalyzer::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
void 
DemoAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
DemoAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
void 
DemoAnalyzer::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
void 
DemoAnalyzer::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
DemoAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(DemoAnalyzer);
