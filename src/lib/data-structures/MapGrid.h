/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file MapGrid.h
    \brief This file defines the MapGrid class, which represents a map grid.
  */

#ifndef MAPGRID_H
#define MAPGRID_H

#include <string>

#include "data-structures/Grid.h"

/** The class MapGrid represents a map grid.
    \brief Map grid
  */
class MapGrid :
  public Grid<double, std::string, 2> {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs MapGrid with parameters
  inline MapGrid(const Coordinate& minimum, const Coordinate& maximum, const
    Coordinate& resolution);
  /// Copy constructor
  inline MapGrid(const MapGrid& other);
  /// Assignment operator
  inline MapGrid& operator = (const MapGrid& other);
  /// Destructor
  inline virtual ~MapGrid();
  /** @}
    */

  /** \name Stream methods
    @{
    */
  /// Stream the MapGrid into binary format
  inline virtual void writeBinary(std::ostream& stream) const;
  /// Reads the MapGrid from a binary format
  inline virtual void readBinary(std::istream& stream);
  /** @}
    */

protected:

};

#include "data-structures/MapGrid.tpp"

#endif // MAPGRID_H