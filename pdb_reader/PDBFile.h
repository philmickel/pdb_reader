#pragma once
#include <vector>
#include <string>
#include <map>
#include "Atom.h"

/*
.pdb files contain many potential REMARK statements; some important statements are:
REMARK 290 - Crystallographic Symmetry information. Automatically generated. Has information like symmetry operators/space group, etc.
REMARK 465 - Residues that are present in SEQRES records but absent from coordinates section
REMARK 470 - Non-hydrogen atoms in standard residues that are missing from coordinates section. Also missing HETATMs within heterogen groups in SEQRES also listed.
REMARK 475 - Residues modeled with zero occupancy (i.e. 0% chance of existing in that form?)
REMARK 480 - Non-hydrogen atoms modeled with zero occupancy.

I plan to have these REMARK statements accounted for in the future.

*/

class PDBFile
{
public:
  explicit PDBFile(const std::string& topology_filename);
  ~PDBFile();

  void read(const std::string& filename);
  void write(const std::string& filename, const std::vector<Atom>& atoms);
  void parseTopology();

  std::vector<Atom> getAtoms() const;

private:
  std::vector<Atom> atoms;
  std::string topology_filename;
  std::map<std::string, std::map<std::string, std::vector<std::string>>> topology;
};