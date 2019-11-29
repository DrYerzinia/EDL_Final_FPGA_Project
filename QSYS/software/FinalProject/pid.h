#ifndef PID_H_
#define PID_H_

typedef enum {

	FORWARD,
	REVERSE

} pid_mode_e;

typedef float fp_t;

typedef struct {

	// target
	fp_t setpoint;

	// integral state
	fp_t i;

	// previous error
	fp_t prev_err;

	// PID tuning parameters
	fp_t kp;
	fp_t ki;
	fp_t kd;

	// integral term wind-up limit
	fp_t windup_limit;

	// control effort saturation limits
	fp_t max;
	fp_t min;

	// Forward or reverse
	pid_mode_e mode;

} PID_t;

fp_t pid_compute(PID_t * pid, fp_t input, fp_t dt);

#endif
