#pragma once
#include <string>
#include <vector>
/*
Atom.h includes the class definition for Atoms. So far, the attributes I would extract from the PDB file:
1. Atom Type (ATOM, HETATM, TER) (columns 1-6)
2. Atom Name (columns 13-16)
3. Index (columns 7-11)
4. Altloc (column 17)
5. Residue name (columns 18-20)
6. Chain identifier (column 22)
7. Residue ID (columns 23-26)
8. X, Y, Z coordinates (X, Y, Z) = columns (31-38, 39-46, 47-54)
9. Occupancy (percent in listed Altloc) (columns 55-60)
10. Segment ID (columns 73-76)
11. Element symbol (columns 77-78)
12. Missing atoms (REMARK 470) - future
13. Missing residues (REMARK 465) - future
14. Incorporated ions (REMARK 620) - future
15. Residues coordinating to the incorporated ions (REMARK 620) - future
16. Crystal structure (CRYST1, SCALE1, SCALE2, SCALE3, maybe REMARK 290) - future

If writing PDB files, atom names should be right-justified in columns 13-14, with trailing characters left-justified.
I.e., columns 14-15 filled for 2 letter, 14-16 for 3 letter, and 13-16 for 4 atom names.
*/

class Atom
{
private:
  std::string atomType;
  std::string atomName;
  int atomIndex;
  char altloc;
  std::string resName;
  char chain;
  int resID;
  double x, y, z;
  double occupancy;
  std::string segID;
  std::string element;
  std::vector<Atom*> bonds;

public:
  // Constructor
  Atom(std::string atomType, std::string atomName, int atomIndex, char altloc,
    std::string resName, char chain, int resID, double x, double y, double z,
    double occupancy, std::string segID, std::string element);

  // Getters and setters
  std::string getAtomType() const;
  std::string getAtomName() const;
  int getAtomIndex() const;
  char getAltloc() const;
  std::string getResName() const;
  char getChain() const;
  int getResID() const;
  double getX() const;
  double getY() const;
  double getZ() const;
  double getOccupancy() const;
  std::string getSegID() const;
  std::string getElement() const;
  const std::vector<Atom*>& getBonds() const;

  void setAtomType(std::string atomType);
  void setAtomName(std::string atomName);
  void setAtomIndex(int atomIndex);
  void setAltloc(char altloc);
  void setResName(std::string resName);
  void setChain(char chain);
  void setResID(int resID);
  void setX(double x);
  void setY(double y);
  void setZ(double z);
  void setOccupancy(double occupancy);
  void setSegID(std::string segID);
  void setElement(std::string element);
  void addBond(Atom* atom);
};