#include "header/vehicleReachTask.h"

/**
 * @brief VehicleReachTask::VehicleReachTask Constructor of specific task simply calls the parent constructor
 * through inizializer list
 * @param dimension dimension of the task (e.g. 1 for scalar task)
 * @param dof degrees of freedom of the robot (4+6 for girona500 with 4DOF arm)
 * @param eqType true or false for equality or inequality task
 */
VehicleReachTask::VehicleReachTask(int dimension, int dof, bool eqType)
  : Task(dimension, dof, eqType) {
  gain = 0.2;
}

VehicleReachTask::VehicleReachTask(int dimension, bool eqType)
  : Task(dimension, eqType) {
  gain = 0.2;
}

/**
 * @brief VehicleReachTask::updateMatrices overriden of the pure virtual method of Task parent class
 * @param robInfo struct filled with all infos needed by the task to compute the matrices
 * @return 0 for correct execution
 */
int VehicleReachTask::updateMatrices(struct Infos* const robInfo){

  setActivation();
  setJacobian(robInfo->robotState.wTv_eigen);
  setReference(robInfo->robotState.wTv_eigen, robInfo->transforms.wTgoalVeh_eigen);
  return 0;
}

int VehicleReachTask::setJacobian(Eigen::Matrix4d wTv_eigen){

  Eigen::MatrixXd jacobian_eigen = Eigen::MatrixXd::Zero(dimension, dof);
  Eigen::Matrix3d wRv_eigen = wTv_eigen.topLeftCorner(3,3);

  //matrix([1:6];[1:4]) deve restare zero
  //matrix([1:3];[5:7]) parte linear
  jacobian_eigen.block(0,4, 3,3) = wRv_eigen; //block: beginning row, beginning column,  dimensions (rows & columns)

  //matrix([4:6];[8:10]) parte angolare
  //according to eigen doc, using these kind of specific function (and not
  //.block) improves performance
  jacobian_eigen.bottomRightCorner(3,3) = wRv_eigen;

  //to cmat
  //eigen unroll to vector for cmat function
  this->J = CMAT::Matrix(dimension, dof, jacobian_eigen.data());

  //J.PrintMtx("JACOB");  ///DEBUG

}

int VehicleReachTask::setActivation(){

  double vectDiag[6];
  std::fill_n(vectDiag, 6, 1);
  this->A.SetDiag(vectDiag);

  return 0;
}

int VehicleReachTask::setReference(
    Eigen::Matrix4d wTv_eigen, Eigen::Matrix4d wTg_eigen){

  CMAT::TransfMatrix wTv_cmat = CONV::matrix_eigen2cmat(wTv_eigen);
  CMAT::TransfMatrix wTg_cmat = CONV::matrix_eigen2cmat(wTg_eigen);
  CMAT::Vect6 errorSwapped = CMAT::CartError(wTg_cmat, wTv_cmat); //ang,lin
  // ang and lin must be swapped because in qDot and jacob linear part is before
  CMAT::Vect6 error;
  error.SetFirstVect3(errorSwapped.GetSecondVect3());
  error.SetSecondVect3(errorSwapped.GetFirstVect3());

  this->reference = this->gain * (error);
}
