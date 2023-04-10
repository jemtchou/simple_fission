#include "SimpleGeometry.hh"
#include "SimpleParticleSource.hh"
#include "SimpleRunAction.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4RunManager.hh"
#include "G4ProductionCuts.hh"
#include "G4UImanager.hh"
#include "FREYA.hh"
#include "NeutronPhysicsFREYA.hh"

#define FISSION_NEW 1

int main(int argc, char** argv)
{    
  // Construct the default run manager

  G4RunManager * runManager = new G4RunManager;

  // Set mandatory initialization classes

  // Detector construction
  runManager->SetUserInitialization(new SimpleGeometry());

  // Physics list
  auto plist = new FREYA;
  runManager->SetUserInitialization(plist);
    
  // Primary generator action
  runManager->SetUserAction(new SimpleParticleSource());

  runManager->SetUserAction(new SimpleRunAction);

  // Initialize G4 kernel
  runManager->Initialize();

  G4UIExecutive* ui = new G4UIExecutive(argc, argv);

//  G4UImanager::GetUIpointer()->ApplyCommand("/tracking/verbose 2");

  if(argc>1) G4UImanager::GetUIpointer()->ApplyCommand("/control/execute "+G4String(argv[1]));
  else{
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();

    // interactive mode
    G4UImanager::GetUIpointer()->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete visManager;
  }

  delete ui;
  delete runManager;
  return 0;
}
