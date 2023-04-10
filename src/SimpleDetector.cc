#include "SimpleDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4VProcess.hh"
#include "G4EventManager.hh"
#include "G4AnalysisManager.hh"

using namespace CLHEP;

SimpleDetector::SimpleDetector(G4String name) : G4VSensitiveDetector(name)
{
}

SimpleDetector::~SimpleDetector() 
{
}

void SimpleDetector::Initialize(G4HCofThisEvent*)
{
}

G4bool SimpleDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{  
  G4Track* track = step->GetTrack();

  auto dname = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetName();
  auto time = track->GetGlobalTime();
  auto kine = track->GetKineticEnergy();
  auto pos = step->GetPreStepPoint()->GetPosition(); 

  G4cout << "NEW HIT: " << dname << " Time: " << time/ns << " [ns] " << G4endl;

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(0, kine/MeV);
  return true;
}

void SimpleDetector::EndOfEvent(G4HCofThisEvent*)
{
}
