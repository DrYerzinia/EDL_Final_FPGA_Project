#include "pid.h"

/**
 * Updates the PID controller from a given input
 *
 * @param pid PID controller object
 * @param input Current state
 *
 * @return Control effort
 */
fp_t pid_compute(PID_t * pid, fp_t input, fp_t dt){

	fp_t err = pid->setpoint - input;

	// Integrate error
	pid->i += err;

	// Check wind-up limit
	if(pid->i > pid->windup_limit){
		pid->i = pid->windup_limit;
	} else if(pid->i < -1.0f * pid->windup_limit){
		pid->i = -1.0f * pid->windup_limit;
	}

	fp_t der = err - pid->prev_err;

	pid->prev_err = err;

	fp_t output = ( pid->kp * err ) + ( pid->ki * pid->i * dt ) + ( pid->kd * der / dt );

	// Don't command more than maximum value
	if( output > pid->max){
		output = pid->max;
	} else if( output < pid->min){
		output = pid->min;
	}

	if( pid->mode == REVERSE){
		output *= -1.0f;
	}

	return output;

}
