#include "PDBFile.h"
#include <iostream>

int main()
{
  try {
    std::string topologyFilePath = "C:\\Users\\micro\\Documents\\PhD\\top_all36_prot.rtf";
    std::string pdbFilePath = "C:\\Users\\micro\\Downloads\\4gdl.pdb";
    PDBFile pdbFile(topologyFilePath);
    pdbFile.read(pdbFilePath);
    std::vector<Atom> atoms = pdbFile.getAtoms();
    std::cout << "Read " << atoms.size() << " atoms.\n";
  } catch (const std::runtime_error& e) {
    std::cerr << "Caught an exception: " << e.what() << '\n';
  }
  return 0;
}
