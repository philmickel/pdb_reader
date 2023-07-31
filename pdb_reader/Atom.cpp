#include "Atom.h"
#include <iostream>

// Constructor
Atom::Atom(std::string atomType, std::string atomName, int atomIndex, char altloc,
  std::string resName, char chain, int resID, double x, double y, double z,
  double occupancy, std::string segID, std::string element)
  : atomType(atomType), atomName(atomName), atomIndex(atomIndex), altloc(altloc),
  resName(resName), chain(chain), resID(resID), x(x), y(y), z(z),
  occupancy(occupancy), segID(segID), element(element) {}

// Getters and setters
std::string Atom::getAtomType() const
{
  return atomType;
}

std::string Atom::getAtomName() const
{
  return atomName;
}

int Atom::getAtomIndex() const
{
  return atomIndex;
}

char Atom::getAltloc() const
{
  return altloc;
}

std::string Atom::getResName() const
{
  return resName;
}

char Atom::getChain() const
{
  return chain;
}

int Atom::getResID() const
{
  return resID;
}

double Atom::getX() const
{
  return x;
}

double Atom::getY() const
{
  return y;
}

double Atom::getZ() const
{
  return z;
}

double Atom::getOccupancy() const
{
  return occupancy;
}

std::string Atom::getSegID() const
{
  return segID;
}

std::string Atom::getElement() const
{
  return element;
}

const std::vector<Atom*>& Atom::getBonds() const {
  return bonds;
}

void Atom::setAtomType(std::string newAtomType)
{
  atomType = newAtomType;
}

void Atom::setAtomName(std::string newAtomName)
{
  atomName = newAtomName;
}

void Atom::setAtomIndex(int newAtomIndex)
{
  atomIndex = newAtomIndex;
}

void Atom::setAltloc(char newAltloc)
{
  altloc = newAltloc;
}

void Atom::setResName(std::string newResName)
{
  resName = newResName;
}

void Atom::setChain(char newChain)
{
  chain = newChain;
}

void Atom::setResID(int newResID)
{
  resID = newResID;
}

void Atom::setX(double newX)
{
  x = newX;
}

void Atom::setY(double newY)
{
  y = newY;
}

void Atom::setZ(double newZ)
{
  z = newZ;
}

void Atom::setOccupancy(double newOccupancy)
{
  occupancy = newOccupancy;
}

void Atom::setSegID(std::string newSegID)
{
  segID = newSegID;
}

void Atom::setElement(std::string newElement)
{
  element = newElement;
}

void Atom::addBond(Atom* atom)
{
  bonds.push_back(atom);
}