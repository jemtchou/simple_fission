#include "SimpleRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"

SimpleRunAction::SimpleRunAction() : G4UserRunAction()
{
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  G4int id = analysisManager->CreateH1("hist_0", "Kine", 100, 0, 2000);
}

SimpleRunAction::~SimpleRunAction()
{}

void SimpleRunAction::BeginOfRunAction(const G4Run* aRun)
{ 
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile("run.root");

  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
}

void SimpleRunAction::EndOfRunAction(const G4Run*)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}
