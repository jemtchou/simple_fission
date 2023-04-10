#ifndef SimpleDetector_h
#define SimpleDetector_h 1

#include "G4VSensitiveDetector.hh"

class G4Step;
class G4HCofThisEvent;

class SimpleDetector : public G4VSensitiveDetector
{
  public:
    SimpleDetector(G4String name);
    virtual ~SimpleDetector();
  
    // methods from base class
    virtual void   Initialize(G4HCofThisEvent* hitCollection);
    virtual G4bool ProcessHits(G4Step* step, G4TouchableHistory* history);
    virtual void   EndOfEvent(G4HCofThisEvent* hitCollection);

  private:

};

#endif
