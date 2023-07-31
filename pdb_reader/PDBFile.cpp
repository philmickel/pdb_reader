#include "PDBFile.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>

PDBFile::PDBFile(const std::string& topology_filename)
  : topology_filename(topology_filename)
{
  parseTopology();
}
PDBFile::~PDBFile()
{

}

void PDBFile::read(const std::string& PDBFilename)
{ 
  std::vector<Atom> newAtoms;
  std::ifstream inputFile(PDBFilename);

  if (!inputFile)
  {
    throw std::runtime_error("Could not open file");
  }
  std::string line;

  std::cout << "Read first line.\n";

  while (std::getline(inputFile, line))
  {
    std::string atomType = line.substr(0, 6);
    atomType.erase(std::remove(atomType.begin(), atomType.end(), ' '), atomType.end());
    if (atomType == "ATOM" || atomType == "HETATM")
    {
      std::string atomName = line.substr(12, 4);
      atomName.erase(std::remove(atomName.begin(), atomName.end(), ' '), atomName.end());

      int atomIndex = std::stoi(line.substr(6, 5));

      char altloc = line[16];

      std::string resName = line.substr(17, 3);
      resName.erase(std::remove(resName.begin(), resName.end(), ' '), resName.end());

      char chain = line[21];

      int resID = std::stoi(line.substr(22, 4));

      double x = std::stod(line.substr(30, 8));
      double y = std::stod(line.substr(38, 8));
      double z = std::stod(line.substr(46, 8));

      double occupancy = std::stod(line.substr(54, 6));

      std::string segID = line.substr(72, 4);
      segID.erase(std::remove(segID.begin(), segID.end(), ' '), segID.end());

      std::string element = line.substr(76, 2);
      element.erase(std::remove(element.begin(), element.end(), ' '), element.end());

      newAtoms.emplace_back(atomType, atomName, atomIndex, altloc, resName, chain, resID, x, y, z, occupancy, segID, element);

      //DEBUG CODE BELOW
      //std::cout << "Adding atom: " << atomName << "\n";
      //std::cout << "  Residue: " << resName << "\n";
      //std::cout << "  Chain: " << chain << "\n";
      //std::cout << "  ResID: " << resID << "\n";
      //std::cout << "  Coordinates: (" << x << ", " << y << ", " << z << ")\n";
      //std::cout << "  Occupancy: " << occupancy << "\n";
      //std::cout << "  SegID: " << segID << "\n";
      //std::cout << "  Element: " << element << "\n";
      //END DEBUG CODE
    }
  }
  parseTopology();
  atoms = newAtoms;
  inputFile.close();

  std::map<std::string, std::map<int, std::map<std::string, Atom*>>> atomLookup;
  for (Atom& atom : atoms) {
    atomLookup[atom.getResName()][atom.getResID()][atom.getAtomName()] = &atom;
  }
  for (Atom& atom : atoms) {
    std::string resName = atom.getResName();
    int resID = atom.getResID();
    std::string atomName = atom.getAtomName();

    if (topology.count(resName) > 0) {
      if (topology[resName].count(atomName) > 0) {
        std::vector<std::string> bonded_atom_names = topology[resName][atomName];

        for (const std::string& bonded_atom_name : bonded_atom_names) {
          if (atomLookup[resName][resID].count(bonded_atom_name) > 0) {
            Atom* bonded_atom = atomLookup[resName][resID][bonded_atom_name];
            atom.addBond(bonded_atom);
          }
          else {
            std::cout << "Warning: Atom " << bonded_atom_name
              << " in residue " << resName << " " << resID
              << " does not exist but is listed in the topology file.\n";
          }
        }
      }
    }
  }
}

void PDBFile::parseTopology() {
  std::ifstream file(topology_filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file " + topology_filename);
  }

  topology.clear();
  std::string line;
  std::string current_residue;
  while (std::getline(file, line)) {
    std::istringstream ss(line);
    std::string first_word;
    ss >> first_word;
    if (first_word == "RESI") {
      ss >> current_residue;
      topology[current_residue] = std::map<std::string, std::vector<std::string>>();
    }
    else if (first_word == "BOND") {
      std::string atom1, atom2;
      while (ss >> atom1 >> atom2) {
        topology[current_residue][atom1].push_back(atom2);
        topology[current_residue][atom2].push_back(atom1);

        //DEBUG CODE BELOW
        std::cout << "Adding bonds for residue: " << current_residue << "\n";
        for (auto& bond : topology[current_residue]) {
          std::cout << "  " << bond.first << " : ";
          for (auto& bonded_atom : bond.second) {
            std::cout << bonded_atom << " ";
          }
          std::cout << "\n";
        }
        //END DEBUG CODE
      }
    }
  }
  file.close();
  return;
}

std::vector<Atom> PDBFile::getAtoms() const {
  return atoms;  
}