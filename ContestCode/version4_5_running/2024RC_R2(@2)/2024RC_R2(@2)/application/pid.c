/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       pid.c/h
  * @brief      pid???????????????????PID????????
  * @note       
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Dec-26-2018     RM              1. ???
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */

#include "pid.h"
#include "main.h"
#include "chassis_task.h"
#include <math.h>

float angle_target;
float angle_actual;
float err_absolute;
float err_absolute_e;


#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }

/**
  * @brief          pid struct data init
  * @param[out]     pid: PID struct data point
  * @param[in]      mode: PID_POSITION: normal pid
  *                 PID_DELTA: delta pid
  * @param[in]      PID: 0: kp, 1: ki, 2:kd
  * @param[in]      max_out: pid max out
  * @param[in]      max_iout: pid max iout
  * @retval         none
  */
/**
  * @brief          pid struct data init
  * @param[out]     pid: PID?????????
  * @param[in]      mode: PID_POSITION:???PID
  *                 PID_DELTA: ???PID
  * @param[in]      PID: 0: kp, 1: ki, 2:kd
  * @param[in]      max_out: pid??????
  * @param[in]      max_iout: pid?????????
  * @retval         none
  */
void PID_init(pid_type_def *pid, uint8_t mode, const fp32 PID[3], fp32 max_out, fp32 max_iout)
{
    if (pid == NULL || PID == NULL)
    {
        return;
    }
    pid->mode = mode;
    pid->Kp = PID[0];
    pid->Ki = PID[1];
    pid->Kd = PID[2];
    pid->max_out = max_out;
    pid->max_iout = max_iout;
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    pid->error[0] = pid->error[1] = pid->error[2] = pid->Pout = pid->Iout = pid->Dout = pid->out = 0.0f;
}

/**
  * @brief          pid calculate 
  * @param[out]     pid: PID struct data point
  * @param[in]      ref: feedback data 
  * @param[in]      set: set point
  * @retval         pid out
  */
/**
  * @brief          pid????
  * @param[out]     pid: PID?????????
  * @param[in]      ref: ????????
  * @param[in]      set: ???
  * @retval         pid???
  */
fp32 PID_calc(int mode,pid_type_def *pid, fp32 ref, fp32 set)
{
	if(mode==0)
	{
		 if (pid == NULL)
		{
			return 0.0f;
		}

		pid->error[2] = pid->error[1];
		pid->error[1] = pid->error[0];
		pid->set = set;
		pid->fdb = ref;
		pid->error[0] = set - ref;
		if (pid->mode == PID_POSITION)
		{
			pid->Pout = pid->Kp * pid->error[0];
			pid->Iout += pid->Ki * pid->error[0];
			pid->Dbuf[2] = pid->Dbuf[1];
			pid->Dbuf[1] = pid->Dbuf[0];
			pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
			pid->Dout = pid->Kd * pid->Dbuf[0];
			LimitMax(pid->Iout, pid->max_iout);
			pid->out = pid->Pout + pid->Iout + pid->Dout;
			LimitMax(pid->out, pid->max_out);
		}
		else if (pid->mode == PID_DELTA)
		{
			pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
			pid->Iout = pid->Ki * pid->error[0];
			pid->Dbuf[2] = pid->Dbuf[1];
			pid->Dbuf[1] = pid->Dbuf[0];
			pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
			pid->Dout = pid->Kd * pid->Dbuf[0];
			pid->out += pid->Pout + pid->Iout + pid->Dout;
			LimitMax(pid->out, pid->max_out);
		}	
	}
   
	if(mode==1)
    {
		angle_target = pid->set = set;
		pid->fdb = ref;
		angle_actual = map(pid->fdb,0,360,-180,180);

		err_absolute = angle_target - angle_actual;
		
		if(fabs(err_absolute)> 180)
		{
			if(err_absolute < 0)
			{
				err_absolute_e = 360 + err_absolute;
			}
			
			if(err_absolute > 0)
			{
				err_absolute_e =  err_absolute - 360;
			}
			pid->error[0] = err_absolute_e;
		}
		
		if(fabs(err_absolute)< 180)
		{
			pid->error[0] = err_absolute;
		}
		
		pid->error[3] = pid->error[2];
		pid->error[2] = pid->error[1];
		pid->error[1] = pid->error[0];
		
//		pid->set = set;
//		pid->fdb = ref;	
			
		pid->Pout = pid->Kp * (pid->error[1] - pid->error[2]);
        pid->Iout = pid->Ki * pid->error[1];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[1] - 2.0f * pid->error[2] + pid->error[3]);
        pid->Dout = pid->Kd * pid->Dbuf[0];
        pid->out += pid->Pout + pid->Iout + pid->Dout;
        LimitMax(pid->out, pid->max_out);
		
//        pid->Pout = pid->Kp * (pid->error[0] - pid->error[1]);
//        pid->Iout = pid->Ki * pid->error[0];
//        pid->Dbuf[2] = pid->Dbuf[1];
//        pid->Dbuf[1] = pid->Dbuf[0];
//        pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
//        pid->Dout = pid->Kd * pid->Dbuf[0];
//        pid->out += pid->Pout + pid->Iout + pid->Dout;
//        LimitMax(pid->out, pid->max_out);
    }	
    return pid->out;
}

/**
  * @brief          pid out clear
  * @param[out]     pid: PID struct data point
  * @retval         none
  */
/**
  * @brief          pid ??????
  * @param[out]     pid: PID?????????
  * @retval         none
  */
void PID_clear(pid_type_def *pid)
{
    if (pid == NULL)
    {
        return;
    }

    pid->error[0] = pid->error[1] = pid->error[2] = 0.0f;
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    pid->out = pid->Pout = pid->Iout = pid->Dout = 0.0f;
    pid->fdb = pid->set = 0.0f;
}
