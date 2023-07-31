# pdb_reader
Rough first draft for a C++ based Protein Data Bank (PDB) file reader. 

The code has no dependencies beyond C++. 

Currently, what it will do is read in a standard .pdb file and return an array of Atom objects containing various information about the atom. It will also input a CHARM36 topology file, scan through the atoms in the array and assign each atom a list of atoms it is bonded with according to the CHARMM36 topology file. It will alert the user of any missing atoms, but it doesn't currently update the .pdb with these missing atoms. 
