#include "header/vehicleConstrainVelTask.h"

VehicleConstrainVelTask::VehicleConstrainVelTask(int dim, bool eqType, std::string robotName)
  : Task(dim, eqType, robotName, "VEHICLE_CONSTRAIN_VEL") {
  //no gain: non reactive task

}


/**
 * @brief VehicleConstrainVelTask::updateMatrices overriden of the pure virtual method of Task parent class
 * @param robInfo struct filled with all infos needed by the task to compute the matrices
 * @return 0 for correct execution
 */
int VehicleConstrainVelTask::updateMatrices(struct Infos* const robInfo){

  setActivation();
  setJacobian();
  setReference(robInfo->robotState.vehicleVel);
  return 0;
}

/**
 * @brief VehicleConstrainVelTask::setJacobian simple identity for vehicle part
 * @param wTv_eigen transformation from world to vehicle
 */
void VehicleConstrainVelTask::setJacobian(){

  Eigen::Matrix<double, 6, TOT_DOF> J_eigen = Eigen::Matrix<double, 6, TOT_DOF>::Zero();
  J_eigen.rightCols(dimension) = Eigen::Matrix<double, 6, 6>::Identity();

  J = CONV::matrix_eigen2cmat(J_eigen);


}

void VehicleConstrainVelTask::setActivation(){

  double vectDiag[dimension];
  std::fill_n(vectDiag, dimension, 1);
  this->A.SetDiag(vectDiag);
}
/**
 * @brief VehicleConstrainVelTask::setReference
 * @param actualVel actual mesaured (in someway) velocities [lin; ang] of the vehicle
 * @note this task is a non reactive one: the reference are the actual velocities of
 * the vehicle, so the velocities produces by this task constrain the second list of
 * task to not change them. (i.e. only the arm will be involved in the next task)
 */
void VehicleConstrainVelTask::setReference(std::vector<double> actualVel){

  for (int i=1; i<=dimension; ++i){
    this->reference(i) = actualVel[i-1];
  }
}

