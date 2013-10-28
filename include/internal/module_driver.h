#ifndef TRIK_V4L2_DSP_FB_INTERNAL_MODULE_DRIVER_H_
#define TRIK_V4L2_DSP_FB_INTERNAL_MODULE_DRIVER_H_

#include <stdbool.h>
#include <time.h>


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus


typedef struct DriverConfig // what user wants to set
{
  int m_zeroX;
  int m_zeroY;
  int m_zeroMass;
} DriverConfig;


typedef struct DriverCtrlChasis
{
  int         m_motorSpeedLeft;
  int         m_motorSpeedRight;

  int         m_lastSpeed; // -100..100
  int         m_lastYaw;   // -100..100
} DriverCtrlChasis;

typedef struct DriverCtrlHand
{
  int         m_motorSpeed;

  int         m_lastSpeed; // -100..100
} DriverCtrlHand;

typedef struct DriverCtrlArm
{
  int         m_motorSpeed;
} DriverCtrlArm;

typedef struct DriverOutput
{
  int              m_zeroX;
  int              m_zeroY;
  int              m_zeroMass;

  DriverCtrlChasis m_ctrlChasis;
  DriverCtrlHand   m_ctrlHand;
  DriverCtrlArm    m_ctrlArm;

  enum State
  {
    StateManual,
    StatePreparing,
    StateSearching,
    StateTracking,
    StateSqueezing,
    StateReleasing
  } m_state;
  struct timespec m_stateEntryTime;

} DriverOutput;


int driverOutputInit(bool _verbose);
int driverOutputFini();

int driverOutputOpen(DriverOutput* _driver, const DriverConfig* _config);
int driverOutputClose(DriverOutput* _driver);
int driverOutputStart(DriverOutput* _driver);
int driverOutputStop(DriverOutput* _driver);

int driverOutputControlAuto(DriverOutput* _driver, int _targetX, int _targetY, int _targetMass);
int driverOutputControlManual(DriverOutput* _driver, int _ctrlChasisLR, int _ctrlChasisFB, int _ctrlHand, int _ctrlArm);

int driverOutputGetControl(const DriverOutput* _driver, int* _ctrlChasisLeft, int* _ctrlChasisRight, int* _ctrlHand, int* _ctrlArm);


#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif // !TRIK_V4L2_DSP_FB_INTERNAL_MODULE_DRIVER_H_
