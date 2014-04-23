
#include <boutmain.hxx>
#include <smoothing.hxx>
#include <invert_laplace.hxx>
#include <derivs.hxx>
#include <field_factory.hxx>
#include <bout/constants.hxx>

Field3D n, vort;  // Evolving density and vorticity
Field3D phi;

BoutReal alpha, kappa, Dvort, Dn;
bool modified; // Modified H-W equations?

class Laplacian* phiSolver; // Laplacian solver for vort -> phi

// Poisson brackets: b0 x Grad(f) dot Grad(g) / B = [f, g]
// Method to use: BRACKET_ARAKAWA, BRACKET_STD or BRACKET_SIMPLE
BRACKET_METHOD bm; // Bracket method for advection terms

int physics_init(bool restart) {
  
  Options *options = Options::getRoot()->getSection("hw");
  OPTION(options, alpha, 1.0);
  OPTION(options, kappa, 0.1);
  OPTION(options, Dvort, 1e-2);
  OPTION(options, Dn,    1e-2);

  OPTION(options, modified, false);
  
  ////// Set mesh spacing
  Options *meshoptions = Options::getRoot()->getSection("mesh");

  BoutReal Lx;
  meshoptions->get("Lx",Lx,1.0);

  /*this assumes equidistant grid*/
  int nguard = mesh->xstart;
  mesh->dx = Lx/(mesh->GlobalNx - 2*nguard);
  mesh->dz = TWOPI*Lx/(mesh->ngz-1);
  /////

  SOLVE_FOR2(n, vort);
  SAVE_REPEAT(phi);

  phiSolver = Laplacian::create();
  phi = 0.; // Starting phi
  
  // Use default flags 

  // Choose method to use for Poisson bracket advection terms
  int bracket;
  OPTION(options, bracket, 0);
  switch(bracket) {
  case 0: {
    bm = BRACKET_STD; 
    output << "\tBrackets: default differencing\n";
    break;
  }
  case 1: {
    bm = BRACKET_SIMPLE; 
    output << "\tBrackets: simplified operator\n";
    break;
  }
  case 2: {
    bm = BRACKET_ARAKAWA; 
    output << "\tBrackets: Arakawa scheme\n";
    break;
  }
  case 3: {
    bm = BRACKET_CTU; 
    output << "\tBrackets: Corner Transport Upwind method\n";
    break;
  }
  default:
    output << "ERROR: Invalid choice of bracket method. Must be 0 - 3\n";
    return 1;
  }

  return 0;
}

const Field3D bracketTest(const Field3D &f, const Field3D &g) {
  return DDZ(f)*DDX(g) - DDZ(g)*DDX(f);
  //return bracket(f, g, bm) 
}

const Field3D Delp2mod(const Field3D &f) {
  return D2DX2(f) + D2DZ2(f);
  //return Delp2(f,0.0);
}

int physics_run(BoutReal time) {
  
  // Solve for potential
  //phi = phiSolver->solve(vort, phi);
  phi = FieldFactory::get()->create3D("phi:solution", Options::getRoot(), mesh, CELL_CENTRE, time);
  
  // Communicate variables
  mesh->communicate(n, vort, phi);

  // Modified H-W equations, with zonal component subtracted from resistive coupling term
  Field3D nonzonal_n = n;
  Field3D nonzonal_phi = phi;
  if(modified) {
    // Subtract average in Y and Z
    nonzonal_n -= averageY(n.DC());
    nonzonal_phi -= averageY(phi.DC());
  }
  
  ddt(n) = 
    - bracketTest(phi, n)//bracket(phi, n, bm) 
    + alpha*(nonzonal_phi - nonzonal_n)
    - kappa*DDZ(phi)
    + Dn*Delp2mod(n)
    ;
  
  ddt(vort) = 
    - bracketTest(phi, vort)//bracket(phi, vort, bm)
    + alpha*(nonzonal_phi - nonzonal_n)
    + Dvort*Delp2mod(vort)
    ;
  
  return 0;
}
