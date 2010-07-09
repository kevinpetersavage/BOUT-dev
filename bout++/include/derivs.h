/**************************************************************************
 * Basic differential functions
 *
 **************************************************************************
 * Copyright 2010 B.D.Dudson, S.Farley, M.V.Umansky, X.Q.Xu
 *
 * Contact: Ben Dudson, bd512@york.ac.uk
 * 
 * This file is part of BOUT++.
 *
 * BOUT++ is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BOUT++ is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with BOUT++.  If not, see <http://www.gnu.org/licenses/>.
 * 
 **************************************************************************/

#ifndef __DERIVS_H__
#define __DERIVS_H__

#include "field3d.h"
#include "field2d.h"
#include "vector3d.h"
#include "vector2d.h"

#include "bout_types.h" // See this for codes

int derivs_init();

////////// FIRST DERIVATIVES //////////

const Field3D DDX(const Field3D &f, CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT);
const Field3D DDX(const Field3D &f, DIFF_METHOD method, CELL_LOC outloc);
const Field3D DDX(const Field3D &f, DIFF_METHOD method);
const Field2D DDX(const Field2D &f);

const Field3D DDY(const Field3D &f, CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT);
const Field3D DDY(const Field3D &f, DIFF_METHOD method, CELL_LOC outloc);
const Field3D DDY(const Field3D &f, DIFF_METHOD method);
const Field2D DDY(const Field2D &f);

const Field3D DDZ(const Field3D &f, CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT, bool inc_xbndry = false);
const Field3D DDZ(const Field3D &f, DIFF_METHOD method, CELL_LOC outloc, bool inc_xbndry=false);
const Field3D DDZ(const Field3D &f, DIFF_METHOD method, bool inc_xbndry = false);
const Field3D DDZ(const Field3D &f, bool inc_xbndry);
const Field2D DDZ(const Field2D &f);

const Vector3D DDZ(const Vector3D &v, CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT);
const Vector3D DDZ(const Vector3D &v, DIFF_METHOD method, CELL_LOC outloc = CELL_DEFAULT);
const Vector2D DDZ(const Vector2D &v);

////////// SECOND DERIVATIVES //////////

const Field3D D2DX2(const Field3D &f, CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT);
const Field3D D2DX2(const Field3D &f, DIFF_METHOD method, CELL_LOC outloc = CELL_DEFAULT);
const Field2D D2DX2(const Field2D &f);

const Field3D D2DY2(const Field3D &f, CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT);
const Field3D D2DY2(const Field3D &f, DIFF_METHOD method, CELL_LOC outloc = CELL_DEFAULT);
const Field2D D2DY2(const Field2D &f);

const Field3D D2DZ2(const Field3D &f, CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT);
const Field3D D2DZ2(const Field3D &f, DIFF_METHOD method, CELL_LOC outloc = CELL_DEFAULT);
const Field2D D2DZ2(const Field2D &f);

/////////// MIXED DERIVATIVES //////////

const Field3D D2DXDZ(const Field3D &f);

///////// UPWINDING METHODS /////////////

const Field2D VDDX(const Field2D &v, const Field2D &f, CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT);
const Field2D VDDX(const Field2D &v, const Field2D &f, DIFF_METHOD method);

const Field3D VDDX(const Field &v, const Field &f, 
		   CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT);
const Field3D VDDX(const Field &v, const Field &f, DIFF_METHOD method, CELL_LOC outloc = CELL_DEFAULT);

const Field2D VDDY(const Field2D &v, const Field2D &f,
		   CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT);
const Field2D VDDY(const Field2D &v, const Field2D &f, DIFF_METHOD method);
const Field3D VDDY(const Field &v, const Field &f, 
		   CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT);
const Field3D VDDY(const Field &v, const Field &f, DIFF_METHOD method, CELL_LOC outloc = CELL_DEFAULT);

const Field2D VDDZ(const Field2D &v, const Field2D &f);
const Field2D VDDZ(const Field3D &v, const Field2D &f);
const Field3D VDDZ(const Field &v, const Field &f, 
		   CELL_LOC outloc = CELL_DEFAULT, DIFF_METHOD method = DIFF_DEFAULT);
const Field3D VDDZ(const Field &v, const Field &f, DIFF_METHOD method, CELL_LOC outloc = CELL_DEFAULT);

#endif // __DERIVS_H__