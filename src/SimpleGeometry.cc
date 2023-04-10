#include "SimpleGeometry.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4VSensitiveDetector.hh"
#include "G4SDManager.hh"
#include "SimpleDetector.hh"

using namespace CLHEP;

SimpleGeometry::SimpleGeometry()
: G4VUserDetectorConstruction()
{ }

SimpleGeometry::~SimpleGeometry()
{ }

G4VPhysicalVolume* SimpleGeometry::Construct()
{  
  G4bool checkOverlaps = true;

  G4NistManager* nist = G4NistManager::Instance();

  G4Isotope* U235 = new G4Isotope("U235",92,235);
  G4Element* U = new G4Element("Uranium","U",1);
  U->AddIsotope(U235,1.0);
  G4Material* Uranium = new G4Material("U235",19*g/cm3,1);
  Uranium->AddElement(U,1.0);
  G4Material* Vacuum = nist->FindOrBuildMaterial("G4_Galactic");
 
  // World
  G4Box* world = new G4Box("World", 50*cm, 50*cm, 50*cm);
  G4LogicalVolume* worldlv =                         
    new G4LogicalVolume(world, Vacuum, "World");  
  
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0, G4ThreeVector(),
                      worldlv, "World",
                      0, false, 0, checkOverlaps);

  // Lead plate
  G4Box* plate = new G4Box("UPlate", 10*cm, 10*cm, 5*cm);
  G4LogicalVolume* platelv =                         
    new G4LogicalVolume(plate, Uranium, "UPlate");  

  new G4PVPlacement(0, G4ThreeVector(0.,0.,0.),
                      platelv, "UPlate",
                      worldlv, false, 0, checkOverlaps);

  return physWorld;
}

void SimpleGeometry::ConstructSDandField()
{
  // Sensitive detectors
  G4SDManager* SDman = G4SDManager::GetSDMpointer();
  G4VSensitiveDetector* sd = new SimpleDetector("simple_detector");
  SetSensitiveDetector("UPlate", sd, true);
  SDman->AddNewDetector(sd);
}
